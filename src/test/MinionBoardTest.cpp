#include <iostream>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "Minion.h"
#include "Board.h"

TEST(MinionBoardTest, SimpleTest) {
    std::vector<Minion> minions;
    for (int i = 0; i < MINIONTYPE_COUNT; i++) {
        minions.emplace_back(Minion(static_cast<MinionType>(i)));
    }
    Board board(minions, HeroType::None, false, 1, 40);
    LOG(INFO) << board.toString();
}

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::INFO);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
