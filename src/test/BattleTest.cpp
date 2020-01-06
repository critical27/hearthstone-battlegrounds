#include <iostream>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "simulate/Battle.h"

TEST(BattleTest, AlleycatTest) {
    std::vector<Minion> minions;
    minions.emplace_back(Minion(MinionType::Alleycat));
    Board you(minions, HeroType::None, false, 1, 40);
    Board opponent(minions, HeroType::None, false, 1, 40);
    Battle battle(you, opponent);
    int result = battle.run();
    EXPECT_EQ(0, result);
}

TEST(BattleTest, MecharooTest) {
    std::vector<Minion> minions;
    minions.emplace_back(Minion(MinionType::Mecharoo));
    Board you(minions, HeroType::None, false, 1, 40);
    Board opponent(minions, HeroType::None, false, 1, 40);
    Battle battle(you, opponent);
    int result = battle.run();
    EXPECT_EQ(0, result);
}

TEST(BattleTest, MultiMecharooTest) {
    std::vector<Minion> minions;
    for (int i = 0; i < BOARD_SIZE; i++) {
        LOG(INFO) << "---------------------------------------------";
        minions.emplace_back(Minion(MinionType::Mecharoo));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
}

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    testing::InitGoogleTest(&argc, argv);
    FLAGS_logtostderr = true;
    FLAGS_v = 1;
    return RUN_ALL_TESTS();
}
