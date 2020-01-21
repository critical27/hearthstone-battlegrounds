#pragma once
#include <iostream>
#include <cstdlib>
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
        ss << board.front().toString();
        ss << "VS";
        ss << board.back().toString();
        return ss.str();
    }

    void prepare();
    int run();
    void attack();
    void doAttack(BattleMinions& active, size_t atkIdx, BattleMinions& passive, size_t defIdx);
    void damage(Minion& defender, int amount, bool poison, int& kill, int& overkill);
    void checkForDeath();
    bool done();
    int result();

    // summon count minion for player before iter
    void summon(int count, const Minion& minion, size_t player, MinionIter& iter);
    // summon count minion for player at the end
    void summon(int count, const Minion& minion, size_t player);

    // Events during battle
    void onDeath(size_t player, Minion& deadMinion, MinionIter& iter);

private:
    Board you_;
    Board opponent_;

    // build BattleMinions with board
    std::vector<BattleMinions> board;

    bool yourTurn_{true};
    // who attack first is the main player, true for you, false for opponent
    bool isMainPlayer_{true};
};

