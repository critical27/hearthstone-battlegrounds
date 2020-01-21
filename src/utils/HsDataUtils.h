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
        auto picked = rand(0, OneCostMinions.size());
        return OneCostMinions[picked];
    }

    static MinionType randomTwoCostMinion() {
        auto picked = rand(0, TwoCostMinions.size());
        return TwoCostMinions[picked];
    }

    static MinionType randomFourCostminion() {
        auto picked = rand(0, FourCostMinions.size());
        return FourCostMinions[picked];
    }

    static MinionType randomDeathRattleMinion() {
        auto picked = rand(0, DeathRattleMinions.size());
        return DeathRattleMinions[picked];
    }

    static MinionType randomLegendaryMinion() {
        auto picked = rand(0, LengendaryMinions.size());
        return LengendaryMinions[picked];
    }
};

/*
// additional MinionInfo
constexpr bool is_aura_minion(MinionType t) {
    return t == MinionType::DireWolfAlpha
           || t == MinionType::MurlocWarleader
           || t == MinionType::OldMurkEye
           || t == MinionType::PhalanxCommander
           || t == MinionType::Siegebreaker
           || t == MinionType::MalGanis;
}
*/
