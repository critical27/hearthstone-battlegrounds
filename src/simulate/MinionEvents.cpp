#include "Battle.h"

#define TWICE_IF_GOLDEN for (int i = 0; i < (deadMinion.isGolden() ? 2 : 1); ++i)

void Minion::onAllySummon(Battle* battle, size_t player, Minion& summoned, bool played) {
    switch (minionType_) {
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
        case MinionType::MamaBear:
            if (summoned.isTribe(Tribe::Beast)) {
                summoned.buff(doubleIfGolden(4), doubleIfGolden(4));
            }
            break;
        case MinionType::PreNerfMamaBear:
            if (summoned.isTribe(Tribe::Beast)) {
                summoned.buff(doubleIfGolden(5), doubleIfGolden(5));
            }
            break;
        default:
            break;
    }
}

void Minion::onAllyAttack(Battle* battle, size_t player) {
    CHECK_NOTNULL(battle);
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
    switch (minionType_) {
        case MinionType::BolvarFireblood:
            buff(doubleIfGolden(2), 0);
            break;
        default:
            break;
    }
}

void Minion::onAllyDeath(Battle *battle, size_t player, const Minion& deadMinion) {
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
    switch (minionType_) {
        case MinionType::ImpGangBoss:
            // Note: summons to the right
            battle->summon(1, Minion(MinionType::Imp, golden_), player, pos+1);
            break;
        case MinionType::SecurityRover:
            battle->summon(1, Minion(MinionType::GuardBot, golden_), player, pos+1);
            break;
        default:
            break;
    }
}

void Minion::onKill(Battle* battle, size_t player) {
    CHECK_NOTNULL(battle);
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
