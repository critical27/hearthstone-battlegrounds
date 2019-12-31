#include <iostream>
#include "Minion.h"
#include "Board.h"
#include "enums.h"

int main() {
    std::vector<Minion> minions;
    for (int i = 0; i < MINIONTYPE_COUNT; i++) {
        minions.emplace_back(Minion(static_cast<MinionType>(i)));
    }
    Board board(minions, HeroType::None, false, 1, 40);
    std::cout << board << std::endl;
}