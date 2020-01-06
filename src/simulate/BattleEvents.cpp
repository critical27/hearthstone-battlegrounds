#include "Battle.h"

#define TWICE_IF_GOLDEN for (int i = 0; i < (deadMinion.isGolden() ? 2 : 1); ++i)

// precondition and postcondition: iter points to next attack minion
void Battle::onDeath(size_t player, Minion& deadMinion, MinionIter& iter) {
    switch (deadMinion.minionType()) {
        // Tier 1
        case MinionType::Mecharoo:
            summon(1, Minion(MinionType::JoEBot, deadMinion.isGolden()), player, iter);
            break;
        /*
        case MinionType::SelflessHero:
            TWICE_IF_GOLDEN {
                board[player].give_random_deadMinion_divine_shield(rng, player);
            }
            break;
        // Tier 2
        case MinionType::HarvestGolem:
            summon(1, Minion(MinionType::DamagedGolem,deadMinion.isGolden()), player, pos);
            break;
        case MinionType::KaboomBot:
            TWICE_IF_GOLDEN {
                damage_random_deadMinion(1-player, 4);
            }
            break;
        case MinionType::KindlyGrandmother:
            summon(1, Minion(MinionType::BigBadWolf,deadMinion.isGolden()), player, pos);
            break;
        // todo:
        case MinionType::MountedRaptor:
            TWICE_IF_GOLDEN {
                summon(random_one_cost_deadMinion(rng, player), player, pos);
            }
            break;
        case MinionType::RatPack:
            summon(deadMinion.attack, Minion(MinionType::Rat, deadMinion.isGolden()), player, pos);
            break;
        case MinionType::SpawnOfNZoth:
            board[player].buffAll(deadMinion.double_if_golden(1), deadMinion.double_if_golden(1));
            break;
            // Tier 3
        case MinionType::InfestedWolf:
            summon(2, Minion(MinionType::Spider, deadMinion.isGolden()), player, pos);
            break;
        // todo:
        case MinionType::PilotedShredder:
            TWICE_IF_GOLDEN() {
                summon(random_two_cost_deadMinion(rng, player), player, pos);
            }
            break;
        case MinionType::ReplicatingMenace:
            summon(3, Minion(MinionType::Microbot, deadMinion.isGolden()), player, pos);
            break;
        case MinionType::TortollanShellraiser:
            int amount = deadMinion.double_if_golden(1);
            board[player].buffRandomMinion(amount, amount, rng, player);
            break;
        case MinionType::TheBeast:
            summon(MinionType::FinkleEinhorn, player);
            break;
        // Tier 4:
        // todo:
        case MinionType::PilotedSkyGolem:
            TWICE_IF_GOLDEN() {
                summon(random_four_cost_deadMinion(rng, player), player, pos);
            }
            break;
        // Tier 5
        case MinionType::GoldrinnTheGreatWolf:
            int amount = m.double_if_golden(4);
            board[player].buff_all_if(amount, amount, [](Minion const& x){return x.has_tribe(Tribe::Beast);});
            break;
        case MinionType::KingBagurgle:
            int amount = m.double_if_golden(2);
            board[player].buff_all_if(amount, amount, [](Minion const& x){return x.has_tribe(Tribe::Murloc);});
            break;
        case MinionType::MechanoEgg:
            summon(Minion(MinionType::Robosaur,m.isGolden()), player, pos);
            break;
        case MinionType::SatedThreshadon:
            summon_many(3, Minion(MinionType::MurlocScout,m.isGolden()), player, pos);
            break;
        case MinionType::SavannahHighmane:
            summon_many(2, Minion(MinionType::Hyena,m.isGolden()), player, pos);
            break;
            // Tier 6
        case MinionType::Ghastcoiler:
            for (int i=0; i<m.double_if_golden(2); ++i) {
                summon(random_deathrattle_deadMinion(rng, player), player, pos);
            }
            break;
        case MinionType::KangorsApprentice:
            for (int i=0; i<m.double_if_golden(2) && mechs_that_died[player][i].exists(); ++i) {
                summon(mechs_that_died[player][i].new_copy(), player, pos);
            }
            break;
        case MinionType::SneedsOldShredder:
            TWICE_IF_GOLDEN {
                summon(random_legendary_deadMinion(rng, player), player, pos);
            }
            break;
        */
        default:
            break;
    }
}

// if we summon minions, we insert them before iter, and iter points to the newly add minion,
// which is the newly summoned one
void Battle::summon(int count, const Minion& minion, size_t player, MinionIter& iter) {
    auto& battleMinions = board[player].battleMinions();
    for (int i = 0; i < count && board[player].hasEmptySlot(); ++i) {
        size_t pos = iter - board[player].battleMinions().begin();
        VLOG(2) << "Board " << player << " insert " << minion << " at pos " << pos;
        iter = battleMinions.insert(iter, minion);
        // todo:
        // onSummoned();
    }
}