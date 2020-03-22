# This script generates the enums.h and enum_data.cpp files
# As input, uses the HearthDb database

import xml.etree.ElementTree as ET

# ------------------------------------------------------------------------------
# Extracting info from CardDefs.xml
# ------------------------------------------------------------------------------

def get_tag(e, n):
    return e.find("Tag[@name='{}']".format(n))

def get_tag_value(e, n, default = None):
    tag = get_tag(e, n)
    if tag is None:
        return default
    else:
        return tag.attrib['value']

def get_tag_int(e, n, default = 0):
    return int(get_tag_value(e, n, default))

def get_tag_loc_string(e, n, lang = 'enUS'):
    tag = e.find("Tag[@name='{}']/{}".format(n, lang))
    if tag is None:
        return None
    else:
        return tag.text

def enum_name(n):
    out = ""
    word_start = True
    for c in n:
        if c in "-_ ":
            word_start = True
        elif c.isalnum():
            if word_start:
                out += c.upper()
            else:
                out += c
            word_start = False
    return out

class Entity:
    e = None

    name = None
    enum_name = None
    id = None
    tribe = "None"
    tier = 0

    attack = 0
    health = 0
    taunt = False
    divine_shield = False
    poisonous = False
    windfury = False
    cleave = False
    battlecry = False
    bacon = False

    hero_power = None

    token = False
    custom = False

    def __init__(self, e):
        self.e = e
        self.name = get_tag_loc_string(self.e, 'CARDNAME', 'enUS')
        self.enum_name = enum_name(self.name)
        self.id = self.e.attrib["CardID"]
        self.tribe = self.get_tribe()
        self.tier = get_tag_int(self.e, "TECH_LEVEL", 1)
        self.attack = self.get_int("ATK")
        self.health = self.get_int("HEALTH")
        self.taunt = self.get_bool("TAUNT")
        self.divine_shield = self.get_bool("DIVINE_SHIELD")
        self.poisonous = self.get_bool("POISONOUS")
        self.windfury = self.get_bool("WINDFURY")
        self.cleave = self.get_cleave()
        self.battlecry = self.get_bool("BATTLECRY")
        self.bacon = self.get_bool("IS_BACON_POOL_MINION")
        self.token = not self.get_bool("IS_BACON_POOL_MINION")

    def get_tag(self, x):
        return get_tag(self.e, x)

    def get_int(self, x):
        return None if self.e is None else get_tag_int(self.e, x)

    def get_bool(self, x):
        return None if self.e is None else get_tag_int(self.e, x) == 1

    def get_tribe(self):
        tribe = get_tag_int(self.e, "CARDRACE")
        if tribe in tribes:
            return tribes[tribe]
        else:
            return None

    def get_cleave(self):
        text = get_tag_loc_string(self.e, "CARDTEXT")
        return text is not None and "minions next to whomever" in text


class CustomEntity(Entity):
    def __init__(self):
        self.custom = True

class NoneEntity(Entity):
    def __init__(self):
        self.name = "(none)"
        self.tier = 0

# Some tokens useless, it doesn't have tag TECH_LEVEL
extra_names = ["Safeguard", "Plant"]


def extract_data():
    # Load xml file
    cards = ET.parse('3rd-party/hsdata/CardDefs.xml')
    defs = cards.getroot()

    # Collect minions and heroes
    minions = dict()
    heroes = []

    # Loop over entities, collect minion info
    for e in defs.iterfind("Entity"):
        e = Entity(e)
        name = e.name
        if name is None:
            continue
        if e.get_int("CARDTYPE") == 4: # minion
            # only Entity with TECH_LEVEL is in battlegournd
            if not (e.get_int("TECH_LEVEL") or name in extra_names):
                continue
            if e.id == "TRLA_149": # there are two versions of Ghastcoiler
                continue
            golden = "BaconUps" in e.id
            if not e.name in minions:
                minions[e.name] = [None, None]
            if minions[e.name][1 if golden else 0] is not None:
                print("Warning: duplicate minion:", name, minions[e.name][1 if golden else 0].id, e.id)
            minions[e.name][1 if golden else 0] = e
        elif "TB_BaconShop_HERO" in e.id and e.id != "TB_BaconShop_HERO_PH" and e.get_int("CARDTYPE") == 3: # hero
            heroes.append(e)
            hero_power = e.get_tag("HERO_POWER")
            if hero_power is None or "cardID" not in hero_power.attrib:
                e.hero_power = NoneEntity()
                print("Hero power of {} not found".format(name))
            else:
                e.hero_power = Entity(defs.find("Entity[@CardID='{}']".format(hero_power.attrib["cardID"])))

    return minions, heroes

