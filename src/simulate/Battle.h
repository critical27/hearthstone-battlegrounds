#pragma once
#include <iostream>
#include <cstdlib>
#include "Board.h"
#include "BattleMinions.h"

// -----------------------------------------------------------------------------
// Battle state
// -----------------------------------------------------------------------------

const int MAX_MECHS_THAT_DIED = 4;
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

    // Events during battle
    void onDeath(size_t player, Minion& deadMinion, MinionIter& iter);
    /*
    void on_summoned(Minion& summoned, int player);
    void on_after_friendly_attack(Minion const& attacker, int player);
    void on_break_divine_shield(int player);

    // Minion specific events
    void do_deathrattle(Minion const& m, int player, int pos);
    void do_base_deathrattle(Minion const& m, int player, int pos);
    void on_damaged(Minion const& m, int player, int pos);
    void on_after_friendly_attack(Minion& m, Minion const& attacker);
    void on_friendly_death(Minion& m, Minion const& dead_minion, int player);
    void on_friendly_summon(Minion& m, Minion& summoned, int player);
    void on_attack_and_kill(Minion& m, int player, int pos, bool overkill);
    void on_break_friendly_divine_shield(Minion& m, int player); // for Bolvar
     */

private:
    Board you_;
    Board opponent_;

    // build BattleMinions with board
    std::vector<BattleMinions> board;

    bool yourTurn_{true};
    // who attack first is the main player, true for you, false for opponent
    bool isMainPlayer_{true};
};

