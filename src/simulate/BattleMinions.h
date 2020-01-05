#include "Minion.h"
#include "Board.h"

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

    bool full() const {
        return battleMinions_.size() < BOARD_SIZE;
    }

    bool hasAliveMinion() const {
        return std::any_of(battleMinions_.begin(), battleMinions_.end(),
                           [] (const Minion& minion) {
                               return minion.isAlive();
                           });
    }

    void insert(Minion minion, size_t pos) {
        if (pos > battleMinions_.size()) {
            DLOG(INFO) << "Invalid insert position";
            return;
        }
        auto iter = battleMinions_.begin() + pos;
        battleMinions_.insert(iter, minion);
    }

    Minion& minionWithLowestAttack();

    // Duplication effects
    int extraSummonCount() const {
        return hasMinion(MinionType::Khadgar) + 1;
    }

    int extraDeathrattleCount() const {
        return hasMinion(MinionType::BaronRivendare) + 1;
    }

    int extraBattlecryCount() const {
        return hasMinion(MinionType::BrannBronzebeard) + 1;
    }

    // Is the minion present? return 0 if not, 1 if yes, 2 if golden
    int hasMinion(MinionType type) const;

private:
    std::vector<Minion> battleMinions_;

    // Next attacker index
    int nextAttacker_{0};
};
