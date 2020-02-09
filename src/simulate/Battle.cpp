#include "Battle.h"
#include <glog/logging.h>
#include "utils/Enums.h"
#include "utils/Random.h"

std::ostream& operator<<(std::ostream& os, const BattleResult& result) {
    os << result.toString();
    return os;
}

std::string Battle::toString() const {
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
    os << battle.toString();
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
    // reset the board
    LOG(INFO) << "---------------------------------------------";
    board.clear();
    board.emplace_back(you_.minions());
    board.emplace_back(opponent_.minions());
    CHECK_EQ(2, board.size());
}

BattleResult Battle::run() {
    prepare();
    flipCoin();

    VLOG(1) << "Battle after " << turn_ << " turns:";
    VLOG(1) << "\n" << toPrettyString();
    while (!done()) {
        if (!hasValidAttacker()) {
            return result(true);
        }
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
        CHECK_GT(attacker.attack(), 0);
        bool attackerAlive = true;
        for (; attackTimes > 0; attackTimes--) {
            if (!passive.hasAliveMinion()) {
                break;
            }
            attackerAlive = singleAttack(active, passive, atkIdx);
            onAllyAttack(attackPlayer_);
            checkForDeath();
            if (!attackerAlive) {
                break;
            }
        }
        if (attackerAlive) {
            active.forwardAttackerIndex();
        }
    }
}

// return true for attacker alive, otherwise dead
bool Battle::singleAttack(BattleMinions& active, BattleMinions& passive, size_t atkIdx) {
    Minion& attacker = active[atkIdx];
    if (attacker.minionType() != MinionType::ZappSlywick) {
        size_t defIdx = passive.nextDefenderIndex();
        if (attacker.isCleave()) {
            auto adjacent = passive.getAdajacent(defIdx);
            VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                    << " **attack** "
                    << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << passive[defIdx].toSimpleString();
            return doCleaveAttack(active, atkIdx, passive, defIdx, adjacent);
        } else {
            VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                    << " **attack** "
                    << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << passive[defIdx].toSimpleString();
            return doAttack(active, atkIdx, passive, defIdx);
        }
    } else {
        size_t defIdx = passive.minionWithLowestAttack();
        VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                << " **attack** "
                << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << passive[defIdx].toSimpleString();
        return doAttack(active, atkIdx, passive, defIdx);
    }
}

bool Battle::doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx) {
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
    return attacker.isAlive();
}

bool Battle::doCleaveAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx, std::vector<size_t> adjacent) {
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
    return attacker.isAlive();
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
    // dooodle: we need to first remove all dead minion, and then trigger onDeath one by one.
    // Otherwise, if more than one minion died during this round, the dead minion could affect other dead minion,
    // i.e. empty slot
    int deadCount = 0;
    do {
        deadCount = 0;
        // doodle: check random player at first, this do affect the battle result,
        for (size_t player = 0; player < board.size(); player++) {
            std::vector<std::pair<Minion, size_t>> deadMinions;
            auto& minions = board[player].battleMinions();
            int aliveMinionsCount = 0;
            // iterate through the battle minions
            for (auto iter = minions.begin(); iter != minions.end(); ) {
                if (!iter->isAlive()) {
                    VLOG(3) << "Board " << player << " " << iter->toSimpleString() << " is dead";
                    deadCount++;
                    // 1. remove the dead minion, so there would be at least a empty slot
                    auto deadMinion = *iter;
                    iter = minions.erase(iter);
                    // 2. save the aliveMinionsCount, which is the position to trigger onDeath
                    deadMinions.emplace_back(deadMinion, aliveMinionsCount);
                    if (deadMinion.isTribe(Tribe::Mech)) {
                        board[player].addDeadMech(deadMinion);
                    }
                } else {
                    // 3. if minion is alive, move to next
                    aliveMinionsCount++;
                    iter++;
                }
            }
            int offset = 0;
            for (auto& pair : deadMinions) {
                // 4. death trigger, onDeath return the summoned count, which need to apply to all pos in deadMinions
                // for example: 3 RatPack died, the pos in deadMinions is [0, 0, 0],
                // after first onDeath, we summon 2 rat, so the remaining pos should count offset, which would be [0, 2, 2],
                // after second onDeath, we summon another 2 rat, which would be [0, 2, 4],
                offset += onDeath(player, pair.first, pair.second + offset);
            }
        }
    } while (deadCount);
}

bool Battle::done() {
    // return true when one of BattleMinions is empty
    return !board[0].hasAliveMinion() || !board[1].hasAliveMinion();
}

bool Battle::hasValidAttacker() {
    return board[0].hasMinionWhichCanAttack() || board[1].hasMinionWhichCanAttack();
}

BattleResult Battle::result(bool tied) {
    CHECK(turn_ < MAX_TURN);
    if (tied) {
        return BattleResult(turn_);
    }
    // stars > 0 if you win, < 0 if opponent win, 0 if tied
    int yourStars = board[0].remainingStars(), opponentStars = board[1].remainingStars();
    int yourCount = board[0].remainingMinions(), opponentCount = board[1].remainingMinions();
    int stars = yourStars - opponentStars;
    if (stars > 0) {
        CHECK_GT(yourCount, 0);
        CHECK_EQ(opponentCount, 0);
        return BattleResult(you_.level() + yourStars, yourStars, yourCount, turn_);
    } else if (stars < 0) {
        CHECK_GT(opponentCount, 0);
        CHECK_EQ(yourCount, 0);
        return BattleResult(-(opponent_.level() + opponentStars), -opponentStars, opponentCount, turn_);
    } else {
        return BattleResult(turn_);
    }
}
