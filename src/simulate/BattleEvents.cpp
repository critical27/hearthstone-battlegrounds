#include "Battle.h"

#define TWICE_IF_GOLDEN for (int count = 0; count < (deadMinion.isGolden() ? 2 : 1); ++count)

void Battle::onDeath(size_t player, const Minion& deadMinion, MinionIter& iter) {
    // reborn
    if (deadMinion.isReborn()) {
        summon(1, deadMinion.rebornCopy(), player, iter);
    }
    // deathrattle
    int count = board[player].extraDeathrattleCount();
    for (int i = 0; i < count; i++) {
        deathRattle(player, deadMinion, iter);
    }
    // onAllyDeath
    onAllyDeath(player, deadMinion);
}

// precondition and postcondition: iter points to next attack minion
void Battle::deathRattle(size_t player, const Minion& deadMinion, MinionIter& iter) {
    switch (deadMinion.minionType()) {
        // Tier 1
        case MinionType::Mecharoo:
            summon(1, Minion(MinionType::JoEBot, deadMinion.isGolden()), player, iter);
            break;
        case MinionType::SelflessHero:
            TWICE_IF_GOLDEN {
                board[player].giveRandomMinionDivineShield();
            }
            break;
        // Tier 2
        case MinionType::HarvestGolem:
            summon(1, Minion(MinionType::DamagedGolem, deadMinion.isGolden()), player, iter);
            break;
        case MinionType::KaboomBot:
            TWICE_IF_GOLDEN {
                board[1 - player].takeDamageRandom(4);
            }
            break;
        case MinionType::KindlyGrandmother:
            summon(1, Minion(MinionType::BigBadWolf, deadMinion.isGolden()), player, iter);
            break;
        case MinionType::MountedRaptor:
            TWICE_IF_GOLDEN {
                summon(1, Minion(HsDataUtils::randomOneCostMinion()), player, iter);
            }
            break;
        case MinionType::RatPack:
            summon(deadMinion.attack(), Minion(MinionType::Rat, deadMinion.isGolden()), player, iter);
            break;
        case MinionType::SpawnOfNZoth: {
            int amount = deadMinion.doubleIfGolden(1);
            board[player].buffAll(amount, amount);
            break;
        }
        // Tier 3
        case MinionType::InfestedWolf:
            summon(2, Minion(MinionType::Spider, deadMinion.isGolden()), player, iter);
            break;
        case MinionType::PilotedShredder:
            TWICE_IF_GOLDEN {
                summon(1, Minion(HsDataUtils::randomTwoCostMinion()), player, iter);
            }
            break;
        case MinionType::ReplicatingMenace:
            summon(3, Minion(MinionType::Microbot, deadMinion.isGolden()), player, iter);
            break;
        case MinionType::TortollanShellraiser: {
            int amount = deadMinion.doubleIfGolden(1);
            board[player].buffRandomMinion(amount, amount);
            break;
        }
        case MinionType::TheBeast:
            summon(1, MinionType::FinkleEinhorn, 1 - player);
            break;
        // Tier 4:
        case MinionType::PilotedSkyGolem:
            TWICE_IF_GOLDEN {
                summon(1, Minion(HsDataUtils::randomFourCostminion()), player, iter);
            }
            break;
        case MinionType::MechanoEgg:
            summon(1, Minion(MinionType::Robosaur, deadMinion.isGolden()), player, iter);
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
            summon(3, Minion(MinionType::MurlocScout, deadMinion.isGolden()), player, iter);
            break;
        case MinionType::SavannahHighmane:
            summon(2, Minion(MinionType::Hyena, deadMinion.isGolden()), player, iter);
            break;
        case MinionType::Voidlord:
            summon(3, Minion(MinionType::Voidwalker, deadMinion.isGolden()), player, iter);
            break;
        // Tier 6
        case MinionType::Ghastcoiler:
            TWICE_IF_GOLDEN {
                // we need to summon one by one, otherwise we would summon two same minion
                for (int i = 0; i < 2; i++) {
                    summon(1, Minion(HsDataUtils::randomDeathRattleMinion()), player, iter);
                }
            }
            break;
        case MinionType::KangorsApprentice: {
            auto deadMechs = board[player].deadMechs();
            for (int i = 0; i < deadMinion.doubleIfGolden(2) && i < deadMechs.size(); ++i) {
                summon(1, deadMechs[i], player, iter);
            }
            break;
        }
        case MinionType::SneedsOldShredder:
            TWICE_IF_GOLDEN {
                summon(1, Minion(HsDataUtils::randomLegendaryMinion()), player, iter);
            }
            break;
        default:
            break;
    }
}

// if we summon minions, we insert them before iter, and iter points to the newly add minion,
// which is the newly summoned one
void Battle::summon(int count, Minion minion, size_t player, MinionIter& iter) {
    CHECK(minion.minionType() != MinionType::None);
    auto& battleMinions = board[player].battleMinions();
    for (int i = 0; i < count && board[player].hasEmptySlot(); ++i) {
        size_t pos = iter - board[player].battleMinions().begin();
        VLOG(3) << "Board " << player << " insert " << minion << " at pos " << pos;
        iter = battleMinions.insert(iter, minion);
        onAllySummon(player, minion);
    }
}

void Battle::summon(int count, Minion minion, size_t player, size_t pos) {
    CHECK(minion.minionType() != MinionType::None);
    auto& battleMinions = board[player].battleMinions();
    for (int i = 0; i < count && board[player].hasEmptySlot(); ++i) {
        VLOG(3) << "Board " << player << " insert " << minion << " at pos " << pos;
        CHECK(battleMinions.begin() + pos <= battleMinions.end());
        battleMinions.insert(battleMinions.begin() + pos, minion);
        onAllySummon(player, minion);
    }
}

// for TheBeast, always insert at opponent's last empty slot
void Battle::summon(int count, Minion minion, size_t player) {
    CHECK(minion.minionType() != MinionType::None);
    auto& battleMinions = board[player].battleMinions();
    for (int i = 0; i < count && board[player].hasEmptySlot(); ++i) {
        battleMinions.emplace_back(minion);
        onAllySummon(player, minion);
    }
}

void Battle::onAllySummon(size_t player, Minion &summoned, bool played) {
    board[player].forEachMinion([&] (Minion& m) { m.onAllySummon(this, player, summoned, played); });
}

void Battle::onAllyBreakDivineShield(size_t player) {
    board[player].forEachMinion([player, this] (Minion& m) { m.onAllyBreakDivineShield(this, player); });
}

void Battle::onAllyAttack(size_t player) {
    board[player].forEachMinion([player, this] (Minion& m) { m.onAllyAttack(this, player); });
}

void Battle::onAllyDeath(size_t player, const Minion& deadMinion) {
    board[player].forEachMinion([&] (Minion& m) { m.onAllyDeath(this, player, deadMinion); });
}
