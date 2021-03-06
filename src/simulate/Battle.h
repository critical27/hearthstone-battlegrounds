#pragma once

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <gtest/gtest_prod.h>
#include "Minion.h"
#include "Board.h"
#include "BattleMinions.h"

// -----------------------------------------------------------------------------
// Battle state
// -----------------------------------------------------------------------------

using MinionIter = std::vector<Minion>::iterator;
const int OUTPUT_WIDTH = 50;
const int MAX_TURN = 100;
const std::string BLANK(OUTPUT_WIDTH, ' ');

class BattleResult {
public:
    // damage = level + stars
    BattleResult(int damage, int stars, int count, int turn)
        : damage_(damage), stars_(stars), count_(count), turn_(turn) {}

    BattleResult(int turn)
            : turn_(turn) {}

    int stars() const {
        return stars_;
    }

    int damage() const {
        return damage_;
    }

    int count() const {
        return count_;
    }

    int turn() const {
        return turn_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Battle& BattleResult);

    std::string toString() const {
        return "Damage: " + std::to_string(damage_) + ", stars: " + std::to_string(stars());
    }

private:
    int damage_{0};
    int stars_{0};
    int count_{0};
    int turn_;
};

class Battle {
public:
    Battle(const Board& you, const Board& opponent)
        : you_(you), opponent_(opponent) {}

    friend std::ostream& operator<<(std::ostream& os, Battle& battle);

    friend class Minion;

    std::string toString();
    std::string toPrettyString();

    BattleResult run();

private:
    void flipCoin();
    void prepare();
    void start();
    std::pair<size_t, size_t> randomOrderPlayer();

    void attack();
    void singleAttack(BattleMinions& active, BattleMinions& passive, size_t atkIdx);
    void doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx);
    void doCleaveAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx, std::vector<size_t> adjacent);
    void doDefense(Minion& attacker, size_t atkIdx, Minion& defender);
    std::pair<int, int> dealDamage(size_t defPlayerIdx, Minion& defender, size_t defIdx, Minion& attacker);

    void checkForDeath();
    int checkOnePlayerDeath(size_t player);
    bool done();
    bool hasValidAttacker();
    BattleResult result(bool tied = false);

    void dealDamageTo(size_t player, size_t pos, int amount);
    void dealDamageToRandomly(size_t player, int amount);
    bool dealDamageToLeftMost(size_t player, int amount);

    // Events during battle
    void onBattleStart(size_t player);
    void onAllySummon(size_t player, Minion& summoned, bool played = false);
    void onAllyAttack(size_t player);
    void onAllyBreakDivineShield(size_t player);
    void onAllyDeath(size_t player, const Minion& deadMinion);
    int onDeath(size_t player, const Minion& deadMinion, size_t idx);

    void onAllyKill(size_t player, Minion& minion, int kill);

    // summon count minion for player before pos
    // return value is actual the summoned count
    int summon(int count, Minion minion, size_t player, size_t pos);
    // summon count minion for player at the end
    int summon(int count, Minion minion, size_t player);
    // death rattle
    int deathRattle(size_t player, const Minion& deadMinion, size_t idx);

    void computeAurs() {
        board_[0].computeAuras(&board_[1]);
        board_[1].computeAuras(&board_[0]);
    }

    Board you_;
    Board opponent_;

    BattleMinions& attacker() {
        return yourTurn_ ? board_[0] : board_[1];
    }

    BattleMinions& defender() {
        return yourTurn_ ? board_[1] : board_[0];
    }

    BattleMinions& player(size_t idx) {
        return board_[idx];
    }

    void nextTurn() {
        ++turn_;
        yourTurn_ = !yourTurn_;
    }

    // build BattleMinions with board, board[0] is you, board[1] is opponent
    // BattleMinions is the actual minions on battle ground, which would compute auras
    std::vector<BattleMinions> board_;

    size_t attackPlayer_{0};
    // who attack in this turn
    bool yourTurn_{true};

    int turn_{0};
};

