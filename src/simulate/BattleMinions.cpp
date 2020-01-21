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

void BattleMinions::buffAll(int attack, int health) {
    // doodle: we buff all now, do we need to exclude dead ones
    for (auto& minion : battleMinions_) {
        minion.buff(attack, health);
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
        if (pred(minion)) {
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
