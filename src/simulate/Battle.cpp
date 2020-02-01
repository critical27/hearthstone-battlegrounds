#include "Battle.h"
#include <glog/logging.h>
#include "utils/Enums.h"
#include "utils/Random.h"

std::string Battle::toString() {
    std::stringstream ss;
    ss << board.front().toString();
    ss << "VS" << "\n";
    ss << board.back().toString();
    return ss.str();
}

std::string Battle::toPrettyString() {
    size_t m = board.front().size(), n = board.back().size();
    size_t vs = std::max(m, n) / 2;
    std::stringstream ss;
    for (size_t i = 0; i < std::max(m, n); i++) {
        if (i < m) {
            ss << std::left << std::setfill(' ') << std::setw(OUTPUT_WIDTH) << board[0][i].toString();
        } else {
            ss << BLANK;
        }
        if (i == vs) {
            ss << " VS ";
        } else {
            ss << "    ";
        }
        if (i < n) {
            ss << std::right << std::setfill(' ') << std::setw(OUTPUT_WIDTH) << board[1][i].toString();
        } else {
            ss << BLANK;
        }
        ss << "\n";
    }
    return ss.str();
}
std::ostream& operator<<(std::ostream& os, const Battle& battle) {
    os << battle.board[0];
    os << "VS" << std::endl;
    os << battle.board[1];
    return os;
}

void Battle::flipCoin() {
    size_t m = board[0].size(), n = board[1].size();
    if (m < n) {
        yourTurn_ = false;
        return;
    } else if (m > n) {
        yourTurn_ = true;
        return;
    }

    // decide which player attacks first, 0 is you, 1 is opponent
    if (!rand(0, 1)) {
        yourTurn_ = true;
    } else {
        yourTurn_ = false;
    }
}

void Battle::prepare() {
    // todo: hero_power
    // todo: aurus
}

BattleResult Battle::run() {
    CHECK_EQ(2, board.size());
    flipCoin();
    prepare();

    VLOG(1) << "Battle after " << turn_ << " turns:";
    VLOG(1) << "\n" << toPrettyString();
    while (!done() && turn_ < MAX_TURN) {
        attack();
        nextTurn();
        VLOG(1) << "Battle after " << turn_ << " turns:";
        VLOG(1) << "\n" << toPrettyString();
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
        int attackTimes = attacker.attackTimes();
        CHECK(attacker.isAlive());
        for (int i = 0; i < attackTimes && attacker.isAlive(); i++) {
            singleAttack(active, passive, atkIdx);
            onAllyAttack(attackPlayer_);
        }
        if (attacker.isAlive()) {
            active.forwardAttackerIndex();
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
            doCleaveAttack(active, atkIdx, passive, defIdx, adjacent);
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
    if (defender.attack() > 0) {
        damage(attackPlayer_, attacker, atkIdx, defender.isPoison(), overkill, kill, defender.attack());
    }

    if (kill) {
        attacker.onKill(this, attackPlayer_);
    }
    if (overkill) {
        attacker.onOverKill(this, attackPlayer_, atkIdx);
    }
}

void Battle::doCleaveAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx, std::vector<size_t> adjacent) {
    Minion& attacker = active[atkIdx];
    Minion& defender = passive[defIdx];

    int kill = 0, overkill = 0;
    damage(1 - attackPlayer_, defender, defIdx, attacker.isPoison(), overkill, kill, attacker.attack());
    for (auto idx : adjacent) {
        damage(1 - attackPlayer_, passive[idx], idx, attacker.isPoison(), overkill, kill, attacker.attack());
    }
    if (defender.attack() > 0) {
        damage(attackPlayer_, attacker, atkIdx, defender.isPoison(), overkill, kill, defender.attack());
    }

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

BattleResult Battle::result() {
    // stars > 0 if you win, < 0 if opponent win, 0 if tied
    int stars = board[0].remainingStars() - board[1].remainingStars();
    int count = 0;
    if (stars > 0) {
        count = board[0].remainingMinions();
        CHECK_GT(count, 0);
        CHECK_EQ(board[1].remainingMinions(), 0);
    } else if (stars < 0) {
        count = board[1].remainingMinions();
        CHECK_GT(count, 0);
        CHECK_EQ(board[0].remainingMinions(), 0);
    } else {
        // we can not make sure of following, e.g., 1 MechanoEgg vs 1 MechanoEgg
        // which would make a even
        // CHECK_EQ(board[0].remainingMinions(), 0);
        // CHECK_EQ(board[1].remainingMinions(), 0);
    }
    return BattleResult(stars, count, turn_);
}
