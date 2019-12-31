#include "enums.h"
#include "MinionInfo.h"

// -----------------------------------------------------------------------------
// THIS FILE IS AUTOGENERATED
// see generate_enum_data.py
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Tribe information
// -----------------------------------------------------------------------------

const char* gTribeNames[] = {
    "None",
    "Murloc",
    "Demon",
    "Mech",
    "Beast",
    "Dragon",
    "All",
};

// -----------------------------------------------------------------------------
// Minion information
// -----------------------------------------------------------------------------

const MinionInfo gMinionInfo[] = {
    {"(none)", {"(none)", "(none)"}, 0, Tribe::None, 0, 0, false, false, false, false, false, false, false},
    {"Alleycat", {"CFM_315", "TB_BaconUps_093"}, 1, Tribe::Beast, 1, 1, false, false, false, false, false, true, true},
    {"Dire Wolf Alpha", {"EX1_162", "TB_BaconUps_088"}, 1, Tribe::Beast, 2, 2, false, false, false, false, false, false, true},
    {"Mecharoo", {"BOT_445", "TB_BaconUps_002"}, 1, Tribe::Mech, 1, 1, false, false, false, false, false, false, true},
    {"Micro Machine", {"BGS_027", "TB_BaconUps_094"}, 1, Tribe::Mech, 1, 2, false, false, false, false, false, false, true},
    {"Murloc Tidecaller", {"EX1_509", "TB_BaconUps_011"}, 1, Tribe::Murloc, 1, 2, false, false, false, false, false, false, true},
    {"Murloc Tidehunter", {"EX1_506", "TB_BaconUps_003"}, 1, Tribe::Murloc, 2, 1, false, false, false, false, false, true, true},
    {"Righteous Protector", {"ICC_038", "(none)"}, 1, Tribe::None, 1, 1, true, true, false, false, false, false, true},
    {"Rockpool Hunter", {"UNG_073", "TB_BaconUps_061"}, 1, Tribe::Murloc, 2, 3, false, false, false, false, false, true, true},
    {"Selfless Hero", {"OG_221", "TB_BaconUps_014"}, 1, Tribe::None, 2, 1, false, false, false, false, false, false, true},
    {"Voidwalker", {"CS2_065", "TB_BaconUps_059t"}, 1, Tribe::Demon, 1, 3, true, false, false, false, false, false, true},
    {"Vulgar Homunculus", {"LOOT_013", "(none)"}, 1, Tribe::Demon, 2, 4, true, false, false, false, false, true, true},
    {"Wrath Weaver", {"BGS_004", "TB_BaconUps_079"}, 1, Tribe::None, 1, 1, false, false, false, false, false, false, true},
    {"Annoy-o-Tron", {"GVG_085", "(none)"}, 2, Tribe::Mech, 1, 2, true, true, false, false, false, false, true},
    {"Harvest Golem", {"EX1_556", "TB_BaconUps_006"}, 2, Tribe::Mech, 2, 3, false, false, false, false, false, false, true},
    {"Kaboom Bot", {"BOT_606", "TB_BaconUps_028"}, 2, Tribe::Mech, 2, 2, false, false, false, false, false, false, true},
    {"Kindly Grandmother", {"KAR_005", "TB_BaconUps_004"}, 2, Tribe::Beast, 1, 1, false, false, false, false, false, false, true},
    {"Metaltooth Leaper", {"GVG_048", "TB_BaconUps_066"}, 2, Tribe::Mech, 3, 3, false, false, false, false, false, true, true},
    {"Mounted Raptor", {"BGS_025", "TB_BaconUps_019"}, 2, Tribe::Beast, 3, 2, false, false, false, false, false, false, true},
    {"Murloc Warleader", {"EX1_507", "TB_BaconUps_008"}, 2, Tribe::Murloc, 3, 3, false, false, false, false, false, false, true},
    {"Nathrezim Overseer", {"BGS_001", "TB_BaconUps_062"}, 2, Tribe::Demon, 2, 4, false, false, false, false, false, true, true},
    {"Old Murk-Eye", {"EX1_062", "TB_BaconUps_036"}, 2, Tribe::Murloc, 2, 4, false, false, false, false, false, false, true},
    {"Pogo-Hopper", {"BGS_028", "TB_BaconUps_077"}, 2, Tribe::Mech, 1, 1, false, false, false, false, false, true, true},
    {"Rat Pack", {"CFM_316", "TB_BaconUps_027"}, 2, Tribe::Beast, 2, 2, false, false, false, false, false, false, true},
    {"Scavenging Hyena", {"EX1_531", "TB_BaconUps_043"}, 2, Tribe::Beast, 2, 2, false, false, false, false, false, false, true},
    {"Shielded Minibot", {"GVG_058", "(none)"}, 2, Tribe::Mech, 2, 2, false, true, false, false, false, false, true},
    {"Spawn of N'Zoth", {"OG_256", "TB_BaconUps_025"}, 2, Tribe::None, 2, 2, false, false, false, false, false, false, true},
    {"Zoobot", {"KAR_095", "TB_BaconUps_063"}, 2, Tribe::Mech, 3, 3, false, false, false, false, false, true, true},
    {"Cobalt Guardian", {"GVG_062", "(none)"}, 3, Tribe::Mech, 6, 3, false, false, false, false, false, false, true},
    {"Coldlight Seer", {"EX1_103", "TB_BaconUps_064"}, 3, Tribe::Murloc, 2, 3, false, false, false, false, false, true, true},
    {"Crowd Favorite", {"AT_121", "TB_BaconUps_037"}, 3, Tribe::None, 4, 4, false, false, false, false, false, false, true},
    {"Crystalweaver", {"CFM_610", "TB_BaconUps_070"}, 3, Tribe::None, 5, 4, false, false, false, false, false, true, true},
    {"Floating Watcher", {"GVG_100", "TB_BaconUps_101"}, 3, Tribe::Demon, 4, 4, false, false, false, false, false, false, true},
    {"Houndmaster", {"DS1_070", "TB_BaconUps_068"}, 3, Tribe::None, 4, 3, false, false, false, false, false, true, true},
    {"Imp Gang Boss", {"BRM_006", "TB_BaconUps_030"}, 3, Tribe::Demon, 2, 4, false, false, false, false, false, false, true},
    {"Infested Wolf", {"OG_216", "TB_BaconUps_026"}, 3, Tribe::Beast, 3, 3, false, false, false, false, false, false, true},
    {"Khadgar", {"DAL_575", "TB_BaconUps_034"}, 3, Tribe::None, 2, 2, false, false, false, false, false, false, true},
    {"Pack Leader", {"BGS_017", "TB_BaconUps_086"}, 3, Tribe::None, 3, 3, false, false, false, false, false, false, true},
    {"Phalanx Commander", {"ULD_179", "TB_BaconUps_038"}, 3, Tribe::None, 4, 5, false, false, false, false, false, false, true},
    {"Piloted Shredder", {"BGS_023", "TB_BaconUps_035"}, 3, Tribe::Mech, 4, 3, false, false, false, false, false, false, true},
    {"Psych-o-Tron", {"OG_145", "(none)"}, 3, Tribe::Mech, 3, 4, true, true, false, false, false, false, true},
    {"Replicating Menace", {"BOT_312", "TB_BaconUps_032"}, 3, Tribe::Mech, 3, 1, false, false, false, false, false, false, true},
    {"Screwjank Clunker", {"GVG_055", "TB_BaconUps_069"}, 3, Tribe::Mech, 2, 5, false, false, false, false, false, true, true},
    {"Shifter Zerus", {"BGS_029", "TB_BaconUps_095"}, 3, Tribe::None, 1, 1, false, false, false, false, false, false, true},
    {"Soul Juggler", {"BGS_002", "TB_BaconUps_075"}, 3, Tribe::None, 3, 3, false, false, false, false, false, false, true},
    {"The Beast", {"EX1_577", "TB_BaconUps_042"}, 3, Tribe::Beast, 9, 7, false, false, false, false, false, false, true},
    {"Tortollan Shellraiser", {"UNG_037", "TB_BaconUps_031"}, 3, Tribe::None, 2, 6, true, false, false, false, false, false, true},
    {"Annoy-o-Module", {"BOT_911", "TB_BaconUps_099"}, 4, Tribe::Mech, 2, 4, true, true, false, false, false, false, true},
    {"Bolvar, Fireblood", {"ICC_858", "TB_BaconUps_047"}, 4, Tribe::None, 1, 7, false, true, false, false, false, false, true},
    {"Cave Hydra", {"LOOT_078", "(none)"}, 4, Tribe::Beast, 2, 4, false, false, false, false, true, false, true},
    {"Defender of Argus", {"EX1_093", "TB_BaconUps_009"}, 4, Tribe::None, 2, 3, false, false, false, false, false, true, true},
    {"Festeroot Hulk", {"GIL_655", "TB_BaconUps_033"}, 4, Tribe::None, 2, 7, false, false, false, false, false, false, true},
    {"Iron Sensei", {"GVG_027", "TB_BaconUps_044"}, 4, Tribe::Mech, 2, 2, false, false, false, false, false, false, true},
    {"Mechano-Egg", {"BOT_537", "TB_BaconUps_039"}, 4, Tribe::Mech, 0, 5, false, false, false, false, false, false, true},
    {"Menagerie Magician", {"KAR_702", "TB_BaconUps_073"}, 4, Tribe::None, 4, 4, false, false, false, false, false, true, true},
    {"Piloted Sky Golem", {"BGS_024", "TB_BaconUps_050"}, 4, Tribe::Mech, 6, 4, false, false, false, false, false, false, true},
    {"Security Rover", {"BOT_218", "TB_BaconUps_041"}, 4, Tribe::Mech, 2, 6, false, false, false, false, false, false, true},
    {"Siegebreaker", {"EX1_185", "TB_BaconUps_053"}, 4, Tribe::Demon, 5, 8, true, false, false, false, false, false, true},
    {"The Boogeymonster", {"OG_300", "TB_BaconUps_058"}, 4, Tribe::None, 6, 7, false, false, false, false, false, false, true},
    {"Toxfin", {"DAL_077", "(none)"}, 4, Tribe::Murloc, 1, 2, false, false, false, false, false, true, true},
    {"Virmen Sensei", {"CFM_816", "TB_BaconUps_074"}, 4, Tribe::None, 4, 5, false, false, false, false, false, true, true},
    {"Annihilan Battlemaster", {"BGS_010", "TB_BaconUps_083"}, 5, Tribe::Demon, 3, 1, false, false, false, false, false, true, true},
    {"Baron Rivendare", {"FP1_031", "TB_BaconUps_055"}, 5, Tribe::None, 1, 7, false, false, false, false, false, false, true},
    {"Brann Bronzebeard", {"LOE_077", "TB_BaconUps_045"}, 5, Tribe::None, 2, 4, false, false, false, false, false, false, true},
    {"Goldrinn, the Great Wolf", {"BGS_018", "TB_BaconUps_085"}, 5, Tribe::Beast, 4, 4, false, false, false, false, false, false, true},
    {"Ironhide Direhorn", {"TRL_232", "TB_BaconUps_051"}, 5, Tribe::Beast, 7, 7, false, false, false, false, false, false, true},
    {"Junkbot", {"GVG_106", "TB_BaconUps_046"}, 5, Tribe::Mech, 1, 5, false, false, false, false, false, false, true},
    {"King Bagurgle", {"BGS_030", "TB_BaconUps_100"}, 5, Tribe::Murloc, 6, 3, false, false, false, false, false, true, true},
    {"Lightfang Enforcer", {"BGS_009", "TB_BaconUps_082"}, 5, Tribe::None, 2, 2, false, false, false, false, false, false, true},
    {"Mal'Ganis", {"GVG_021", "TB_BaconUps_060"}, 5, Tribe::Demon, 9, 7, false, false, false, false, false, false, true},
    {"Primalfin Lookout", {"BGS_020", "TB_BaconUps_089"}, 5, Tribe::Murloc, 3, 2, false, false, false, false, false, true, true},
    {"Sated Threshadon", {"UNG_010", "TB_BaconUps_052"}, 5, Tribe::Beast, 5, 7, false, false, false, false, false, false, true},
    {"Savannah Highmane", {"EX1_534", "TB_BaconUps_049"}, 5, Tribe::Beast, 6, 5, false, false, false, false, false, false, true},
    {"Strongshell Scavenger", {"ICC_807", "TB_BaconUps_072"}, 5, Tribe::None, 2, 3, false, false, false, false, false, true, true},
    {"Voidlord", {"LOOT_368", "TB_BaconUps_059"}, 5, Tribe::Demon, 3, 9, true, false, false, false, false, false, true},
    {"Foe Reaper 4000", {"GVG_113", "(none)"}, 6, Tribe::Mech, 6, 9, false, false, false, false, true, false, true},
    {"Gentle Megasaur", {"BGS_031", "TB_BaconUps_084"}, 6, Tribe::Beast, 5, 4, false, false, false, false, false, true, true},
    {"Ghastcoiler", {"BGS_008", "TB_BaconUps_057"}, 6, Tribe::Beast, 7, 7, false, false, false, false, false, false, true},
    {"Kangor's Apprentice", {"BGS_012", "TB_BaconUps_087"}, 6, Tribe::None, 3, 6, false, false, false, false, false, false, true},
    {"Maexxna", {"FP1_010", "(none)"}, 6, Tribe::Beast, 2, 8, false, false, true, false, false, false, true},
    {"Mama Bear", {"BGS_021", "TB_BaconUps_090"}, 6, Tribe::Beast, 4, 4, false, false, false, false, false, false, true},
    {"Sneed's Old Shredder", {"BGS_006", "TB_BaconUps_080"}, 6, Tribe::Mech, 5, 7, false, false, false, false, false, false, true},
    {"Zapp Slywick", {"BGS_022", "(none)"}, 6, Tribe::None, 7, 10, false, false, false, true, false, false, true},
    {"Amalgam", {"TB_BaconShop_HP_033t", "(none)"}, 1, Tribe::All, 1, 1, false, false, false, false, false, false, false},
    {"Big Bad Wolf", {"KAR_005a", "TB_BaconUps_004t"}, 1, Tribe::Beast, 3, 2, false, false, false, false, false, false, false},
    {"Damaged Golem", {"skele21", "TB_BaconUps_006t"}, 1, Tribe::Mech, 2, 1, false, false, false, false, false, false, false},
    {"Emperor Cobra", {"EX1_170", "(none)"}, 1, Tribe::Beast, 2, 3, false, false, true, false, false, false, false},
    {"Finkle Einhorn", {"EX1_finkle", "(none)"}, 1, Tribe::None, 3, 3, false, false, false, false, false, false, false},
    {"Guard Bot", {"BOT_218t", "TB_BaconUps_041t"}, 1, Tribe::Mech, 2, 3, true, false, false, false, false, false, false},
    {"Hench-Clan Squire", {"DAL_743t", "(none)"}, 1, Tribe::Murloc, 1, 1, false, false, false, false, false, false, false},
    {"Hyena", {"EX1_534t", "TB_BaconUps_049t"}, 1, Tribe::Beast, 2, 2, false, false, false, false, false, false, false},
    {"Imp", {"BRM_006t", "TB_BaconUps_030t"}, 1, Tribe::Demon, 1, 1, false, false, false, false, false, false, false},
    {"Ironhide Runt", {"TRL_232t", "TB_BaconUps_051t"}, 1, Tribe::Beast, 5, 5, false, false, false, false, false, false, false},
    {"Jo-E Bot", {"BOT_445t", "TB_BaconUps_002t"}, 1, Tribe::Mech, 1, 1, false, false, false, false, false, false, false},
    {"Microbot", {"BOT_312t", "TB_BaconUps_032t"}, 1, Tribe::Mech, 1, 1, false, false, false, false, false, false, false},
    {"Murloc Scout", {"EX1_506a", "TB_BaconUps_003t"}, 1, Tribe::Murloc, 1, 1, false, false, false, false, false, false, false},
    {"Plant", {"UNG_999t2t1", "(none)"}, 1, Tribe::None, 1, 1, false, false, false, false, false, false, false},
    {"Primalfin", {"UNG_201t", "TB_BaconUps_052t"}, 1, Tribe::Murloc, 1, 1, false, false, false, false, false, false, false},
    {"Rat", {"CFM_316t", "TB_BaconUps_027t"}, 1, Tribe::Beast, 1, 1, false, false, false, false, false, false, false},
    {"Robosaur", {"BOT_537t", "TB_BaconUps_039t"}, 1, Tribe::Mech, 8, 8, false, false, false, false, false, false, false},
    {"Safeguard", {"DAL_088", "TB_BaconUps_040"}, 1, Tribe::Mech, 4, 5, true, false, false, false, false, false, false},
    {"Snake", {"EX1_554t", "(none)"}, 1, Tribe::Beast, 1, 1, false, false, false, false, false, false, false},
    {"Spider", {"OG_216a", "TB_BaconUps_026t"}, 1, Tribe::Beast, 1, 1, false, false, false, false, false, false, false},
    {"Tabbycat", {"CFM_315t", "TB_BaconUps_093t"}, 1, Tribe::Beast, 1, 1, false, false, false, false, false, false, false},
    {"Vault Safe", {"DAL_088t2", "TB_BaconUps_040t"}, 1, Tribe::Mech, 0, 5, true, false, false, false, false, false, false},
    {"Nightmare Amalgam", {"GIL_681", "(none)"}, 2, Tribe::All, 3, 4, false, false, false, false, false, false, false},
    {"Pre-nerf Mama Bear", {"(none)", "(none)"}, 6, Tribe::Beast, 5, 5, false, false, false, false, false, false, false},
};

