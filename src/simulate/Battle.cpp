#include "Battle.h"
#include <glog/logging.h>
#include "utils/Enums.h"
#include "utils/Random.h"

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
        coin_ = true;
        yourTurn_ = true;
    } else {
        coin_ = false;
        yourTurn_ = false;
    }

    // todo: hero_power
    // todo: aurus
}

int Battle::run() {
    prepare();
    while (!done() && turn_ < 100) {
        attack();
        VLOG(1) << "Battle after " << turn_ << " turns:";
        VLOG(1) << toString();
        nextTurn();
    }
    VLOG(1) << "Battle end after " << turn_ << " turns.";
    return result();
}

void Battle::attack() {
    attackPlayer_ = yourTurn_ ? 0 : 1;
    BattleMinions& active = attacker();
    BattleMinions& passive = defender();
    size_t atkIdx = active.nextAttackerIndex();
    if (atkIdx != -1) {
        Minion& attacker = active[atkIdx];
        singleAttack(active, passive, atkIdx);
        onAllyAttack(attackPlayer_);
        // wind fury
        if (attacker.isAlive() && attacker.isWindfury()) {
            singleAttack(active, passive, atkIdx);
            onAllyAttack(attackPlayer_);
        }
        checkForDeath();
    }
}

void Battle::singleAttack(BattleMinions& active, BattleMinions& passive, size_t atkIdx) {
    Minion& attacker = active[atkIdx];
    if (attacker.minionType() != MinionType::ZappSlywick) {
        size_t defIdx = passive.nextDefenderIndex();
        if (attacker.isCleave()) {
            auto adjacent = passive.getAdajacent(defIdx);
            doAttack(active, atkIdx, passive, defIdx, adjacent);
            VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString() << " [Cleave]"
                    << " **attack** "
                    << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << passive[defIdx].toSimpleString();
        } else {
            VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                    << " **attack** "
                    << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << passive[defIdx].toSimpleString();
            doAttack(active, atkIdx, passive, defIdx);
        }
    } else {
        size_t defIdx = passive.minionWithLowestAttack();
        VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                << " **attack** "
                << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << passive[defIdx].toSimpleString();
        doAttack(active, atkIdx, passive, defIdx);
    }
}

void Battle::doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx) {
    Minion& attacker = active[atkIdx];
    Minion& defender = passive[defIdx];

    int kill = 0, overkill = 0;
    damage(1 - attackPlayer_, defender, defIdx, attacker.isPoison(), overkill, kill, attacker.attack());
    damage(attackPlayer_, attacker, atkIdx, defender.isPoison(), overkill, kill, defender.attack());

    if (kill) {
        attacker.onKill(this, attackPlayer_);
    }
    if (overkill) {
        attacker.onOverKill(this, attackPlayer_, atkIdx);
    }
}

void Battle::doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx, std::vector<size_t> adjacent) {
    Minion& attacker = active[atkIdx];
    Minion& defender = passive[defIdx];

    int kill = 0, overkill = 0;
    damage(1 - attackPlayer_, defender, defIdx, attacker.isPoison(), overkill, kill, attacker.attack());
    for (auto idx : adjacent) {
        damage(1 - attackPlayer_, passive[idx], idx, attacker.isPoison(), overkill, kill, attacker.attack());
    }
    damage(attackPlayer_, attacker, atkIdx, defender.isPoison(), overkill, kill, defender.attack());

    if (kill) {
        attacker.onKill(this, attackPlayer_);
    }
    if (overkill) {
        attacker.onOverKill(this, attackPlayer_, atkIdx);
    }
}

// deal amount damage to defender minion of player idx
void Battle::damage(size_t idx, Minion& defender, size_t defIdx, bool poison, int& overkill, int& kill, int amount) {
    CHECK(amount > 0);
    if (defender.isDivineShield()) {
        defender.setDivineShield(false);
        onAllyBreakDivineShield(idx);
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
        defender.onDamaged(this, idx, defIdx);
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
                    VLOG(3) << "Board " << player << " " << iter->toSimpleString() << " is dead";
                    deadCount++;
                    // 1. remove the dead minion, so there would be at least a empty slot
                    auto deadMinion = *iter;
                    iter = minions.erase(iter);
                    // 2. death trigger, pre/post condition: iter points to next attack minion
                    onDeath(player, deadMinion, iter);
                    board[player].addDeadMech(deadMinion);
                    // get next element
                    if (iter != minions.end()) {
                        iter++;
                    }
                } else {
                    iter++;
                }
            }
        }
    } while (deadCount);
}

bool Battle::done() {
    // return true when one of BattleMinions is empty
    return !board[0].hasAliveMinion() || !board[1].hasAliveMinion();
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
