#include <iostream>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "simulate/Battle.h"

#define DRAW_LINE LOG(INFO) << "---------------------------------------------"

TEST(BattleTest, AlleycatTest) {
    sleep(1);
    std::vector<Minion> minions;
    minions.emplace_back(Minion(MinionType::Alleycat));
    Board you(minions, HeroType::None, false, 1, 40);
    Board opponent(minions, HeroType::None, false, 1, 40);
    Battle battle(you, opponent);
    int result = battle.run();
    EXPECT_EQ(0, result);
}

TEST(BattleTest, MultiMecharooTest) {
    sleep(1);
    std::vector<Minion> minions;
    for (int i = 0; i < BOARD_SIZE; i++) {
        DRAW_LINE;
        minions.emplace_back(Minion(MinionType::Mecharoo));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
}

TEST(BattleTest, TierOneDeathRattleTest) {
    sleep(1);
    {
        DRAW_LINE;
        // 1 Mecharoo vs 1 Mecharoo
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::Mecharoo));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
    {
        DRAW_LINE;
        // 1 golden Mecharoo vs 1 Mecharoo
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::Mecharoo, true));
        p2.emplace_back(Minion(MinionType::Mecharoo));
        p2.emplace_back(Minion(MinionType::Mecharoo));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
    {
        DRAW_LINE;
        // 1 SelflessHero 1 Mecharoo
        // vs
        // 1 SelflessHero 1 Mecharoo
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::SelflessHero));
        minions.emplace_back(Minion(MinionType::Mecharoo));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
}

TEST(BattleTest, TierTwoDeathRattleTest) {
    sleep(1);
    {
        DRAW_LINE;
        // 1 HarvestGolem vs 1 HarvestGolem
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::HarvestGolem));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
    {
        DRAW_LINE;
        // 2 KaboomBot vs 2 KaboomBot
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::KaboomBot));
        minions.emplace_back(Minion(MinionType::KaboomBot));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
    {
        DRAW_LINE;
        // 1 MountedRaptor vs 1 MountedRaptor
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::MountedRaptor));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
    {
        DRAW_LINE;
        // 1 SpawnOfNZoth 1 HarvestGolem
        // vs
        // 1 SpawnOfNZoth 1 HarvestGolem
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::SpawnOfNZoth));
        minions.emplace_back(Minion(MinionType::HarvestGolem));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
        EXPECT_EQ(0, result);
    }
}

TEST(BattleTest, RandomTest) {
    sleep(1);
    {
        DRAW_LINE;
        // 1 MountedRaptor vs 1 MountedRaptor
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::MountedRaptor));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        int result = battle.run();
    }
}

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    testing::InitGoogleTest(&argc, argv);
    FLAGS_logtostderr = true;
    FLAGS_v = 1;
    return RUN_ALL_TESTS();
}
