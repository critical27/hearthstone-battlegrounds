#pragma once
#include <iostream>
#include <cstdlib>
#include "Minion.h"
#include "Board.h"
#include "BattleMinions.h"

// -----------------------------------------------------------------------------
// Battle state
// -----------------------------------------------------------------------------

using MinionIter = std::vector<Minion>::iterator;

class Battle {
public:
    Battle(const Board& you, const Board& opponent)
        : you_(you), opponent_(opponent) {
        board.emplace_back(you_.minions());
        board.emplace_back(opponent_.minions());
    }

    friend std::ostream& operator<<(std::ostream& os, const Battle& battle);

    std::string toString() const {
        std::stringstream ss;
        ss << "\n";
        ss << board.front().toString();
        ss << "VS" << "\n";
        ss << board.back().toString();
        return ss.str();
    }

    void prepare();
    int run();

    void attack();
    void singleAttack(BattleMinions& active, BattleMinions& passive, size_t atkIdx);
    void doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx);
    void doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx, std::vector<size_t> adjacent);
    void damage(size_t playerIdx, Minion& defender, size_t defIdx, bool poison, int& overkill, int& kill, int amount);

    void checkForDeath();
    bool done();
    int result();

    // Events during battle
    void onAllySummon(size_t player, Minion &summoned, bool played = false);
    void onAllyAttack(size_t player);
    void onAllyBreakDivineShield(size_t player);
    void onAllyDeath(size_t player, const Minion& deadMinion);
    void onDeath(size_t player, const Minion& deadMinion, MinionIter& iter);

    // summon count minion for player before iter
    void summon(int count, Minion minion, size_t player, MinionIter& iter);
    void summon(int count, Minion minion, size_t player, size_t pos);
    // summon count minion for player at the end
    void summon(int count, Minion minion, size_t player);
    // death rattle
    void deathRattle(size_t player, const Minion& deadMinion, MinionIter& iter);

    BattleMinions& player(size_t idx) {
        return board[idx];
    }

private:

    Board you_;
    Board opponent_;

    BattleMinions& attacker() {
        return yourTurn_ ? board[0] : board[1];
    }

    BattleMinions& defender() {
        return yourTurn_ ? board[1] : board[0];
    }

    void nextTurn() {
        ++turn_;
        yourTurn_ = !yourTurn_;
    }

    // build BattleMinions with board, board[0] is you, board[1] is opponent
    std::vector<BattleMinions> board;

    size_t attackPlayer_{0};
    // who attack in this turn
    bool yourTurn_{true};
    // coin means who attack first, true four you, false for opponent
    bool coin_{true};

    int turn_{0};
};

