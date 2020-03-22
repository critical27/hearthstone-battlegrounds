#include "Battle.h"

#define TWICE_IF_GOLDEN for (int count = 0; count < (deadMinion.isGolden() ? 2 : 1); ++count)

void Battle::onBattleStart(size_t player) {
    board_[player].forEachMinion([player, this] (Minion& m) {
        m.onBattleStart(this, player);
    });
}

int Battle::onDeath(size_t player, const Minion& deadMinion, size_t idx) {
    int result = 0;
    // 1. deathrattle
    int count = board_[player].extraDeathrattleCount();
    for (int i = 0; i < count; i++) {
        result += deathRattle(player, deadMinion, idx);
    }
    // 2. reborn
    if (deadMinion.isReborn()) {
        result += summon(1, deadMinion.rebornCopy(), player, idx);
    }
    // 3. onAllyDeath
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
                board_[player].giveRandomMinionDivineShield();
            }
            break;
        case MinionType::FiendishServant:
            TWICE_IF_GOLDEN {
                board_[player].buffRandomMinion(deadMinion.attack(), 0);
            }
            break;
        // Tier 2
        case MinionType::HarvestGolem:
            result += summon(1, Minion(MinionType::DamagedGolem, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::KaboomBot:
            TWICE_IF_GOLDEN {
                dealDamageToRandomly(1 - player, 4);
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
            board_[player].forEachMinion([amount] (Minion& m) { m.buff(amount, amount); });
            break;
        }
        case MinionType::UnstableGhoul: {
            int amount = deadMinion.doubleIfGolden(1);
            for (size_t player = 0; player <= 1; player++) {
                for (size_t pos = 0; pos < board_[player].size(); pos++) {
                    // todo: do we need to judge isAlive?
                    dealDamageTo(player, pos, amount);
                }
            }
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
            board_[player].buffRandomMinion(amount, amount);
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
        case MinionType::SavannahHighmane:
            result += summon(2, Minion(MinionType::Hyena, deadMinion.isGolden()), player, idx);
            break;
        // Tier 5
        case MinionType::GoldrinnTheGreatWolf: {
            int amount = deadMinion.doubleIfGolden(4);
            board_[player].forEachMinion([amount] (Minion& m) { m.buff(amount, amount); },
                                        [] (const Minion& m) -> bool { return m.isTribe(Tribe::Beast); });
            break;
        }
        case MinionType::KingBagurgle: {
            int amount = deadMinion.doubleIfGolden(2);
            board_[player].forEachMinion([amount] (Minion& m) { m.buff(amount, amount); },
                                        [] (const Minion& m) -> bool { return m.isTribe(Tribe::Murloc); });
            break;
        }
        case MinionType::SatedThreshadon:
            result += summon(3, Minion(MinionType::MurlocScout, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::Voidlord:
            result += summon(3, Minion(MinionType::Voidwalker, deadMinion.isGolden()), player, idx);
            break;
        case MinionType::SneedsOldShredder:
            TWICE_IF_GOLDEN {
                result += summon(1, Minion(HsDataUtils::randomLegendaryMinion()), player, idx);
            }
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
            auto deadMechs = board_[player].deadMechs();
            for (int i = 0; i < deadMinion.doubleIfGolden(2) && i < deadMechs.size(); ++i) {
                result += summon(1, deadMechs[i], player, idx);
            }
            break;
        }
        case MinionType::NadinaTheRed:
            board_[player].forEachMinion([] (Minion& m) { m.setDivineShield(true); },
                                         [] (const Minion& m) -> bool { return m.isTribe(Tribe::Dragon); });
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
    auto& battleMinions = board_[player].battleMinions();
    int extra = board_[player].extraSummonCount();
    while (count && board_[player].hasEmptySlot()) {
        // need to copy the value, otherwise, it could be affected by onAllySummon
        Minion summoned = minion;
        VLOG(3) << "Board " << player << " insert " << minion << " at pos " << pos;
        CHECK(battleMinions.begin() + pos <= battleMinions.end());
        auto iter = battleMinions.insert(battleMinions.begin() + pos, summoned);
        onAllySummon(player, *iter);
        ++pos;
        ++result;
        --count;

        // trigger Khadgar after it has called onAllySummon
        int khadgar = extra;
        while (khadgar > 1 && board_[player].hasEmptySlot()) {
            iter = battleMinions.insert(battleMinions.begin() + pos, *iter);
            onAllySummon(player, *iter);
            ++pos;
            ++result;
            --khadgar;
        }
    }
    computeAurs();
    return result;
}

// for TheBeast, always insert at opponent's last empty slot
int Battle::summon(int count, Minion minion, size_t player) {
    size_t pos = board_[player].size();
    return summon(count, minion, player, pos);
}

void Battle::onAllySummon(size_t player, Minion &summoned, bool played) {
    board_[player].forEachMinion([&] (Minion& m) {
        m.onAllySummon(this, player, summoned, played);
    });
    VLOG(4) << "onAllySummon " << summoned;
}

void Battle::onAllyBreakDivineShield(size_t player) {
    board_[player].forEachMinion([player, this] (Minion& m) {
        m.onAllyBreakDivineShield(this, player);
    });
}

void Battle::onAllyAttack(size_t player) {
    board_[player].forEachMinion([player, this] (Minion& m) {
        m.onAllyAttack(this, player);
    });
}

void Battle::onAllyDeath(size_t player, const Minion& deadMinion) {
    board_[player].forEachMinion([&] (Minion& m) {
        m.onAllyDeath(this, player, deadMinion);
    });
}

void Battle::onAllyKill(size_t player, Minion& minion, int kill) {
    // this only works for WaxriderTogwaggle, so we judge whether attacker is dragon
    if (minion.isTribe(Tribe::Dragon)) {
        board_[player].forEachMinion([player, kill, this] (Minion& m) {
            m.onAllyKill(this, player, kill);
        });
    }
}

void Battle::dealDamageTo(size_t player, size_t pos, int amount) {
    board_[player][pos].takeDamage(this, player, pos, amount);
}

void Battle::dealDamageToRandomly(size_t player, int amount) {
    auto living = board_[player].livingMinions();
    if (!living.empty()) {
        auto picked = rand(0, living.size() - 1);
        dealDamageTo(player, picked, amount);
    }
}

// return true for overKill
bool Battle::dealDamageToLeftMost(size_t player, int amount) {
    for (size_t pos = 0; pos < board_[player].size(); pos++) {
        if (board_[player][pos].isAlive()) {
            dealDamageTo(player, pos, amount);
            return board_[player][pos].health() < 0;
        }
    }
    return false;
}
