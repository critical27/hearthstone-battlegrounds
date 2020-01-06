#include <sstream>
#include "BattleMinions.h"
#include "utils/random.h"

std::ostream& operator<<(std::ostream& os, const BattleMinions& battleMinions) {
    os << battleMinions.toString();
    return os;
}

std::string BattleMinions::toString() const {
    std::stringstream ss;
    ss << "\n";
    for (const auto& minion : battleMinions_) {
        ss << "* " << minion.toString() << "\n";
    }
    return ss.str();
}

size_t BattleMinions::nextAttackerIndex() {
    // return -1 if has no valid attacker, else index of attacker
    if (battleMinions_.empty()) {
        return -1;
    }
    size_t i = 0;
    size_t size = battleMinions_.size();
    // find next minion which can attack
    while (battleMinions_[nextAttacker_].attack() == 0 && i++ < size) {
        nextAttacker_ = (nextAttacker_ + 1) % size;
    }
    // return -1 if all 0 attack minions
    if (i == BOARD_SIZE) {
        return -1;
    }
    return nextAttacker_;
}

Minion& BattleMinions::nextAttacker() {
    return battleMinions_[nextAttacker_];
}

size_t BattleMinions::nextDefenderIndex() {
    CHECK(!battleMinions_.empty());
    std::vector<size_t> tauntIdx;
    for (size_t i = 0; i < battleMinions_.size(); i++) {
        if (battleMinions_[i].isTaunt()) {
            tauntIdx.emplace_back(i);
        }
    }
    if (!tauntIdx.empty()) {
        return rand(0, tauntIdx.size() - 1);
    } else {
        return rand(0, battleMinions_.size() - 1);
    }
}

Minion& BattleMinions::minionWithLowestAttack() {
    CHECK(!battleMinions_.empty());
    Minion& result = battleMinions_.front();
    for (auto& minion : battleMinions_) {
        if (minion.attack() < result.attack()) {
            result = minion;
        }
    }
    return result;
}

int BattleMinions::hasMinion(MinionType type) const {
    int result = 0;
    std::for_each(battleMinions_.begin(), battleMinions_.end(),
                  [type, &result] (const Minion& minion) {
                      if (minion.minionType() == type) {
                          result = std::max(result, minion.isGolden() ? 2 : 1);
                      }
                  }
    );
    return result;
}
