#include <iostream>
#include <sstream>
#include "Minion.h"

std::ostream& operator<<(std::ostream& os, const Minion& minion) {
    os << minion.toString();
    return os;
}

std::string Minion::toSimpleString() const {
    std::stringstream ss;
    ss << attack_ << "/" << health_ << " ";
    ss << name();
    if (cleave_) {
        ss << " [Cleave]";
    }
    if (windfury_) {
        ss << " [WindFury]";
    }
    return ss.str();
}

std::string Minion::toString() const {
    std::stringstream ss;
    ss << attack_ << "/" << health_ << " ";
    if (golden_) {
        ss << "Golden ";
    }
    ss << name();
    if (taunt_) {
        ss << ", taunt";
    }
    if (divineShield_) {
        ss << ", divine shield";
    }
    if (poison_) {
        ss << ", poisonous";
    }
    if (windfury_) {
        ss << ", windfury";
    }
    if (reborn_) {
        ss << ", reborn";
    }
    for (int i = 0; i < deathrattle_microbots_; i += 3) {
        ss << ", microbots";
    }
    for (int i = 0; i < deathrattle_golden_microbots_; i += 3) {
        ss << ", golden microbots";
    }
    for (int i = 0; i < deathrattle_plants_; i += 2) {
        ss << ", plants";
    }
    return ss.str();
}
