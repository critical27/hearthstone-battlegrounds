#pragma once

#include "Enums.h"
#include "MinionInfo.h"
#include "Random.h"

struct HeroPowerInfo {
    std::string name_;
    std::string hsId_;
};

struct HeroInfo {
    std::string name_;
    std::string hsId_;
    HeroPowerInfo heroPower_;
};

class HsDataUtils {
public:
    static const std::vector<std::string> TribeNames;
    static const std::vector<MinionInfo> MinionInfos;
    static const std::vector<MinionType> OneCostMinions;
    static const std::vector<MinionType> TwoCostMinions;
    static const std::vector<MinionType> FourCostMinions;
    static const std::vector<MinionType> DeathRattleMinions;
    static const std::vector<MinionType> LengendaryMinions;
    static const std::vector<MinionType> DemonMinions;
    static const std::vector<HeroInfo> HeroInfos;

    static std::string tribeName(Tribe t) {
        return TribeNames[static_cast<size_t>(t)];
    }

    static MinionInfo minionInfo(MinionType minionType) {
        return MinionInfos[static_cast<size_t>(minionType)];
    }

    static HeroInfo heroInfo(HeroType hero) {
        return HeroInfos[static_cast<size_t>(hero)];
    }

    static MinionType randomOneCostMinion() {
        auto picked = rand(0, OneCostMinions.size() - 1);
        return OneCostMinions[picked];
    }

    static MinionType randomTwoCostMinion() {
        auto picked = rand(0, TwoCostMinions.size() - 1);
        return TwoCostMinions[picked];
    }

    static MinionType randomFourCostminion() {
        auto picked = rand(0, FourCostMinions.size() - 1);
        return FourCostMinions[picked];
    }

    static MinionType randomDeathRattleMinion() {
        auto picked = rand(0, DeathRattleMinions.size() - 1);
        return DeathRattleMinions[picked];
    }

    static MinionType randomLegendaryMinion() {
        auto picked = rand(0, LengendaryMinions.size() - 1);
        return LengendaryMinions[picked];
    }

    static MinionType randomDemonMinion() {
        auto picked = rand(0, DemonMinions.size() - 1);
        return DemonMinions[picked];
    }
};
