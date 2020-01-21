#pragma once

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <glog/logging.h>
#include "Minion.h"

// -----------------------------------------------------------------------------
// Board state (for a single player)
// -----------------------------------------------------------------------------

const int BOARD_SIZE = 7;

// Board state
class Board {
public:
    // Caller must make sure that minions.size() < BOARD_SIZE
    Board(std::vector<Minion> minions, HeroType hero, bool useHeroPower, int level, int health)
        : minions_(std::move(minions)), hero_(hero), useHeroPower_(useHeroPower), level_(level), health_(health) {}

    std::vector<Minion> minions() const {
        return minions_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& board);

    std::string toString() const;

private:
    std::vector<Minion> minions_;

    HeroType hero_{HeroType::None};
    bool useHeroPower_{false};

    // level of the player (or 0 if unknown)
    int level_{0};
    // health of the player
    int health_{0};
};
