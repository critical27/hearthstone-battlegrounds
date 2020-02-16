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
    auto result = battle.run();
    ASSERT_EQ(0, result.stars());
    ASSERT_EQ(0, result.count());
    ASSERT_EQ(1, result.turn());
}

TEST(BattleTest, MultiMecharooTest) {
    std::vector<Minion> minions;
    for (int i = 1; i <= BOARD_SIZE; i++) {
        minions.emplace_back(Minion(MinionType::Mecharoo));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(2 * i, result.turn());
    }
}

TEST(BattleTest, TierOneDeathRattleTest) {
    {
        // 1 Mecharoo vs 1 Mecharoo
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::Mecharoo));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 1 golden Mecharoo vs 2 Mecharoo
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::Mecharoo, true));
        p2.emplace_back(Minion(MinionType::Mecharoo));
        p2.emplace_back(Minion(MinionType::Mecharoo));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(4, result.turn());
    }
    {
        // 1 SelflessHero 1 Mecharoo
        // vs
        // 1 SelflessHero 1 Mecharoo
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::SelflessHero));
        minions.emplace_back(Minion(MinionType::Mecharoo));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(4, result.turn());
    }
    {
        // 1 SelflessHero 1 Mecharoo
        // vs
        // 1 Mecharoo 1 SelflessHero
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::SelflessHero));
        p1.emplace_back(Minion(MinionType::Mecharoo));
        p2.emplace_back(Minion(MinionType::Mecharoo));
        p2.emplace_back(Minion(MinionType::SelflessHero));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_LE(abs(result.stars()), 1);
        ASSERT_LE(result.count(), 1);
    }
    {
        // 2 FiendishServant
        // vs
        // 2 FiendishServant
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::FiendishServant));
        minions.emplace_back(Minion(MinionType::FiendishServant));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(2, result.turn());
    }
}

TEST(BattleTest, TierTwoDeathRattleTest) {
    {
        // 1 HarvestGolem vs 1 HarvestGolem
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::HarvestGolem));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 2 KaboomBot vs 2 KaboomBot
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::KaboomBot));
        minions.emplace_back(Minion(MinionType::KaboomBot));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(1, result.turn());
    }
    {
        // 2 KindlyGrandmother vs 2 KindlyGrandmother
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::KindlyGrandmother));
        minions.emplace_back(Minion(MinionType::KindlyGrandmother));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
    }
    {
        // 1 MountedRaptor vs 1 MountedRaptor
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::MountedRaptor));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_LE(abs(result.count()), 1);
    }
    {
        // 2 RatPack vs 2 RatPack
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::RatPack));
        minions.emplace_back(Minion(MinionType::RatPack));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_LE(abs(result.count()), 1);
    }
    {
        // 1 SpawnOfNZoth 1 HarvestGolem
        // vs
        // 1 SpawnOfNZoth 1 HarvestGolem
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::SpawnOfNZoth));
        minions.emplace_back(Minion(MinionType::HarvestGolem));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
    }
}

TEST(BattleTest, TierThreeDeathRattleTest) {
    {
        // 1 InfestedWolf vs 1 InfestedWolf
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::InfestedWolf));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 1 golden InfestedWolf vs 1 golden InfestedWolf
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::InfestedWolf, true));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 1 PilotedShredder vs 1 PilotedShredder
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::PilotedShredder));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_LE(abs(result.count()), 1);
    }
    {
        // 1 ReplicatingMenace vs 1 ReplicatingMenace
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::ReplicatingMenace));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(4, result.turn());
    }
    {
        // 1 TortollanShellraiser vs 1 TortollanShellraiser
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::TortollanShellraiser));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 1 TheBeast vs 1 TheBeast
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::TheBeast));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 1 TheBeast vs 1 TortollanShellraiser 1 InfestedWolf
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::TheBeast));
        p2.emplace_back(Minion(MinionType::TortollanShellraiser));
        p2.emplace_back(Minion(MinionType::InfestedWolf));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-2, result.stars());
        ASSERT_EQ(2, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 1 Imprisoner vs 1 Imprisoner
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::Imprisoner));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(2, result.turn());
    }
}