# ------------------------------------------------------------------------------
# Extra data
# ------------------------------------------------------------------------------
tribes = {0: "None", 14: "Murloc", 15: "Demon", 17: "Mech", 20: "Beast", 24: "Dragon", 26: "All"}

def add_default_minions(minions):
    minions.insert(0, [NoneEntity(), None])

# Add a custom minion
def add_custom_minions(minions):
    # Shielded Minibot is removed in patch 16.4
    minion = CustomEntity()
    minion.name = "Shielded Minibot"
    minion.enum_name = enum_name("Shielded Minibot")
    minion.tribe = "Mech"
    minion.tier = 2
    minion.attack = 2
    minion.health = 2
    minion.divine_shield = True
    minions.append([minion, None])

def add_default_heroes(heroes):
    heroes.insert(0, NoneEntity())

def format_minion_data(name, id, gold_id, tier, tribe, attack, health,
                       taunt, divive_shield, poisonous, windfury, cleave, battlecry, bacon):
    return "    {{{}, {{{}, {}}}, {}, Tribe::{}, {}, {}, {}, {}, {}, {}, {}, {}, {}}},\n" \
           .format(name, id, gold_id, tier, tribe, attack, health,
                   taunt, divive_shield, poisonous, windfury, cleave, battlecry, bacon)

# ------------------------------------------------------------------------------
# enums.h
# ------------------------------------------------------------------------------
def sort_minions(minions):
    return sorted(minions.values(), key = lambda x: (x[0].token, x[0].tier, x[0].enum_name))

def sort_heroes(heroes):
    return sorted(heroes, key = lambda x: x.enum_name)

def write_enums_h(minions, heroes):
    with open("src/utils/Enums.h", "wt", encoding = "utf-8") as f:
        f.write("#pragma once\n\n")
        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// THIS FILE IS AUTOGENERATED\n")
        f.write("// see generate_enum_data.py\n")
        f.write("// -----------------------------------------------------------------------------\n\n")

        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// Tribes\n")
        f.write("// -----------------------------------------------------------------------------\n\n")
        f.write("enum class Tribe {\n")
        for i in sorted(tribes):
            f.write("    {},\n".format(tribes[i]))
        f.write("};\n\n")
        f.write("const int TRIBE_COUNT = {};\n\n".format(len(tribes)))

        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// Minion types\n")
        f.write("// -----------------------------------------------------------------------------\n\n")
        f.write("enum class MinionType : unsigned char {\n")
        tier = 0
        for m in minions:
            e = m[0]
            if e.tier != tier:
                if e.token:
                    f.write("    // Tokens of tier {}\n".format(e.tier))
                elif e.custom:
                    f.write("    // Custom minion\n")
                else:
                    f.write("    // Tier {}\n".format(e.tier))
                tier = e.tier
            f.write("    {},\n".format(e.enum_name))

        f.write("};\n\n")
        f.write("const int MINIONTYPE_COUNT = {};\n\n".format(len(minions)))

        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// Heroes and hero powers\n")
        f.write("// -----------------------------------------------------------------------------\n\n")
        f.write("enum class HeroType {\n")
        for e in heroes:
            f.write("    {},\n".format(e.enum_name))
        f.write("};\n\n")
        f.write("const int HEROTYPE_COUNT = {};\n".format(len(heroes)))

