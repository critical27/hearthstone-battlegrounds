#pragma once

#include "Battle.h"

const int DEFAULT_RUNS = 10;

class Simulation {
public:
    Simulation(Board you, Board opponent)
        : you_(you), opponent_(opponent) {}

    void simulate(int count = DEFAULT_RUNS, bool optimize = false);

    std::string result();
    std::string detail();

private:
    float run(int count);
    float meanDamage();

    Board you_;
    Board opponent_;

    std::vector<BattleResult> results_;
};