TEST(BattleTest, TierFourDeathRattleTest) {
    {
        // 1 PilotedSkyGolem vs 1 PilotedSkyGolem
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::PilotedSkyGolem));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        // we can not make sure that abs(count) < 1, e.g.,
        // 1/7 Baron Rivendare VS 3/3 Infested Wolf
    }
    {
        // 1 MechanoEgg vs 1 MechanoEgg
        // no one could attack
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::MechanoEgg));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(0, result.turn());
    }
    {
        // 1 TortollanShellraiser 1 MechanoEgg vs 1 TortollanShellraiser 1 MechanoEgg
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::TortollanShellraiser));
        minions.emplace_back(Minion(MinionType::MechanoEgg));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(10, result.turn());
    }
}

TEST(BattleTest, TierFiveDeathRattleTest) {
    {
        // 1 GoldrinnTheGreatWolf [taunt], 1 RatPack
        // vs
        // 1 GoldrinnTheGreatWolf [taunt], 1 RatPack
        std::vector<Minion> minions;
        Minion tauntGoldrinnTheGreatWolf(MinionType::GoldrinnTheGreatWolf);
        tauntGoldrinnTheGreatWolf.setTaunt(true);
        minions.emplace_back(tauntGoldrinnTheGreatWolf);
        minions.emplace_back(Minion(MinionType::RatPack));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(8, result.turn());
    }
    {
        // 1 KingBagurgle [taunt], 1 OldMurkEye
        // vs
        // 1 KingBagurgle [taunt], 1 OldMurkEye
        std::vector<Minion> minions;
        Minion tauntKingBagurgle(MinionType::KingBagurgle);
        tauntKingBagurgle.setTaunt(true);
        minions.emplace_back(tauntKingBagurgle);
        minions.emplace_back(Minion(MinionType::OldMurkEye));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 1 SatedThreshadon vs 1 SatedThreshadon
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::SatedThreshadon));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(5, result.turn());
    }
    {
        // 1 SavannahHighmane vs 1 SavannahHighmane
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::SavannahHighmane));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 1 Voidlord vs 1 Voidlord
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::Voidlord));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(12, result.turn());
    }
}

TEST(BattleTest, TierSixDeathRattleTest) {
    {
        // 1 Ghastcoiler vs 1 Ghastcoiler
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::Ghastcoiler));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
    }
    {
        // 1 KangorsApprentice vs 1 KangorsApprentice
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::KangorsApprentice));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 2 AnnoyOModule 1 KangorsApprentice
        // vs
        // 2 AnnoyOModule 1 KangorsApprentice
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::AnnoyOModule));
        minions.emplace_back(Minion(MinionType::AnnoyOModule));
        minions.emplace_back(Minion(MinionType::KangorsApprentice));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
    }
    {
        // 1 SneedsOldShredder vs 1 SneedsOldShredder
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::SneedsOldShredder));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
    }
}

TEST(BattleTest, RandomTest) {
    for (int i = 0; i < 100; i++) {
        // 1 MountedRaptor, 1 PilotedShredder, 1 PilotedSkyGolem, 1 Ghastcoiler, 1 SneedsOldShredder
        // vs
        // 1 MountedRaptor, 1 PilotedShredder, 1 PilotedSkyGolem, 1 Ghastcoiler, 1 SneedsOldShredder
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::MountedRaptor));
        minions.emplace_back(Minion(MinionType::PilotedShredder));
        minions.emplace_back(Minion(MinionType::PilotedSkyGolem));
        minions.emplace_back(Minion(MinionType::Ghastcoiler));
        minions.emplace_back(Minion(MinionType::SneedsOldShredder));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
    }
}

