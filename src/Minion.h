#pragma once

#include "MinionInfo.h"
#include <algorithm>

using std::min;
using std::max;

// -----------------------------------------------------------------------------
// Minion instances
// -----------------------------------------------------------------------------

struct Minion {
public:
    Minion(MinionType type, bool golden = false)
        : minionType_(type), minionInfo_(info(type)), golden_(golden),
          attack_(minionInfo_.attack_for(golden)), health_(minionInfo_.health_for(golden)),
          taunt_(minionInfo_.taunt_), divineShield_(minionInfo_.divineShield_), poison_(minionInfo_.poison_),
          windfury_(minionInfo_.windfury_), reborn_(false),
          deathrattle_murlocs_(0), deathrattle_microbots_(0), deathrattle_golden_microbots_(0),
          deathrattle_plants_(0),
          attackAura_(0), healthAura_(0) {}

    // Minion static info
    MinionType minionType_{MinionType::None};
    MinionInfo minionInfo_;
    bool golden_{false};

    int attack_{0};
    int health_{0};

    bool taunt_{false};
    bool divineShield_{false};
    bool poison_{false};
    bool windfury_{false};
    bool reborn_{false};                        // for lich king

    int deathrattle_murlocs_{0};                // for giantfin
    int deathrattle_microbots_{0};
    int deathrattle_golden_microbots_{0};
    int deathrattle_plants_{0};                 // from adapt
    int attackAura_{0};
    int healthAura_{0};

    // Minion dynamic info
    bool exists_{true};

public:
    friend std::ostream& operator<<(std::ostream& os, const Minion& minion);

    const std::string name() const {
        return minionInfo_.name_;
    }

    int stars() const {
        return minionInfo_.stars_;
    }

    bool exists() const {
        return exists_;
    }

    /*
    Minion new_copy() const {
        return Minion(minionType_, golden_);
    }

    Minion reborn_copy() const {
        Minion copy(minionType_, golden_);
        copy.health_ = 1;
        return copy;
    }

    void buff(int attack, int health) {
        this->attack_ += attack;
        this->health_ += health;
    }

    void buff(Minion const &b) {
        // buff by the stats of the reference minion (want b.type == None)
        this->attack_ += b.attack_;
        this->health_ += b.health_;
        this->taunt_ |= b.taunt_;
        this->divineShield_ |= b.divineShield_;
        this->poison_ |= b.poison_;
        this->windfury_ |= b.windfury_;
        this->reborn_ |= b.reborn_;
        this->attackAura_ += b.attackAura_;
        this->healthAura_ += b.healthAura_;
        this->deathrattle_murlocs_ = max(this->deathrattle_murlocs_, b.deathrattle_murlocs_);
        this->add_deathrattle_microbots(b.deathrattle_microbots_);
        this->add_deathrattle_golden_microbots(b.deathrattle_golden_microbots_);
        this->add_deathrattle_plants(b.deathrattle_plants_);
    }

    void aura_buff(int attack, int health) {
        this->attack_ += attack;
        this->health_ += health;
        this->attackAura_ += attack;
        this->healthAura_ += health;
    }

    void clear_aura_buff() {
        this->attack_ -= this->attackAura_;
        this->health_ -= this->healthAura_;
        this->attackAura_ = 0;
        this->healthAura_ = 0;
    }

    void add_deathrattle_microbots(int n = 3) {
        this->deathrattle_microbots_ = min(this->deathrattle_microbots_ + n, 7);
    }

    void add_deathrattle_golden_microbots(int n = 3) {
        this->deathrattle_golden_microbots_ = min(this->deathrattle_golden_microbots_ + n, 7);
    }

    void add_deathrattle_plants(int n = 2) {
        this->deathrattle_plants_ = min(this->deathrattle_plants_ + n, 7);
    }
     */
};

std::ostream& operator<<(std::ostream &os, const Minion& minion) {
    os << minion.attack_ << "/" << minion.health_ << " ";
    if (minion.golden_) {
        os << "Golden ";
    }
    os << minion.name();
    if (minion.taunt_) {
        os << ", taunt";
    }
    if (minion.divineShield_) {
        os << ", divine shield";
    }
    if (minion.poison_) {
        os << ", poisonous";
    }
    if (minion.windfury_) {
        os << ", windfury";
    }
    if (minion.reborn_) {
        os << ", reborn";
    }
    for (int i = 0; i < minion.deathrattle_microbots_; i += 3) {
        os << ", microbots";
    }
    for (int i = 0; i < minion.deathrattle_golden_microbots_; i += 3) {
        os << ", golden microbots";
    }
    for (int i = 0; i < minion.deathrattle_plants_; i += 2) {
        os << ", plants";
    }
    return os;
}

