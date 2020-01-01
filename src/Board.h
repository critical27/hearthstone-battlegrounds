#pragma once

#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include "Minion.h"
#include "utils/enums.h"

// -----------------------------------------------------------------------------
// Board state (for a single player)
// -----------------------------------------------------------------------------

const int BOARDSIZE = 7;

// Board state
class Board {
public:
    Board(std::vector<Minion> minions, HeroType hero, bool useHeroPower, int level, int health)
        : minions_(std::move(minions)), hero_(hero), useHeroPower_(useHeroPower), level_(level), health_(health) {}

    std::vector<Minion> minions() const {
        return minions_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& board);

    std::string toString() const {
        std::stringstream ss;
        ss << "\n";
        if (level_) {
            ss << "level " << level_ << "\n";
        }
        if (health_) {
            ss << "health " << health_ << "\n";
        }
        if (useHeroPower_) {
            ss << "hero power " << hero_ << "\n";
        }
        for (const auto& minion : minions()) {
            if (minion.exists()) {
                ss << "* " << minion << "\n";
            }
        }
        return ss.str();
    }

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

inline std::ostream &operator<<(std::ostream& os, const Board& board) {
    if (board.level_) {
        os << "level " << board.level_ << std::endl;
    }
    if (board.health_) {
        os << "health " << board.health_ << std::endl;
    }
    if (board.useHeroPower_) {
        os << "hero power " << board.hero_ << std::endl;
    }
    for (const auto& minion : board.minions()) {
        if (minion.exists()) {
            os << "* " << minion << std::endl;
        }
    }
    return os;
}

