#include "Battle.h"

#define TWICE_IF_GOLDEN for (int i = 0; i < (deadMinion.isGolden() ? 2 : 1); ++i)

void Minion::onAllySummon(Battle* battle, size_t player, Minion& summoned, bool played) {
    CHECK_NOTNULL(battle);
    if (!isAlive()) {
        return;
    }
    switch (minionType_) {
        // Tier 1
        case MinionType::MurlocTidecaller:
            if (summoned.isTribe(Tribe::Murloc)) {
                buff(doubleIfGolden(1), 0);
            }
            break;
        case MinionType::WrathWeaver:
            if (played) {
                if (summoned.isTribe(Tribe::Demon)) {
                    // todo: deal damage to hero
                    buff(doubleIfGolden(2), doubleIfGolden(2));
                }
            }
            break;
        // Tier 3
        case MinionType::CobaltGuardian:
            if (summoned.isTribe(Tribe::Mech)) {
                setDivineShield(true);
            }
            break;
        case MinionType::CrowdFavorite:
            if (played) {
                if (summoned.minionInfo_.battlecry_) {
                    buff(doubleIfGolden(1), doubleIfGolden(1));
                }
            }
            break;
        case MinionType::PackLeader:
            if (summoned.isTribe(Tribe::Beast)) {
                summoned.buff(doubleIfGolden(3), 0);
            }
            break;
        // Tier 6:
        case MinionType::MamaBear:
            if (summoned.isTribe(Tribe::Beast)) {
                summoned.buff(doubleIfGolden(4), doubleIfGolden(4));
            }
            break;
        default:
            break;
    }
}

void Minion::onAllyAttack(Battle* battle, size_t player) {
    CHECK_NOTNULL(battle);
    if (!isAlive()) {
        return;
    }
    // also add attack after FesterootHulk attacked
    switch (minionType_) {
        case MinionType::FesterootHulk:
            buff(doubleIfGolden(1), 0);
            break;
        default:
            break;
    }
}

void Minion::onAllyBreakDivineShield(Battle* battle, size_t player) {
    CHECK_NOTNULL(battle);
    if (!isAlive()) {
        return;
    }
    switch (minionType_) {
        case MinionType::BolvarFireblood:
            buff(doubleIfGolden(2), 0);
            break;
        default:
            break;
    }
}

void Minion::onAllyDeath(Battle *battle, size_t player, const Minion& deadMinion) {
    CHECK_NOTNULL(battle);
    if (!isAlive()) {
        return;
    }
    switch (minionType_) {
        case MinionType::ScavengingHyena:
            if (deadMinion.isTribe(Tribe::Beast)) {
                buff(doubleIfGolden(2), doubleIfGolden(1));
            }
            break;
        case MinionType::SoulJuggler:
            if (deadMinion.isTribe(Tribe::Demon)) {
                TWICE_IF_GOLDEN {
                    battle->player(1 - player).takeDamageRandom(3);
                }
            }
            break;
        case MinionType::Junkbot:
            if (deadMinion.isTribe(Tribe::Mech)) {
                buff(doubleIfGolden(2), doubleIfGolden(2));
            }
            break;
        default:
            break;
    }
}

void Minion::onDamaged(Battle* battle, size_t player, size_t pos) {
    CHECK_NOTNULL(battle);
    // we don't need to check whether isAlive or not
    // 1. summon to the right.
    // 2. then check for death
    switch (minionType_) {
        case MinionType::ImpGangBoss:
            battle->summon(1, Minion(MinionType::Imp, golden_), player, pos + 1);
            break;
        case MinionType::SecurityRover:
            battle->summon(1, Minion(MinionType::GuardBot, golden_), player, pos + 1);
            break;
        default:
            break;
    }
}

void Minion::onKill(Battle* battle, size_t player) {
    CHECK_NOTNULL(battle);
    if (!isAlive()) {
        return;
    }
    switch (minionType_) {
        case MinionType::TheBoogeymonster:
            buff(doubleIfGolden(2), doubleIfGolden(2));
            break;
        default:
            break;
    }
}

void Minion::onOverKill(Battle* battle, size_t player, size_t pos) {
    CHECK_NOTNULL(battle);
    switch (minionType_) {
        case MinionType::IronhideDirehorn:
            // forward iter so that new minion is the next attacker
            battle->summon(1, Minion(MinionType::IronhideRunt, golden_), player, pos + 1);
            break;
        default:
            break;
    }
}

bool Minion::computeAuras(size_t pos, BattleMinions* you, BattleMinions* opponent) {
    switch (minionType_) {
        case MinionType::DireWolfAlpha:
            you->auraBuffAdjacent(doubleIfGolden(1), 0, pos);
            return true;
        case MinionType::MurlocWarleader:
            you->auraBuffOthersIf(doubleIfGolden(2), 0, pos, [] (Minion const& m) { return m.isTribe(Tribe::Murloc); });
            return true;
        case MinionType::OldMurkEye: {
            // count murlocs for both players, exclude itself
            int count = -1;
            count += you->countIf([] (const Minion& m) { return m.isTribe(Tribe::Murloc); });
            count += opponent->countIf([] (const Minion& m) { return m.isTribe(Tribe::Murloc); });
            if (count > 0) {
                auraBuff(doubleIfGolden(count), 0);
            }
            return true;
        }
        case MinionType::PhalanxCommander:
            you->auraBuffOthersIf(doubleIfGolden(2), 0, pos, [](Minion const& m) { return m.isTaunt(); });
            return true;
        case MinionType::Siegebreaker:
            you->auraBuffOthersIf(doubleIfGolden(1), 0, pos, [](Minion const& m) { return m.isTribe(Tribe::Demon); });
            return true;
        case MinionType::MalGanis:
            you->auraBuffOthersIf(doubleIfGolden(2), doubleIfGolden(2), pos,
                                  [] (Minion const& m) { return m.isTribe(Tribe::Demon); });
            return true;
        default:
            return false;
    }
    return false;
}

