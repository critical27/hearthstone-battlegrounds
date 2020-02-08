#include "Battle.h"

#define TWICE_IF_GOLDEN for (int count = 0; count < (deadMinion.isGolden() ? 2 : 1); ++count)

int Battle::onDeath(size_t player, const Minion& deadMinion, size_t idx) {
    int result = 0;
    // reborn
    if (deadMinion.isReborn()) {
        result += summon(1, deadMinion.rebornCopy(), player, idx);
    }
    // deathrattle
    int count = board[player].extraDeathrattleCount();
    for (int i = 0; i < count; i++) {
        result += deathRattle(player, deadMinion, idx);
    }
    // onAllyDeath
    onAllyDeath(player, deadMinion);
    return result;
}

// precondition and postcondition: iter points to next attack minion
int Battle::deathRattle(size_t player, const Minion& deadMinion, size_t idx) {
    int result = 0;
    switch (deadMinion.minionType()) {
        // Tier 1
        case MinionType::Mecharoo:
            result += summon(1, Minion(MinionType::JoEBot, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::SelflessHero:
            TWICE_IF_GOLDEN {
                board[player].giveRandomMinionDivineShield();
            }
            break;
        case MinionType::FiendishServant:
            TWICE_IF_GOLDEN {
                board[player].buffRandomMinion(deadMinion.attack(), 0);
            }
            break;
        // Tier 2
        case MinionType::HarvestGolem:
            result += summon(1, Minion(MinionType::DamagedGolem, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::KaboomBot:
            TWICE_IF_GOLDEN {
                board[1 - player].takeDamageRandom(4);
            }
            break;
        case MinionType::KindlyGrandmother:
            result += summon(1, Minion(MinionType::BigBadWolf, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::MountedRaptor:
            TWICE_IF_GOLDEN {
                result += summon(1, Minion(HsDataUtils::randomOneCostMinion()), player, idx);
            }
            break;
        case MinionType::RatPack:
            result += summon(deadMinion.attack(), Minion(MinionType::Rat, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::SpawnOfNZoth: {
            int amount = deadMinion.doubleIfGolden(1);
            board[player].forEachMinion([amount] (Minion& m) { m.buff(amount, amount); });
            break;
        }
        // Tier 3
        case MinionType::InfestedWolf:
            result += summon(2, Minion(MinionType::Spider, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::PilotedShredder:
            TWICE_IF_GOLDEN {
                result += summon(1, Minion(HsDataUtils::randomTwoCostMinion()), player, idx);
            }
            break;
        case MinionType::ReplicatingMenace:
            result += summon(3, Minion(MinionType::Microbot, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::TortollanShellraiser: {
            int amount = deadMinion.doubleIfGolden(1);
            board[player].buffRandomMinion(amount, amount);
            break;
        }
        case MinionType::TheBeast:
            result += summon(1, MinionType::FinkleEinhorn, 1 - player);
            break;
        case MinionType::Imprisoner:
            result += summon(1, Minion(MinionType::Imp, deadMinion.isGolden()), player, idx);
            break;
        // Tier 4:
        case MinionType::PilotedSkyGolem:
            TWICE_IF_GOLDEN {
                result += summon(1, Minion(HsDataUtils::randomFourCostminion()), player, idx);
            }
            break;
        case MinionType::MechanoEgg:
            result += summon(1, Minion(MinionType::Robosaur, deadMinion.isGolden()), player, idx);
            break;
        // Tier 5
        case MinionType::GoldrinnTheGreatWolf: {
            int amount = deadMinion.doubleIfGolden(4);
            board[player].forEachMinion([amount] (Minion& m) { m.buff(amount, amount); },
                                        [] (Minion& m) -> bool { return m.isTribe(Tribe::Beast); });
            break;
        }
        case MinionType::KingBagurgle: {
            int amount = deadMinion.doubleIfGolden(2);
            board[player].forEachMinion([amount] (Minion& m) { m.buff(amount, amount); },
                                        [] (Minion& m) -> bool { return m.isTribe(Tribe::Murloc); });
            break;
        }
        case MinionType::SatedThreshadon:
            result += summon(3, Minion(MinionType::MurlocScout, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::SavannahHighmane:
            result += summon(2, Minion(MinionType::Hyena, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::Voidlord:
            result += summon(3, Minion(MinionType::Voidwalker, deadMinion.isGolden()), player, idx);
            break;
        // Tier 6
        case MinionType::Ghastcoiler:
            TWICE_IF_GOLDEN {
                // we need to summon one by one, otherwise we would summon two same minion
                for (int i = 0; i < 2; i++) {
                    result += summon(1, Minion(HsDataUtils::randomDeathRattleMinion()), player, idx);
                }
            }
            break;
        case MinionType::KangorsApprentice: {
            auto deadMechs = board[player].deadMechs();
            for (int i = 0; i < deadMinion.doubleIfGolden(2) && i < deadMechs.size(); ++i) {
                result += summon(1, deadMechs[i], player, idx);
            }
            break;
        }
        case MinionType::SneedsOldShredder:
            TWICE_IF_GOLDEN {
                result += summon(1, Minion(HsDataUtils::randomLegendaryMinion()), player, idx);
            }
            break;
        default:
            break;
    }
    return result;
}

int Battle::summon(int count, Minion minion, size_t player, size_t pos) {
    // return value is actual the summoned count
    int result = 0;
    CHECK(minion.minionType() != MinionType::None);
    auto& battleMinions = board[player].battleMinions();
    for (; result < count && board[player].hasEmptySlot(); ++result) {
        // need to copy the value, otherwise, it could be affected by onAllySummon
        Minion summoned = minion;
        VLOG(3) << "Board " << player << " insert " << minion << " at pos " << pos;
        CHECK(battleMinions.begin() + pos <= battleMinions.end());
        auto iter = battleMinions.insert(battleMinions.begin() + pos, summoned);
        onAllySummon(player, *iter);
    }
    return result;
}

// for TheBeast, always insert at opponent's last empty slot
int Battle::summon(int count, Minion minion, size_t player) {
    // return value is actual the summoned count
    int result = 0;
    CHECK(minion.minionType() != MinionType::None);
    auto& battleMinions = board[player].battleMinions();
    for (; result < count && board[player].hasEmptySlot(); ++result) {
        // need to copy the value, otherwise, it could be affected by onAllySummon
        Minion summoned = minion;
        VLOG(3) << "Board " << player << " add " << minion << " at last";
        battleMinions.emplace_back(summoned);
        onAllySummon(player, battleMinions.back());
    }
    return result;
}

void Battle::onAllySummon(size_t player, Minion &summoned, bool played) {
    board[player].forEachMinion([&] (Minion& m) {
        m.onAllySummon(this, player, summoned, played);
    });
    VLOG(4) << "onAllySummon " << summoned;
}

void Battle::onAllyBreakDivineShield(size_t player) {
    board[player].forEachMinion([player, this] (Minion& m) {
        m.onAllyBreakDivineShield(this, player);
    });
}

void Battle::onAllyAttack(size_t player) {
    board[player].forEachMinion([player, this] (Minion& m) {
        m.onAllyAttack(this, player);
    });
}

void Battle::onAllyDeath(size_t player, const Minion& deadMinion) {
    board[player].forEachMinion([&] (Minion& m) {
        m.onAllyDeath(this, player, deadMinion);
    });
}
