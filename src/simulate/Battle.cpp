#include "Battle.h"
#include <glog/logging.h>
#include "utils/Enums.h"
#include "utils/Random.h"

std::ostream& operator<<(std::ostream& os, const BattleResult& result) {
    os << result.toString();
    return os;
}

std::string Battle::toString() {
    std::stringstream ss;
    ss << board_.front().toString();
    ss << "VS" << "\n";
    ss << board_.back().toString();
    return ss.str();
}

std::string Battle::toPrettyString() {
    size_t m = board_.front().size(), n = board_.back().size();
    size_t vs = std::max(m, n) / 2;
    std::stringstream ss;
    for (size_t i = 0; i < std::max(m, n); i++) {
        if (i < m) {
            ss << std::left << std::setfill(' ') << std::setw(OUTPUT_WIDTH) << board_[0][i].toString();
        } else {
            ss << BLANK;
        }
        if (i == vs) {
            ss << " VS ";
        } else {
            ss << "    ";
        }
        if (i < n) {
            ss << std::right << std::setfill(' ') << std::setw(OUTPUT_WIDTH) << board_[1][i].toString();
        } else {
            ss << BLANK;
        }
        ss << "\n";
    }
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, Battle& battle) {
    os << battle.toString();
    return os;
}

void Battle::flipCoin() {
    size_t m = board_[0].size(), n = board_[1].size();
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
    VLOG(1) << "---------------------------------------------";
    board_.clear();
    board_.emplace_back(you_.minions());
    board_.emplace_back(opponent_.minions());
    CHECK_EQ(2, board_.size());
    computeAurs();
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
    size_t atkIdx = active.nextAttackerIndex(true);
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
            singleAttack(active, passive, atkIdx);
            attackerAlive = active[atkIdx].isAlive();
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
void Battle::singleAttack(BattleMinions& active, BattleMinions& passive, size_t atkIdx) {
    Minion& attacker = active[atkIdx];
    if (attacker.minionType() != MinionType::ZappSlywick) {
        size_t defIdx = passive.nextDefenderIndex();
        Minion& defender = passive[defIdx];
        if (attacker.isCleave()) {
            auto adjacent = passive.getAdjacent(defIdx);
            VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                    << " **attack** "
                    << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << defender.toSimpleString();
            doCleaveAttack(active, atkIdx, passive, defIdx, adjacent);
        } else {
            VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                    << " **attack** "
                    << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << defender.toSimpleString();
            doAttack(active, atkIdx, passive, defIdx);
        }
        doDefense(attackPlayer_, attacker, atkIdx, defender);
    } else {
        size_t defIdx = passive.minionWithLowestAttack();
        Minion& defender = passive[defIdx];
        VLOG(2) << "Board " << attackPlayer_ << " minion " << atkIdx << " " << active[atkIdx].toSimpleString()
                << " **attack** "
                << "Board " << 1 - attackPlayer_ << " minion " << defIdx << " " << defender.toSimpleString();
        doAttack(active, atkIdx, passive, defIdx);
        doDefense(attackPlayer_, attacker, atkIdx, defender);
    }
}

void Battle::doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx) {
    Minion& attacker = active[atkIdx];
    Minion& defender = passive[defIdx];

    // only attacker handle kill and overkill
    auto result = dealDamage(1 - attackPlayer_, defender, defIdx, attacker);
    if (result.first > 0) {
        attacker.onKill(this, attackPlayer_);
    }
    if (result.second > 0) {
        attacker.onOverKill(this, attackPlayer_, atkIdx);
    }

    // Say passive have 3 minions: m0, m1, m2
    // 1. m0 attack and survived, m1 should be next one (nextAttacker_ = 1)
    // 2. m0 was killed when active attacks, which remains [m1, m2] (nextAttacker_ = 1)
    // 3. m1 should be passive's next attcker
    // so if defIdx is less than passive's next attacker idx, we need to backward it
    // this still need to be check carefully
    if (!defender.isAlive() && defIdx < passive.nextAttackerIndex()) {
        passive.backwardAttackerIndex();
    }
}

void Battle::doCleaveAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx, std::vector<size_t> adjacent) {
    doAttack(active, atkIdx, passive, defIdx);
    for (const auto& adjIdx : adjacent) {
        doAttack(active, atkIdx, passive, adjIdx);
    }
}

void Battle::doDefense(size_t atkPlayerIdx, Minion& attacker, size_t atkIdx, Minion& defender) {
    // only attacker handle kill and overkill
    if (defender.attack() > 0) {
        dealDamage(atkPlayerIdx, attacker, atkIdx, defender);
    }
}

// deal attacker.attack() damage to defender
std::pair<int, int> Battle::dealDamage(size_t defPlayerIdx, Minion& defender, size_t defIdx, Minion& attacker) {
    int amount = attacker.attack();
    int kill = 0, overKill = 0;
    CHECK_GT(amount, 0);
    if (defender.isDivineShield()) {
        defender.setDivineShield(false);
        onAllyBreakDivineShield(defPlayerIdx);
    } else {
        defender.setHealth(defender.health() - amount);
        if (defender.health() > 0 && attacker.isPoison()) {
            defender.setHealth(0);
        }
        if (defender.health() < 0) {
            kill++;
            overKill++;
        } else if (defender.health() == 0) {
            kill++;
        }
        defender.onDamaged(this, defPlayerIdx, defIdx);
    }
    return {kill, overKill};
}

void Battle::checkForDeath() {
    int deadCount = 0;
    size_t first, second;
    if (!rand(0, 1)) {
        first = 0;
        second = 1;
    } else {
        first = 1;
        second = 0;
    }
    do {
        deadCount = 0;
        // doodle: check random player at first, this do affect the battle result,
        deadCount += checkOnePlayerDeath(first);
        deadCount += checkOnePlayerDeath(second);
    } while (deadCount);
}

int Battle::checkOnePlayerDeath(size_t player) {
    // we need to first remove all dead minion, and then trigger onDeath one by one. Otherwise,
    // if more than one minion died during this round, the dead minion could affect other dead
    // minion, e.g. if 3 minions were dead, if we don't remove them at first, there could be
    // less empty slot
    int deadCount = 0;
    std::vector<std::pair<Minion, size_t>> deadMinions;
    auto& minions = board_[player].battleMinions();
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
                board_[player].addDeadMech(deadMinion);
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
    computeAurs();
    return deadCount;
}

bool Battle::done() {
    // return true when one of BattleMinions is empty
    return !board_[0].hasAliveMinion() || !board_[1].hasAliveMinion();
}

bool Battle::hasValidAttacker() {
    return board_[0].hasMinionWhichCanAttack() || board_[1].hasMinionWhichCanAttack();
}

BattleResult Battle::result(bool tied) {
    CHECK(turn_ < MAX_TURN);
    if (tied) {
        return BattleResult(turn_);
    }
    // stars > 0 if you win, < 0 if opponent win, 0 if tied
    int yourStars = board_[0].remainingStars(), opponentStars = board_[1].remainingStars();
    int yourCount = board_[0].remainingMinions(), opponentCount = board_[1].remainingMinions();
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
