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

int Battle::run() {
    prepare();
    int turn = 0;
    while (!done() && turn < 100) {
        attack();
        turn++;
        VLOG(1) << "Battle after " << turn << " turns:" << toString();
    }
    VLOG(1) << "Battle end after " << turn << " turns.";
    return result();
}

void Battle::attack() {
    BattleMinions& active = yourTurn_ ? board[0] : board[1];
    BattleMinions& passive = yourTurn_ ? board[1] : board[0];
    size_t player = yourTurn_ ? 0 : 1;
    size_t atkIdx = active.nextAttackerIndex();
    if (atkIdx != -1) {
        Minion& attacker = active.nextAttacker();
        if (attacker.minionType() != MinionType::ZappSlywick) {
            size_t defIdx = passive.nextDefenderIndex();
            // todo: cleave
            if (attacker.isCleave()) {
            }
            VLOG(1) << "Board " << player << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                    << " **attack** "
                    << "Board " << 1 - player << " minion " << defIdx << " " << passive[defIdx].toSimpleString();
            doAttack(active, atkIdx, passive, defIdx);
        } else {
            // todo
        }
        // todo: onAttackAndKill
        checkForDeath();
    }
    yourTurn_ = !yourTurn_;
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
        for (size_t player = 0; player < board.size(); player++) {
            // always
            auto& minions = board[player].battleMinions();
            for (auto iter = minions.begin(); iter != minions.end(); ) {
                if (!iter->isAlive()) {
                    VLOG(2) << "Board " << player << " " << iter->toSimpleString() << " is dead";
                    deadCount++;
                    // 1. remove the dead minion, so there would be at least a empty slot
                    // doodle: what about on damaged
                    auto deadMinion = *iter;
                    iter = minions.erase(iter);
                    // 2. death rattle, postcondition: iter points to next attack minion
                    onDeath(player, deadMinion, iter);
                    // get next element
                    if (iter != minions.end()) {
                        iter++;
                    }
                } else {
                    iter++;
                }
            }
        }
    } while (deadCount != 0);
}

bool Battle::done() {
    // return true when one BattleMinions is empty
    return !board[0].hasAliveMinion() && !board[1].hasAliveMinion();
}

// result > 0 if you win, < 0 if opponent win, 0 if tied
int Battle::result() {
    int result = board[0].remainingStars();
    if (result > 0) {
        return result;
    }
    result = board[1].remainingStars();
    if (result > 0) {
        return -result;
    }
    return 0;
}
