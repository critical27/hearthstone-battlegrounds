#include <numeric>
#include "Minion.h"
#include "Board.h"

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

    Minion& nextAttacker();

    size_t nextDefenderIndex();

    bool hasEmptySlot() const {
        return battleMinions_.size() < BOARD_SIZE;
    }

    bool hasAliveMinion() const {
        return std::any_of(battleMinions_.begin(), battleMinions_.end(),
                           [] (const Minion& minion) {
                               return minion.isAlive();
                           });
    }

    int remainingStars() const {
        int result = 0;
        for (const auto& minion : battleMinions_) {
            result += minion.stars();
        }
        return result;
    }

    Minion& minionWithLowestAttack();

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
                       MinionBoolCondition pred = [](Minion& minion){return true;});

private:
    std::vector<Minion> battleMinions_;

    // Next attacker index
    int nextAttacker_{0};
};
