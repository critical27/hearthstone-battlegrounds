#pragma once

#include <numeric>
#include "Minion.h"
#include "Board.h"

const size_t MAX_MECHS_THAT_DIED = 4;
using IndexResult = std::vector<size_t>;
using MinionBoolCondition = std::function<bool (Minion& minion)>;
using MinionAction = std::function<void (Minion& minion)>;

class BattleMinions {
public:

    BattleMinions() = default;

    BattleMinions(const std::vector<Minion> minions)
            : battleMinions_(minions), nextAttacker_(0) {}

    std::vector<Minion>& battleMinions() {
        return battleMinions_;
    }

    Minion& operator[](size_t idx) {
        CHECK(0 <= idx && idx < battleMinions_.size());
        return battleMinions_[idx];
    }

    friend std::ostream& operator<<(std::ostream& os, const BattleMinions& battleMinions);

    std::string toString() const;

    // return -1 if has no valid attacker, else index of attacker
    size_t nextAttackerIndex();

    size_t nextDefenderIndex();

    size_t size() const {
        return battleMinions_.size();
    }

    bool hasEmptySlot() const {
        return battleMinions_.size() < BOARD_SIZE;
    }

    bool hasAliveMinion() const {
        if (!battleMinions_.empty()) {
            bool ret = std::any_of(battleMinions_.begin(), battleMinions_.end(),
                                   [] (const Minion& minion) {
                                       return minion.isAlive();
                                   });
            CHECK(ret);
            return ret;
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

    std::vector<size_t> getAdajacent(size_t idx) {
        std::vector<size_t> ret;
        if (idx > 0) {
            ret.emplace_back(idx - 1);
        }
        if (idx < battleMinions_.size() - 1) {
            ret.emplace_back(idx + 1);
        }
        return ret;
    }

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

    void buffAll(int attack, int health);

    void buffRandomMinion(int attack, int health);

    void forEachMinion(MinionAction func,
                       MinionBoolCondition pred = [] (Minion& minion) { return true; });

    void addDeadMech(Minion& minion) {
        if (deadMechs_.size() < MAX_MECHS_THAT_DIED) {
            deadMechs_.emplace_back(minion.newCopy());
        }
    }

    std::vector<Minion> deadMechs() {
        return deadMechs_;
    }

private:
    std::vector<Minion> battleMinions_;
    std::vector<Minion> deadMechs_;

    // Next attacker index
    int nextAttacker_{0};
};