// -----------------------------------------------------------------------------
// Lists of minions
// -----------------------------------------------------------------------------

static const MinionType one_cost_minions[] = {
    MinionType::Alleycat,
    MinionType::Mecharoo,
    MinionType::MurlocTidecaller,
    MinionType::RighteousProtector,
    MinionType::SelflessHero,
    MinionType::Voidwalker,
    MinionType::WrathWeaver,
    MinionType::PogoHopper,
    MinionType::ShifterZerus,
    MinionType::Toxfin,
};

static const MinionType two_cost_minions[] = {
    MinionType::DireWolfAlpha,
    MinionType::MicroMachine,
    MinionType::MurlocTidehunter,
    MinionType::RockpoolHunter,
    MinionType::VulgarHomunculus,
    MinionType::AnnoyOTron,
    MinionType::KindlyGrandmother,
    MinionType::ScavengingHyena,
    MinionType::ShieldedMinibot,
    MinionType::Khadgar,
};

static const MinionType four_cost_minions[] = {
    MinionType::OldMurkEye,
    MinionType::CrowdFavorite,
    MinionType::Crystalweaver,
    MinionType::Houndmaster,
    MinionType::InfestedWolf,
    MinionType::PilotedShredder,
    MinionType::ReplicatingMenace,
    MinionType::ScrewjankClunker,
    MinionType::TortollanShellraiser,
    MinionType::AnnoyOModule,
    MinionType::DefenderOfArgus,
    MinionType::BaronRivendare,
    MinionType::StrongshellScavenger,
    MinionType::GentleMegasaur,
};

