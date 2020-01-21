#pragma once

#include <vector>
#include <ostream>
#include "Enums.h"

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

    constexpr int attack(bool golden) const {
        return golden ? attack_ * 2 : attack_;
    }

    constexpr int health(bool golden) const {
        return golden ? health_ * 2 : health_;
    }
};
