#include <iostream>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "simulate/Simulation.h"

TEST(SimulationTest, SimpleSimulation) {
    {
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
        simulation.simulate(10);
        LOG(INFO) << simulation.detail();
        LOG(INFO) << simulation.result();
    }
}

TEST(SimulationTest, OptimizeTest1) {
    {
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
        simulation.simulate(10, true);
    }
}

TEST(SimulationTest, OptimizeTest2) {
    {
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::SelflessHero, true, 13, 11));
        p1.emplace_back(Minion(MinionType::RighteousProtector, true, 26, 22));
        p1.emplace_back(Minion(MinionType::CrowdFavorite, true, 26, 26));
        p1.emplace_back(Minion(MinionType::PhalanxCommander, true, 17, 19));
        p1.emplace_back(Minion(MinionType::BolvarFireblood, false, 2, 8));
        p1.emplace_back(Minion(MinionType::BolvarFireblood, false, 17, 19));
        p1.back().setTaunt(true);
        p1.emplace_back(Minion(MinionType::SelflessHero, true, 27, 21));
        p1.back().setTaunt(true);

        p2.emplace_back(Minion(MinionType::Maexxna));
        p2.emplace_back(Minion(MinionType::CobaltGuardian, true, 31, 9));
        p2.back().setDivineShield(true).addDeathrattleMicrobots();
        p2.emplace_back(Minion(MinionType::FoeReaper4000));
        p2.back().setTaunt(true).setDivineShield(true).addDeathrattleMicrobots();
        p2.emplace_back(Minion(MinionType::HarvestGolem, false, 11, 8));
        p2.back().setTaunt(true).setDivineShield(true);
        p2.emplace_back(Minion(MinionType::SecurityRover, true, 8, 12));
        p2.emplace_back(Minion(MinionType::KangorsApprentice));
        p2.emplace_back(Minion(MinionType::Junkbot, true, 10, 12));
        p2.back().addDeathrattleMicrobots();

        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Simulation simulation(you, opponent);
        simulation.simulate(10, true);
    }
}

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    testing::InitGoogleTest(&argc, argv);
    FLAGS_logtostderr = true;
    FLAGS_v = 0;
    return RUN_ALL_TESTS();
}