TEST(BattleTest, onAllySummonTest) {
    {
        // 1 Mecharoo [taunt], 1 CobaltGuardian
        // vs
        // 1 Mecharoo [taunt], 1 CobaltGuardian
        std::vector<Minion> minions;
        Minion tauntMecharoo(MinionType::Mecharoo);
        tauntMecharoo.setTaunt(true);
        minions.emplace_back(tauntMecharoo);
        minions.emplace_back(Minion(MinionType::CobaltGuardian));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(4, result.turn());
    }
    {
        // 1 4/4 RatPack [taunt], 1 PackLeader
        // vs
        // 1 4/4 RatPack [taunt], 1 PackLeader
        std::vector<Minion> minions;
        Minion tauntRatPack(MinionType::RatPack);
        tauntRatPack.buff(2, 2);
        tauntRatPack.setTaunt(true);
        minions.emplace_back(tauntRatPack);
        minions.emplace_back(Minion(MinionType::PackLeader));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(6, result.turn());
    }
    {
        // 1 4/4 RatPack [taunt], 2 PackLeader
        // vs
        // 1 4/4 RatPack [taunt], 2 PackLeader
        std::vector<Minion> minions;
        Minion tauntRatPack(MinionType::RatPack);
        tauntRatPack.buff(2, 2);
        tauntRatPack.setTaunt(true);
        minions.emplace_back(tauntRatPack);
        minions.emplace_back(Minion(MinionType::PackLeader));
        minions.emplace_back(Minion(MinionType::PackLeader));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(7, result.turn());
    }
    {
        // 1 4/4 RatPack [taunt], 1 5/5 MamaBear
        // vs
        // 1 4/4 RatPack [taunt], 1 5/5 MamaBear
        std::vector<Minion> minions;
        Minion tauntRatPack(MinionType::RatPack);
        tauntRatPack.buff(2, 2);
        tauntRatPack.setTaunt(true);
        minions.emplace_back(tauntRatPack);
        Minion mamaBear(MinionType::MamaBear);
        mamaBear.buff(1, 1);
        minions.emplace_back(mamaBear);
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(6, result.turn());
    }
}

TEST(BattleTest, onAllyAttackTest) {
    {
        // 1 AnnoyOTron, 1 FesterootHulk
        // vs
        // 1 AnnoyOTron, 1 FesterootHulk
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::AnnoyOTron));
        minions.emplace_back(Minion(MinionType::FesterootHulk));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(6, result.turn());
    }
    {
        // 1 Alleycat, 1 FesterootHulk
        // vs
        // 1 Alleycat, 1 FesterootHulk
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::Alleycat));
        minions.emplace_back(Minion(MinionType::FesterootHulk));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(4, result.turn());
    }
}

TEST(BattleTest, onAllyBreakDivineShieldTest) {
    {
        // 1 RighteousProtector, 1 BolvarFireblood
        // vs
        // 1 RighteousProtector, 1 BolvarFireblood
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::RighteousProtector));
        minions.emplace_back(Minion(MinionType::BolvarFireblood));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(5, result.turn());
    }
    {
        // 2 RighteousProtector, 1 BolvarFireblood
        // vs
        // 2 RighteousProtector, 1 BolvarFireblood
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::RighteousProtector));
        minions.emplace_back(Minion(MinionType::RighteousProtector));
        minions.emplace_back(Minion(MinionType::BolvarFireblood));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(6, result.turn());
    }
}

