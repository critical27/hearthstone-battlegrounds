#include <iostream>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "simulate/Simulation.h"

TEST(SimulationTest, FirstCase) {
    {
        // 1 Alleycat, 1 ReplicatingMenace, 1 golden RatPack [taunt], 1 2/2 RatPack
        // vs
        // 1 4/4 golden CaveHydra
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::FloatingWatcher, false, 8, 8));
        p1.emplace_back(Minion(MinionType::WrathWeaver, true, 56, 56));
        p1.emplace_back(Minion(MinionType::Imprisoner));
        p1.emplace_back(Minion(MinionType::ImpGangBoss, true, 10, 14));
        p1.emplace_back(Minion(MinionType::AnnihilanBattlemaster, false, 3, 28));
        p1.emplace_back(Minion(MinionType::SoulJuggler));
        p1.emplace_back(Minion(MinionType::SoulJuggler));

        p2.emplace_back(Minion(MinionType::CobaltGuardian, false, 14, 7));
        p2.back().setDivineShield(true).addDeathrattleGoldenMicrobots();
        p2.emplace_back(Minion(MinionType::SelflessHero, true, 6, 4));
        p2.emplace_back(Minion(MinionType::PsychOTron, false, 7, 6));
        p2.emplace_back(Minion(MinionType::FiendishServant, true, 10, 8));
        p2.emplace_back(Minion(MinionType::MechanoEgg, false, 2, 5));
        p2.emplace_back(Minion(MinionType::BaronRivendare));
        p2.emplace_back(Minion(MinionType::Khadgar));

        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Simulation simulation(you, opponent);
        simulation.run(100);
        LOG(INFO) << simulation.detail();
        LOG(INFO) << simulation.result();
    }
}

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    testing::InitGoogleTest(&argc, argv);
    FLAGS_logtostderr = true;
    FLAGS_v = 0;
    return RUN_ALL_TESTS();
}
