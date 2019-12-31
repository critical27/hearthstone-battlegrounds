#pragma once

#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include "Minion.h"
#include "enums.h"

// -----------------------------------------------------------------------------
// Array of at most N minions
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Board state (for a single player)
// -----------------------------------------------------------------------------

const int BOARDSIZE = 7;
const int NUM_EXTRA_POS = 3;

// Board state
class Board {
public:
    Board(std::vector<Minion> minions, HeroType hero, bool useHeroPower, int level, int health)
        : minions_(std::move(minions)), hero_(hero), useHeroPower_(useHeroPower), level_(level), health_(health) {}

    std::vector<Minion> minions() const {
        return minions_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
    std::vector<Minion> minions_;

    // Next attacker index
    int nextAttacker_{0};

    // hero power to start with
    HeroType hero_{HeroType::None};
    bool useHeroPower_{false};

    // level of the player (or 0 if unknown)
    int level_{0};
    // health of the player
    int health_{0};
};

inline std::ostream &operator<<(std::ostream &os, const Board& board) {
    if (board.level_) {
        os << "level " << board.level_ << std::endl;
    }
    if (board.health_) {
        os << "health " << board.health_ << std::endl;
    }
    if (board.useHeroPower_) {
        os << "heropower " << board.hero_ << std::endl;
    }
    for (const auto& minion : board.minions()) {
        if (minion.exists()) {
            os << "* " << minion << std::endl;
        }
    }
    return os;
}