TEST(BattleTest, onAllyDeathTest) {
    {
        // 1 Alleycat, 1 ScavengingHyena
        // vs
        // 1 Alleycat, 1 ScavengingHyena
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::Alleycat));
        minions.emplace_back(Minion(MinionType::ScavengingHyena));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
    }
    {
        // 7 ScavengingHyena
        // vs
        // 7 ScavengingHyena
        std::vector<Minion> minions;
        for (int i = 0; i < 7; i++) {
            minions.emplace_back(Minion(MinionType::ScavengingHyena));
        }
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(7, result.turn());
    }
    {
        // 6 Alleycat vs 3 Imp [taunt], 1 SoulJuggler
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 6; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        for (int i = 0; i < 3; i++) {
            Minion imp(MinionType::Imp);
            imp.setTaunt(true);
            p2.emplace_back(imp);
        }
        p2.emplace_back(Minion(MinionType::SoulJuggler));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-3, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 3 Mecharoo vs 3 Imp [taunt], 1 SoulJuggler
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 3; i++) {
            p1.emplace_back(Minion(MinionType::Mecharoo));
        }
        for (int i = 0; i < 3; i++) {
            Minion imp(MinionType::Imp);
            imp.setTaunt(true);
            p2.emplace_back(imp);
        }
        p2.emplace_back(Minion(MinionType::SoulJuggler));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-3, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(3, result.turn());
    }
    {
        // 1 Mecharoo, 1 Junkbot
        // vs
        // 1 Mecharoo, 1 Junkbot
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::Mecharoo));
        minions.emplace_back(Minion(MinionType::Junkbot));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
    }
}

TEST(BattleTest, onDamagedTest) {
    {
        // 7 Alleycat vs 1 ImpGangBoss
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 7; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p2.emplace_back(Minion(MinionType::ImpGangBoss));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-1, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(7, result.turn());
    }
    {
        // 1 Alleycat vs 7 ImpGangBoss
        // because we have no empty slot, so there would be 7 ImpGangBoss alive in the end
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::Alleycat));
        for (int i = 0; i < 7; i++) {
            p2.emplace_back(Minion(MinionType::ImpGangBoss));
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-21, result.stars());
        ASSERT_EQ(7, result.count());
        ASSERT_EQ(1, result.turn());
    }
    {
        // 1 Alleycat vs 7 2/1 ImpGangBoss
        // because we have no empty slot, no imp is summoned even if the ImpGangBoss is dying,
        // so there would be 6 ImpGangBoss alive in the end
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::Alleycat));
        for (int i = 0; i < 7; i++) {
            Minion impGangBoss(MinionType::ImpGangBoss);
            impGangBoss.setHealth(1);
            p2.emplace_back(impGangBoss);
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-18, result.stars());
        ASSERT_EQ(6, result.count());
        ASSERT_EQ(1, result.turn());
    }
    {
        // 1 SecurityRover
        // vs
        // 1 SecurityRover
        std::vector<Minion> minions;
        minions.emplace_back(Minion(MinionType::SecurityRover));
        Board you(minions, HeroType::None, false, 1, 40);
        Board opponent(minions, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(9, result.turn());
    }
}

TEST(BattleTest, onKillTest) {
    {
        // 7 Alleycat vs 1 TheBoogeymonster
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 7; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p2.emplace_back(Minion(MinionType::TheBoogeymonster));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-4, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(7, result.turn());
    }
}

TEST(BattleTest, onOverKillTest) {
    {
        // 1 Alleycat vs 2 IronhideDirehorn
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::Alleycat));
        for (int i = 0; i < 2; i++) {
            p2.emplace_back(Minion(MinionType::IronhideDirehorn));
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-11, result.stars());
        ASSERT_EQ(3, result.count());
        ASSERT_EQ(1, result.turn());
    }
    {
        // 1 7/7 Alleycat vs 2 IronhideDirehorn
        std::vector<Minion> p1, p2;
        Minion alleycat(MinionType::Alleycat);
        alleycat.buff(6, 6);
        p1.emplace_back(alleycat);
        for (int i = 0; i < 2; i++) {
            p2.emplace_back(Minion(MinionType::IronhideDirehorn));
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-5, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(1, result.turn());
    }
    {
        // 1 Alleycat vs 7 IronhideDirehorn
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::Alleycat));
        for (int i = 0; i < 7; i++) {
            p2.emplace_back(Minion(MinionType::IronhideDirehorn));
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-35, result.stars());
        ASSERT_EQ(7, result.count());
        ASSERT_EQ(1, result.turn());
    }
}

