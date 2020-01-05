#include <iostream>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "simulate/Battle.h"

TEST(BattleTest, SimpleBattleTest) {
    // two player with Alleycat
    std::vector<Minion> minions;
    minions.emplace_back(Minion(MinionType::Alleycat));
    Board you(minions, HeroType::None, false, 1, 40);
    Board opponent(minions, HeroType::None, false, 1, 40);
    Battle battle(you, opponent);
    battle.run();
}

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    testing::InitGoogleTest(&argc, argv);
    FLAGS_logtostderr = true;
    FLAGS_v = 4;
    return RUN_ALL_TESTS();
}
