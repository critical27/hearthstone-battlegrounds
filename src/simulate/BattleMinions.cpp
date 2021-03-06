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

size_t BattleMinions::nextAttackerIndex(bool isActive) {
    if (!isActive) {
        return nextAttacker_;
    }

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
        return tauntIdx[rand(0, tauntIdx.size() - 1)];
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
    // doodle: need to check whether a normal and a golden could accumulate
    // I remember that if normal and golden both exist, only the golden one will affect
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

int BattleMinions::countIf(MinionBoolCondition pred) {
    int result = 0;
    for (auto& minion : battleMinions_) {
        if (minion.isAlive() && pred(minion)) {
            ++result;
        }
    }
    return result;
}

int BattleMinions::countTribe(Tribe tribe) {
    return countIf([] (const Minion& m) { return m.isTribe(Tribe::Dragon); });
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

void BattleMinions::computeAuras(BattleMinions* opponent) {
    if (!hasAuraMinion_) {
        return;
    }
    hasAuraMinion_ = false;
    forEachMinion([] (Minion& m) {
        m.clearAuraBuff();
    });
    for (size_t i = 0; i < battleMinions_.size(); i++) {
        if (battleMinions_[i].computeAuras(i, this, opponent)) {
            hasAuraMinion_ = true;
        };
    }
}

void BattleMinions::auraBuffAdjacent(int attack, int health, size_t pos) {
    auto adjacent = getAdjacent(pos);
    for (const auto& adj : adjacent) {
        battleMinions_[adj].auraBuff(attack, health);
    }
}

void BattleMinions::auraBuffOthersIf(int attack, int health, size_t pos, MinionBoolCondition pred) {
    for (size_t i = 0; i < battleMinions_.size(); i++) {
        Minion& minion = battleMinions_[i];
        if (i != pos && pred(minion)) {
            minion.auraBuff(attack, health);
        }
    }
}