TEST(BattleTest, WindfuryTest) {
    {
        // 2 Alleycat vs 1 MurlocWarleader [windfury]
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 2; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        Minion murlocWarleader(MinionType::MurlocWarleader);
        murlocWarleader.setWindfury(true);
        p2.emplace_back(murlocWarleader);
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-2, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 3 Alleycat vs 1 MurlocWarleader [windfury]
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 3; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        Minion murlocWarleader(MinionType::MurlocWarleader);
        murlocWarleader.setWindfury(true);
        p2.emplace_back(murlocWarleader);
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 2 Alleycat vs 1 ZappSlywick
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 2; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p2.emplace_back(Minion(MinionType::ZappSlywick));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-6, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 3 Alleycat vs 1 ZappSlywick
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 3; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p2.emplace_back(Minion(MinionType::ZappSlywick));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-6, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 6 Alleycat vs 2 ZappSlywick
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 6; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        for (int i = 0; i < 2; i++) {
            p2.emplace_back(Minion(MinionType::ZappSlywick));
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-12, result.stars());
        ASSERT_EQ(2, result.count());
        ASSERT_EQ(4, result.turn());
    }
    {
        // 5 Alleycat vs 1 golden ZappSlywick
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 5; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p2.emplace_back(Minion(MinionType::ZappSlywick, true));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-6, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(2, result.turn());
    }
}