static const MinionType deathrattle_minions[] = {
    MinionType::Mecharoo,
    MinionType::SelflessHero,
    MinionType::HarvestGolem,
    MinionType::KaboomBot,
    MinionType::KindlyGrandmother,
    MinionType::MountedRaptor,
    MinionType::RatPack,
    MinionType::SpawnOfNZoth,
    MinionType::InfestedWolf,
    MinionType::PilotedShredder,
    MinionType::ReplicatingMenace,
    MinionType::TheBeast,
    MinionType::TortollanShellraiser,
    MinionType::MechanoEgg,
    MinionType::PilotedSkyGolem,
    MinionType::GoldrinnTheGreatWolf,
    MinionType::KingBagurgle,
    MinionType::SatedThreshadon,
    MinionType::SavannahHighmane,
    MinionType::Voidlord,
    MinionType::Ghastcoiler,
    MinionType::KangorsApprentice,
    MinionType::SneedsOldShredder,
};

static const MinionType legendary_minions[] = {
    MinionType::OldMurkEye,
    MinionType::Khadgar,
    MinionType::ShifterZerus,
    MinionType::TheBeast,
    MinionType::BolvarFireblood,
    MinionType::TheBoogeymonster,
    MinionType::BaronRivendare,
    MinionType::BrannBronzebeard,
    MinionType::GoldrinnTheGreatWolf,
    MinionType::KingBagurgle,
    MinionType::MalGanis,
    MinionType::FoeReaper4000,
    MinionType::Maexxna,
    MinionType::SneedsOldShredder,
    MinionType::ZappSlywick,
};

