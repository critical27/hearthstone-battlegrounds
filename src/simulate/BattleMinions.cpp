#include <sstream>
#include "BattleMinions.h"
#include "utils/Random.h"

std::ostream& operator<<(std::ostream& os, const BattleMinions& battleMinions) {
    os << battleMinions.toString();
    return os;
}

std::string BattleMinions::toString() const {
    std::stringstream ss;
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

    // when nextAttacker_ exceed size, we need to reset it to 0.
    // e.g., we have only two alive minions, when previous minion attacked and survived, we move forward nextAttacker_,
    // however, the latter was killed by opponent, and nextAttacker_ points to a valid position
    if (nextAttacker_ >= battleMinions_.size()) {
        nextAttacker_ = 0;
    }

    // count is used to determine whether we have checked every minion
    size_t count = 0;
    // find next minion which can attack
    while (battleMinions_[nextAttacker_].attack() == 0 && count < battleMinions_.size()) {
        forwardAttackerIndex();
        ++count;
    }
    // return -1 if all 0 attack minions
    if (count == battleMinions_.size()) {
        return -1;
    }
    return nextAttacker_;
}


size_t BattleMinions::nextDefenderIndex() {
    CHECK(!battleMinions_.empty());
    IndexResult tauntIdx;
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

size_t BattleMinions::minionWithLowestAttack() {
    CHECK(!battleMinions_.empty());
    size_t ret = 0;
    for (size_t i = 1; i < battleMinions_.size(); i++) {
        if (battleMinions_[i].attack() < battleMinions_[ret].attack()) {
            ret = i;
        }
    }
    return ret;
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

IndexResult BattleMinions::livingMinions() const {
    IndexResult index;
    for (size_t i = 0; i < battleMinions_.size(); i++) {
        auto& minion = battleMinions_[i];
        if (minion.isAlive()) {
            index.emplace_back(i);
        }
    }
    return index;
}

void BattleMinions::giveRandomMinionDivineShield() {
    IndexResult indexResult;
    for (size_t i = 0; i < battleMinions_.size(); i++) {
        auto& minion = battleMinions_[i];
        if (minion.isAlive() && !minion.isDivineShield()) {
            indexResult.emplace_back(i);
        }
    }
    if (!indexResult.empty()) {
        auto picked = rand(0, indexResult.size() - 1);
        battleMinions_[picked].setDivineShield(true);
    }
}

void BattleMinions::takeDamageRandom(int amount) {
    auto indexResult = livingMinions();
    if (!indexResult.empty()) {
        auto picked = rand(0, indexResult.size() - 1);
        int current = battleMinions_[picked].health();
        battleMinions_[picked].setHealth(current - amount);
    }
}

void BattleMinions::buffRandomMinion(int attack, int health) {
    auto indexResult = livingMinions();
    if (!indexResult.empty()) {
        auto picked = rand(0, indexResult.size() - 1);
        battleMinions_[picked].buff(attack, health);
    }
}

void BattleMinions::forEachMinion(MinionAction func, MinionBoolCondition pred) {
    for (auto& minion : battleMinions_) {
        if (minion.isAlive() && pred(minion)) {
            func(minion);
        }
    }
}

// Duplication effects
int BattleMinions::extraSummonCount() const {
    return hasMinion(MinionType::Khadgar) + 1;
}

int BattleMinions::extraDeathrattleCount() const {
    return hasMinion(MinionType::BaronRivendare) + 1;
}

int BattleMinions::extraBattlecryCount() const {
    return hasMinion(MinionType::BrannBronzebeard) + 1;
}

