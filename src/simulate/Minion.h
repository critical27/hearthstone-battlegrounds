#pragma once

#include <glog/logging.h>
#include "utils/MinionInfo.h"
#include "utils/HsDataUtils.h"

const int BOARD_SIZE = 7;

class Battle;
class BattleMinions;

#define COMP(VAR, FIELD) \
    if (FIELD != VAR.FIELD) { \
        return FIELD < other.FIELD; \
    }

// -----------------------------------------------------------------------------
// Minion instances
// -----------------------------------------------------------------------------

class Minion {
public:
    Minion(MinionType type, bool golden = false)
        : minionType_(type), minionInfo_(HsDataUtils::minionInfo(type)), golden_(golden),
          attack_(minionInfo_.attack(golden)), health_(minionInfo_.health(golden)),
          taunt_(minionInfo_.taunt_), divineShield_(minionInfo_.divineShield_), poison_(minionInfo_.poison_),
          windfury_(minionInfo_.windfury_), cleave_(minionInfo_.cleave_), reborn_(false),
          deathrattle_murlocs_(0), deathrattle_microbots_(0), deathrattle_golden_microbots_(0),
          deathrattle_plants_(0),
          attackAura_(0), healthAura_(0) {
        init();
    }

    Minion(MinionType type, bool golden, int attack, int health)
        : Minion(type, golden) {
        setAttack(attack);
        setHealth(health);
    }

private:
    void init() {
        if (minionType_ == MinionType::ZappSlywick && golden_) {
            megaWindFury_ = true;
        }
    }

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
    bool megaWindFury_{false};
    bool cleave_{false};
    bool reborn_{false};                        // for lich king

    int deathrattle_murlocs_{0};                // for giantfin
    int deathrattle_microbots_{0};
    int deathrattle_golden_microbots_{0};
    int deathrattle_plants_{0};                 // from adapt
    int attackAura_{0};
    int healthAura_{0};

    // Minion dynamic info
    bool alive_{true};

public:

    friend std::ostream& operator<<(std::ostream& os, Minion& minion);

    bool operator<(const Minion& other) const {
        COMP(other, minionType_);
        COMP(other, golden_);
        COMP(other, attack_);
        COMP(other, health_);
        COMP(other, taunt_);
        COMP(other, divineShield_);
        COMP(other, poison_);
        COMP(other, windfury_);
        COMP(other, megaWindFury_);
        COMP(other, cleave_);
        COMP(other, reborn_);
        COMP(other, deathrattle_murlocs_);
        COMP(other, deathrattle_microbots_);
        COMP(other, deathrattle_golden_microbots_);
        COMP(other, attackAura_);
        COMP(other, healthAura_);
        return 0;
    }

    std::string toString() const;
    std::string toSimpleString() const;

    const std::string& name() const {
        return minionInfo_.name_;
    }

    MinionType minionType() const {
        return minionType_;
    }

    bool isGolden() const {
        return golden_;
    }

    int stars() const {
        return minionInfo_.stars_;
    }

    int attack() const {
        return attack_;
    }

    Minion& setAttack(int value) {
        attack_ = value;
        return *this;
    }

    int health() const {
        return health_;
    }

    Minion& setHealth(int value) {
        health_ = value;
        return *this;
    }

    bool isTribe(Tribe t) const {
        return minionInfo_.tribe_ == t;
    }

    bool isAlive() const {
        return health_ > 0;
    }

    int attackTimes() const {
        if (isMegaWindfury()) {
            return 4;
        } else if (isWindfury()) {
            return 2;
        } else {
            return 1;
        }
    }

    bool isTaunt() const {
        return taunt_;
    }

    Minion& setTaunt(bool value) {
        taunt_ = value;
        return *this;
    }

    bool isDivineShield() const {
        return divineShield_;
    }

    Minion& setDivineShield(bool value) {
        divineShield_ = value;
        return *this;
    }

    bool isPoison() const {
        return poison_;
    }

    Minion& setPoison(bool value) {
        poison_ = value;
        return *this;
    }

    bool isWindfury() const {
        return windfury_;
    }

    bool isMegaWindfury() const {
        return megaWindFury_;
    }

    Minion& setWindfury(bool value) {
        windfury_ = value;
        return *this;
    }

    bool isCleave() const {
        return cleave_;
    }

    bool isReborn() const {
        return reborn_;
    }

    int doubleIfGolden(int amount) const {
        return isGolden() ? 2 * amount : amount;
    }

    Minion& buff(int attack, int health) {
        this->attack_ += attack;
        this->health_ += health;
        return *this;
    }

    // buff by the magnetic minion
    Minion& buffByMagnetic(Minion m) {
        this->attack_ += m.attack_;
        this->health_ += m.health_;
        this->taunt_ |= m.taunt_;
        this->divineShield_ |= m.divineShield_;
        this->poison_ |= m.poison_;
        this->windfury_ |= m.windfury_;
        this->cleave_ |= m.cleave_;
        this->reborn_ |= m.reborn_;
        this->attackAura_ += m.attackAura_;
        this->healthAura_ += m.healthAura_;
        this->deathrattle_murlocs_ = std::max(this->deathrattle_murlocs_, m.deathrattle_murlocs_);
        this->addDeathrattleMicrobots(m.deathrattle_microbots_);
        this->addDeathrattleGoldenMicrobots(m.deathrattle_golden_microbots_);
        this->addDeathrattlePlants(m.deathrattle_plants_);
        return *this;
    }

    Minion newCopy() const {
        return Minion(minionType_, golden_);
    }

    Minion rebornCopy() const {
        Minion copy(minionType_, golden_);
        copy.setHealth(1);
        return copy;
    }

    Minion& addDeathrattleMicrobots(int n = 3) {
        this->deathrattle_microbots_ = std::min(this->deathrattle_microbots_ + n, BOARD_SIZE);
        return *this;
    }

    Minion& addDeathrattleGoldenMicrobots(int n = 3) {
        this->deathrattle_golden_microbots_ = std::min(this->deathrattle_golden_microbots_ + n, BOARD_SIZE);
        return *this;
    }

    Minion& addDeathrattlePlants(int n = 2) {
        this->deathrattle_plants_ = std::min(this->deathrattle_plants_ + n, BOARD_SIZE);
        return *this;
    }

    void auraBuff(int attack, int health) {
        this->attack_ += attack;
        this->health_ += health;
        this->attackAura_ += attack;
        this->healthAura_ += health;
    }

    void clearAuraBuff() {
        if (attack_ > attackAura_) {
            attack_ -= attackAura_;
        }
        // aura buff won't kill a minion
        if (health_ > healthAura_) {
            health_ -= this->healthAura_;
        }
        this->attackAura_ = 0;
        this->healthAura_ = 0;
    }

    bool computeAuras(size_t pos, BattleMinions* you, BattleMinions* opponent);

    // bool recompute_aura_from(Board& board, int pos, Board const* enemy_board = nullptr);
    void onAllySummon(Battle* battle, size_t player, Minion& summoned, bool played);
    void onAllyAttack(Battle* battle, size_t player);
    void onAllyBreakDivineShield(Battle* battle, size_t player);
    void onAllyDeath(Battle* battle, size_t player, const Minion& deadMinion);
    void onDamaged(Battle* battle, size_t player, size_t pos);
    void onKill(Battle* battle, size_t player);
    void onOverKill(Battle* battle, size_t player, size_t pos);
};

