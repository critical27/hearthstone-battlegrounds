#pragma once

#include "enums.h"
#include <vector>
#include <ostream>

// -----------------------------------------------------------------------------
// Tribe utilities and MinionInfo
// -----------------------------------------------------------------------------

constexpr bool hasTribe(Tribe tribe, Tribe query) {
    return tribe == Tribe::All || tribe == query;
}

extern const char *gTribeName[TRIBE_COUNT];

inline const char *name(Tribe t) {
    return gTribeName[static_cast<int>(t)];
}

inline std::ostream &operator<<(std::ostream &s, Tribe t) {
    return s << name(t);
}

// -----------------------------------------------------------------------------
// Minion type MinionInfo
// -----------------------------------------------------------------------------

constexpr int double_if_golden(int x, bool golden) {
    return golden ? 2 * x : x;
}

// Minion MinionInfo
struct MinionInfo {
    MinionInfo(const std::string &name, const std::vector<std::string> &hsId,
               int stars, Tribe tribe, int attack, int health,
               bool taunt, bool divineShield, bool poison, bool windfury, bool cleave,
               bool battlecry, bool valid)
        : name_(name), hsId_(hsId), stars_(stars), tribe_(tribe), attack_(attack), health_(health),
          taunt_(taunt), divineShield_(divineShield), poison_(poison), windfury_(windfury), cleave_(cleave),
          battlecry_(battlecry), valid_(valid) {}

    std::string name_;
    std::vector<std::string> hsId_;                             // internal id used by hearthstone, for normal and golden
    int stars_;
    Tribe tribe_;
    int attack_, health_;
    bool taunt_, divineShield_, poison_, windfury_, cleave_;
    bool battlecry_;
    bool valid_;                                                // wheterh is still in game

    constexpr int attack_for(bool golden) const {
        return double_if_golden(attack_, golden);
    }

    constexpr int health_for(bool golden) const {
        return double_if_golden(health_, golden);
    }
};

// All information on the minions
extern const MinionInfo gMinionInfo[MINIONTYPE_COUNT];

inline MinionInfo const &info(MinionType type) {
    return gMinionInfo[static_cast<int>(type)];
}

// Query information about known minions
inline std::string name(MinionType type) { return info(type).name_; }

inline Tribe tribe(MinionType type) { return info(type).tribe_; }

inline bool hasTribe(MinionType type, Tribe query) { return hasTribe(tribe(type), query); }

inline int stars(MinionType type) { return info(type).stars_; }

/*
// random minion spawning
MinionType random_one_cost_minion(BattleRNG &rng, int player);

MinionType random_two_cost_minion(BattleRNG &rng, int player);

MinionType random_four_cost_minion(BattleRNG &rng, int player);

MinionType random_deathrattle_minion(BattleRNG &rng, int player);

MinionType random_legendary_minion(BattleRNG &rng, int player);
 */

// additional MinionInfo
constexpr bool is_aura_minion(MinionType t) {
    return t == MinionType::DireWolfAlpha
           || t == MinionType::MurlocWarleader
           || t == MinionType::OldMurkEye
           || t == MinionType::PhalanxCommander
           || t == MinionType::Siegebreaker
           || t == MinionType::MalGanis;
}

// -----------------------------------------------------------------------------
// Hero power MinionInfo
// -----------------------------------------------------------------------------

struct HeroPowerInfo {
    std::string name_;
    std::string hsId_;
};

struct HeroInfo {
    std::string name_;
    std::string hs_id_;
    HeroPowerInfo hero_power_;
};

extern const HeroInfo gHeroInfo[HEROTYPE_COUNT];

inline std::string name(HeroType x) {
    return gHeroInfo[static_cast<int>(x)].name_;
}

inline std::ostream &operator<<(std::ostream &s, HeroType x) {
    return s << name(x);
}
