#include "Battle.h"
#include <glog/logging.h>
#include "utils/enums.h"
#include "utils/random.h"

std::ostream& operator<<(std::ostream& os, const Battle& battle) {
    os << battle.board[0];
    os << "VS" << std::endl;
    os << battle.board[1];
    return os;
}

void Battle::prepare() {
    // todo: reset both board if necessary

    // decide which player attacks first, 0 is you, 1 is opponent
    if (!rand(0, 1)) {
        yourTurn_ = true;
        isMainPlayer_ = true;
    } else {
        yourTurn_ = false;
        isMainPlayer_ = false;
    }

    // todo: hero_power
    // todo: aurus
}

void Battle::run() {
    prepare();
    while (!done()) {
        attack();
        break;
    }
}

void Battle::attack() {
    BattleMinions& active = yourTurn_ ? board[0] : board[1];
    BattleMinions& passive = yourTurn_ ? board[1] : board[0];
    size_t atkIdx = active.nextAttackerIndex();
    if (atkIdx != -1) {
        Minion& attacker = active.nextAttacker();
        if (attacker.minionType() != MinionType::ZappSlywick) {
            size_t defIdx = passive.nextDefenderIndex();
            // todo: cleave
            if (attacker.isCleave()) {
            }
            VLOG(1) << active[atkIdx] << " attack " << passive[defIdx];
            doAttack(active, atkIdx, passive, defIdx);
        } else {
            // todo
        }
        // todo: onAttackAndKill
        checkForDeath();
    }
}

void Battle::doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx) {
    Minion& attacker = active[atkIdx];
    Minion& defender = passive[defIdx];

    // todo: kill and overkill
    int kill = 0, overkill = 0;
    damage(defender, attacker.attack(), attacker.isPoison(), kill, overkill);
    damage(attacker, defender.attack(), defender.isPoison(), kill, overkill);
}

void Battle::damage(Minion& defender, int amount, bool poison, int& kill, int& overkill) {
    assert(amount > 0);
    if (defender.isDivineShield()) {
        defender.setDivineShield(false);
        // todo: onBreakDivineShield
    } else {
        defender.setHealth(defender.health() - amount);
        if (defender.health() > 0 && poison) {
            defender.setHealth(0);
        }
        if (defender.health() < 0) {
            overkill++;
            kill++;
        } else if (defender.health() == 0) {
            kill++;
        }
        // todo: onDamaged
    }
}

void Battle::checkForDeath() {
    int deadCount = 0;
    do {
        deadCount = 0;
        for (size_t boardIdx = 0; boardIdx < board.size(); boardIdx++) {
            // collect all dead minion
            auto& minions = board[boardIdx].battleMinions();
            std::vector<size_t> deadIdx;
            std::vector<Minion> deadMinion;
            for (auto iter = minions.begin(); iter != minions.end(); ) {
                if (!iter->isAlive()) {
                    VLOG(2) << iter->toSimpleString() << " is dead";
                    deadCount++;
                    onDeath(boardIdx, iter);
                    minions.erase(iter);
                    iter++;
                    /*
                    deadIdx.emplace_back(i);
                    deadMinion.emplace_back(minions[i]);
                     */
                }
            }
        }
    } while (deadCount != 0);
}

bool Battle::done() {
    // return true when one BattleMinions is empty
    return board[0].hasAliveMinion() && board[1].hasAliveMinion();
}
