#include <iostream>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "simulate/Minion.h"
#include "simulate/Board.h"

TEST(MinionBoardTest, CheckAllMinionTest) {
    std::vector<Minion> minions;
    for (int i = 0; i < MINIONTYPE_COUNT; i++) {
        minions.emplace_back(Minion(static_cast<MinionType>(i)));
    }
    Board board(minions, HeroType::None, false, 1, 40);
    LOG(INFO) << board.toString();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    return RUN_ALL_TESTS();
}
