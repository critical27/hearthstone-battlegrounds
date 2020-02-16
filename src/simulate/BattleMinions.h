#pragma once

#include <numeric>
#include "Minion.h"
#include "Board.h"

const size_t MAX_MECHS_THAT_DIED = 4;
using IndexResult = std::vector<size_t>;
using MinionBoolCondition = std::function<bool (const Minion& minion)>;
using MinionAction = std::function<void (Minion& minion)>;

class BattleMinions {
public:

    BattleMinions() = default;

    BattleMinions(const std::vector<Minion> minions)
            : battleMinions_(minions), nextAttacker_(0), hasAuraMinion_{true} {}

    std::vector<Minion>& battleMinions() {
        return battleMinions_;
    }

    Minion& operator[](size_t idx) {
        CHECK_LE(0, idx);
        CHECK_LT(idx, battleMinions_.size());
        return battleMinions_[idx];
    }

    const Minion& at(size_t idx) {
        CHECK_LE(0, idx);
        CHECK_LT(idx, battleMinions_.size());
        return battleMinions_.at(idx);
    }

    friend std::ostream& operator<<(std::ostream& os, const BattleMinions& battleMinions);

    std::string toString() const;

    // return -1 if has no valid attacker, else index of attacker
    size_t nextAttackerIndex(bool isActive = false);

    size_t nextDefenderIndex();

    void forwardAttackerIndex() {
        if (!battleMinions_.empty()) {
            nextAttacker_ = (nextAttacker_ + 1) % battleMinions_.size();
        }
    }

    void backwardAttackerIndex() {
        if (nextAttacker_ > 0) {
            --nextAttacker_;
        }
    }

    size_t size() const {
        return battleMinions_.size();
    }

    bool hasEmptySlot() const {
        return battleMinions_.size() < BOARD_SIZE;
    }

    bool hasAliveMinion() const {
        return !battleMinions_.empty();
    }

    bool hasMinionWhichCanAttack() const {
        if (!battleMinions_.empty()) {
            return std::any_of(battleMinions_.begin(), battleMinions_.end(),
                               [] (const Minion& minion) {
                                   return minion.attack() > 0;
                               });
        } else {
            return false;
        }
    }

    int remainingMinions() const {
        int count = 0;
        for (const auto& minion : battleMinions_) {
            CHECK(minion.isAlive());
            count++;
        }
        return count;
    }

    int remainingStars() const {
        int count = 0;
        for (const auto& minion : battleMinions_) {
            CHECK(minion.isAlive());
            count += minion.stars();
        }
        return count;
    }

    std::vector<size_t> getAdjacent(size_t idx) {
        std::vector<size_t> ret;
        if (idx > 0) {
            ret.emplace_back(idx - 1);
        }
        if (idx < battleMinions_.size() - 1) {
            ret.emplace_back(idx + 1);
        }
        return ret;
    }

    // return the idx of minion with lowest attack
    size_t minionWithLowestAttack();

    // Duplication effects
    int extraSummonCount() const;
    int extraDeathrattleCount() const;
    int extraBattlecryCount() const;

    // Is the minion present? return 0 if not, 1 if yes, 2 if golden
    int hasMinion(MinionType type) const;

    IndexResult livingMinions() const;

    void giveRandomMinionDivineShield();

    void takeDamageRandom(int amount);

    void buffRandomMinion(int attack, int health);

    void forEachMinion(MinionAction func,
                       MinionBoolCondition pred = [] (const Minion& minion) { return true; });

    int countIf(MinionBoolCondition pred);

    void addDeadMech(Minion& minion) {
        if (deadMechs_.size() < MAX_MECHS_THAT_DIED) {
            deadMechs_.emplace_back(minion.newCopy());
        }
    }

    std::vector<Minion> deadMechs() {
        return deadMechs_;
    }

    void computeAuras(BattleMinions* opponent);
    void auraBuffAdjacent(int attack, int health, size_t pos);
    void auraBuffOthersIf(int attack, int health, size_t pos, MinionBoolCondition pred);

private:
    std::vector<Minion> battleMinions_;
    std::vector<Minion> deadMechs_;

    // Next attacker index
    int nextAttacker_{0};

    bool hasAuraMinion_{true};
};