TEST(BattleTest, CleaveTest) {
    {
        // 3 Alleycat vs 1 CaveHydra
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 3; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p2.emplace_back(Minion(MinionType::CaveHydra));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(-4, result.stars());
        ASSERT_EQ(1, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // taunt at first
        // 1 2/2 RatPack [taunt], 2 2/2 RatPack
        // vs
        // 1 CaveHydra, 4 Aleycat
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 3; i++) {
            p1.emplace_back(Minion(MinionType::RatPack));
            if (i == 0) {
                p1.back().setTaunt(true);
            }
        }
        p2.emplace_back(Minion(MinionType::CaveHydra));
        for (int i = 0; i < 4; i++) {
            p2.emplace_back(Minion(MinionType::Alleycat));
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
    }
    {
        // taunt at middle
        // 1 2/2 RatPack, 1 2/2 RatPack [taunt], 1 2/2 RatPack
        // vs
        // 1 CaveHydra, 4 Aleycat
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 3; i++) {
            p1.emplace_back(Minion(MinionType::RatPack));
            if (i == 1) {
                p1.back().setTaunt(true);
            }
        }
        p2.emplace_back(Minion(MinionType::CaveHydra));
        for (int i = 0; i < 4; i++) {
            p2.emplace_back(Minion(MinionType::Alleycat));
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(0, result.stars());
        ASSERT_EQ(0, result.count());
        ASSERT_EQ(7, result.turn());
    }
    {
        // taunt at last
        // 2 2/2 RatPack, 1 2/2 RatPack [taunt]
        // vs
        // 1 CaveHydra, 4 Alleycat
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 3; i++) {
            p1.emplace_back(Minion(MinionType::RatPack));
            if (i == 2) {
                p1.back().setTaunt(true);
            }
        }
        p2.emplace_back(Minion(MinionType::CaveHydra));
        for (int i = 0; i < 4; i++) {
            p2.emplace_back(Minion(MinionType::Alleycat));
        }
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
    }
    {
        // 1 Alleycat, 1 2/2 RatPack, 1 4/8 golden VulgarHomunculus [taunt], 1 2/4 ImpGangBoss
        // vs
        // 1 CaveHydra
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::Alleycat));
        p1.emplace_back(Minion(MinionType::RatPack));
        p1.emplace_back(Minion(MinionType::VulgarHomunculus, true));
        p1.emplace_back(Minion(MinionType::ImpGangBoss));
        p2.emplace_back(Minion(MinionType::CaveHydra));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(7, result.stars());
        ASSERT_EQ(5, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 4 Alleycat, 1 2/2 RatPack, 1 4/8 golden VulgarHomunculus [taunt], 1 2/4 ImpGangBoss
        // vs
        // 1 CaveHydra
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 4; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p1.emplace_back(Minion(MinionType::RatPack));
        p1.emplace_back(Minion(MinionType::VulgarHomunculus, true));
        p1.emplace_back(Minion(MinionType::ImpGangBoss));
        p2.emplace_back(Minion(MinionType::CaveHydra));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(9, result.stars());
        ASSERT_EQ(7, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 4 Alleycat, 1 2/2 RatPack, 1 4/8 golden VulgarHomunculus [taunt], 1 2/2 RatPack
        // vs
        // 1 CaveHydra
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 4; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p1.emplace_back(Minion(MinionType::RatPack));
        p1.emplace_back(Minion(MinionType::VulgarHomunculus, true));
        p1.emplace_back(Minion(MinionType::RatPack));
        p2.emplace_back(Minion(MinionType::CaveHydra));
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(7, result.stars());
        ASSERT_EQ(7, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 4 Alleycat, 1 golden RatPack, 1 4/8 golden VulgarHomunculus [taunt], 1 2/2 RatPack
        // vs
        // 1 4/4 golden CaveHydra
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 4; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p1.emplace_back(Minion(MinionType::RatPack, true));
        p1.emplace_back(Minion(MinionType::VulgarHomunculus, true));
        p1.emplace_back(Minion(MinionType::RatPack));
        Minion caveHydra(MinionType::CaveHydra, true);
        caveHydra.setHealth(4);
        p2.emplace_back(caveHydra);
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(7, result.stars());
        ASSERT_EQ(7, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 4 Alleycat, 1 golden RatPack, 1 4/4 KaboomBot [taunt], 1 2/2 RatPack
        // vs
        // 1 4/4 golden CaveHydra
        std::vector<Minion> p1, p2;
        for (int i = 0; i < 4; i++) {
            p1.emplace_back(Minion(MinionType::Alleycat));
        }
        p1.emplace_back(Minion(MinionType::RatPack, true));
        p1.emplace_back(Minion(MinionType::KaboomBot));
        p1.back().setTaunt(true);
        p1.emplace_back(Minion(MinionType::RatPack));
        Minion caveHydra(MinionType::CaveHydra, true);
        caveHydra.setHealth(4);
        p2.emplace_back(caveHydra);
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(7, result.stars());
        ASSERT_EQ(7, result.count());
        ASSERT_EQ(2, result.turn());
    }
    {
        // 1 Alleycat, 1 ReplicatingMenace, 1 golden RatPack [taunt], 1 2/2 RatPack
        // vs
        // 1 4/4 golden CaveHydra
        std::vector<Minion> p1, p2;
        p1.emplace_back(Minion(MinionType::Alleycat));
        p1.emplace_back(Minion(MinionType::ReplicatingMenace));
        p1.emplace_back(Minion(MinionType::RatPack, true));
        p1.back().setTaunt(true);
        p1.emplace_back(Minion(MinionType::RatPack));
        Minion caveHydra(MinionType::CaveHydra, true);
        caveHydra.setHealth(4);
        p2.emplace_back(caveHydra);
        Board you(p1, HeroType::None, false, 1, 40);
        Board opponent(p2, HeroType::None, false, 1, 40);
        Battle battle(you, opponent);
        auto result = battle.run();
        ASSERT_EQ(7, result.stars());
        ASSERT_EQ(7, result.count());
        ASSERT_EQ(2, result.turn());
    }
}

TEST(BattleTest, Test) {
}


int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    testing::InitGoogleTest(&argc, argv);
    FLAGS_logtostderr = true;
    FLAGS_v = 2;
    return RUN_ALL_TESTS();
}