// -----------------------------------------------------------------------------
// Hero / hero power information
// -----------------------------------------------------------------------------

const HeroInfo gHeroInfo[] = {
    {"(none)", "(none)", {"(none)", "(none)"}},
    {"A. F. Kay", "TB_BaconShop_HERO_16", {"Procrastinate", "TB_BaconShop_HP_044"}},
    {"Arch-Villain Rafaam", "TB_BaconShop_HERO_45", {"I'll Take That!", "TB_BaconShop_HP_053"}},
    {"Bartendotron", "TB_BaconShop_HERO_31", {"Skilled Bartender", "TB_BaconShop_HP_009"}},
    {"Brann Bronzebeard", "TB_BaconShop_HERO_43", {"Battle Brand", "TB_BaconShop_HP_048"}},
    {"Dancin' Deryl", "TB_BaconShop_HERO_36", {"Hat Trick", "TB_BaconShop_HP_042"}},
    {"Edwin VanCleef", "TB_BaconShop_HERO_01", {"Sharpen Blades", "TB_BaconShop_HP_001"}},
    {"Elise Starseeker", "TB_BaconShop_HERO_42", {"Lead Explorer", "TB_BaconShop_HP_047"}},
    {"George the Fallen", "TB_BaconShop_HERO_15", {"Boon of Light", "TB_BaconShop_HP_010"}},
    {"Giantfin", "TB_BaconShop_HERO_19", {"Murloc King", "TB_BaconShop_HP_017"}},
    {"Infinite Toki", "TB_BaconShop_HERO_28", {"Temporal Tavern", "TB_BaconShop_HP_028"}},
    {"Kel'Thuzad", "TB_BaconShop_HERO_KelThuzad", {"(none)", "(none)"}},
    {"King Mukla", "TB_BaconShop_HERO_38", {"Bananarama", "TB_BaconShop_HP_038"}},
    {"Lich Baz'hial", "TB_BaconShop_HERO_25", {"Graveyard Shift", "TB_BaconShop_HP_049"}},
    {"Lord Jaraxxus", "TB_BaconShop_HERO_37", {"Bloodfury", "TB_BaconShop_HP_036"}},
    {"Millificent Manastorm", "TB_BaconShop_HERO_17", {"Tinker", "TB_BaconShop_HP_015"}},
    {"Nefarian", "TB_BaconShop_HERO_30", {"Nefarious Fire", "TB_BaconShop_HP_043"}},
    {"Patches the Pirate", "TB_BaconShop_HERO_18", {"Fire the Cannons!", "TB_BaconShop_HP_027"}},
    {"Patchwerk", "TB_BaconShop_HERO_34", {"All Patched Up", "TB_BaconShop_HP_035"}},
    {"Professor Putricide", "TB_BaconShop_HERO_20", {"Rage Potion", "TB_BaconShop_HP_018"}},
    {"Pyramad", "TB_BaconShop_HERO_39", {"Brick by Brick", "TB_BaconShop_HP_040"}},
    {"Queen Wagtoggle", "TB_BaconShop_HERO_14", {"Wax Warband", "TB_BaconShop_HP_037a"}},
    {"Ragnaros the Firelord", "TB_BaconShop_HERO_11", {"DIE, INSECTS!", "TB_BaconShop_HP_019"}},
    {"Shudderwock", "TB_BaconShop_HERO_23", {"Burbling", "TB_BaconShop_HP_022"}},
    {"Sindragosa", "TB_BaconShop_HERO_27", {"Stay Frosty", "TB_BaconShop_HP_014"}},
    {"Sir Finley Mrrgglton", "TB_BaconShop_HERO_40", {"Power Up!", "TB_BaconShop_HP_045"}},
    {"Sylvanas Windrunner", "TB_BaconShop_HERO_44", {"Banshee's Blessing", "TB_BaconShop_HP_050"}},
    {"The Curator", "TB_BaconShop_HERO_33", {"Menagerist", "TB_BaconShop_HP_033"}},
    {"The Great Akazamzarak", "TB_BaconShop_HERO_21", {"Prestidigitation", "TB_BaconShop_HP_020"}},
    {"The Lich King", "TB_BaconShop_HERO_22", {"Reborn Rites", "TB_BaconShop_HP_024"}},
    {"The Rat King", "TB_BaconShop_HERO_12", {"King of Beasts", "TB_BaconShop_HP_041a"}},
    {"Trade Prince Gallywix", "TB_BaconShop_HERO_10", {"Smart Savings", "TB_BaconShop_HP_008"}},
    {"Yogg-Saron, Hope's End", "TB_BaconShop_HERO_35", {"Puzzle Box", "TB_BaconShop_HP_039"}},
};