# ------------------------------------------------------------------------------
# enum_data.cpp
# ------------------------------------------------------------------------------

def cbool(x):
    if x:
        return "true"
    else:
        return "false"

def cstr(x):
    if x is None:
        return "\"(none)\""
    else:
        return "\"" + x + "\""

def write_enum_data_cpp(minions, heroes):
    with open("src/utils/HsDataUtils.cpp", "wt", encoding = "utf-8") as f:
        f.write("#include \"HsDataUtils.h\"\n")
        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// THIS FILE IS AUTOGENERATED\n")
        f.write("// see generate_enum_data.py\n")
        f.write("// -----------------------------------------------------------------------------\n\n")
        f.write("\n")
        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// Tribe information\n")
        f.write("// -----------------------------------------------------------------------------\n\n")
        f.write("const std::vector<std::string> HsDataUtils::TribeNames = {\n")
        for i in sorted(tribes):
            f.write("    {},\n".format(cstr(tribes[i])))
        f.write("};\n\n")

        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// Minion information\n")
        f.write("// -----------------------------------------------------------------------------\n\n")
        f.write("const std::vector<MinionInfo> HsDataUtils::MinionInfos = {\n")
        for m in minions:
            e = m[0]
            f.write(format_minion_data(
                cstr(e.name),
                cstr(e.id),
                cstr(m[1].id if m[1] is not None else None),
                e.tier,
                e.tribe,
                e.attack,
                e.health,
                cbool(e.taunt),
                cbool(e.divine_shield),
                cbool(e.poisonous),
                cbool(e.windfury),
                cbool(e.cleave),
                cbool(e.battlecry),
                cbool(e.bacon)
            ))
        f.write("};\n\n")

        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// Lists of minions\n")
        f.write("// -----------------------------------------------------------------------------\n\n")
        write_minion_list(f, minions, "OneCost", lambda e: e.get_int("COST") == 1 and not e.token)
        write_minion_list(f, minions, "TwoCost", lambda e: e.get_int("COST") == 2 and not e.token)
        write_minion_list(f, minions, "FourCost", lambda e: e.get_int("COST") == 4 and not e.token)
        write_minion_list(f, minions, "DeathRattle", lambda e: e.get_int("DEATHRATTLE") and not e.token)
        write_minion_list(f, minions, "Lengendary", lambda e: e.get_int("RARITY") == 5 and not e.token)
        write_minion_list(f, minions, "Demon", lambda e: e.tribe == "Demon" and not e.token)

        f.write("// -----------------------------------------------------------------------------\n")
        f.write("// Hero / hero power information\n")
        f.write("// -----------------------------------------------------------------------------\n\n")
        f.write("const std::vector<HeroInfo> HsDataUtils::HeroInfos = {\n")
        for e in heroes:
            hp = e.hero_power
            if hp is None:
                f.write("    {{{}, {}, {{{}, {}}}}},\n".format(cstr(e.name), cstr(e.id), cstr(None), cstr(None)))
            else:
                f.write("    {{{}, {}, {{{}, {}}}}},\n".format(cstr(e.name), cstr(e.id), cstr(hp.name), cstr(hp.id)))
        f.write("};\n")

def write_minion_list(f, minions, name, filter):
    f.write("const std::vector<MinionType> HsDataUtils::{}Minions = {{\n".format(name))
    for m in minions:
        e = m[0]
        if filter(e):
            f.write("    MinionType::{},\n".format(e.enum_name))
    f.write("}};\n\n".format(name))


# ------------------------------------------------------------------------------
# Main
# ------------------------------------------------------------------------------
minions, heroes = extract_data()
print("Found", len(minions), "minions", len(heroes), "heroes")

minions = sort_minions(minions)
add_default_minions(minions)
add_custom_minions(minions)
heroes = sort_heroes(heroes)
add_default_heroes(heroes)

write_enums_h(minions, heroes)
write_enum_data_cpp(minions, heroes)
