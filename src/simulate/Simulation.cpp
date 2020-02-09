#include "Simulation.h"
#include <limits.h>

void Simulation::simulate(int count, bool optimize){
    if (optimize) {
        auto minions = you_.minions();
        std::sort(minions.begin(), minions.end());
        auto bestOrder = minions;
        // max damage would be -(6 * 7) = -42 at most
        float bestDamage = -(6 * BOARD_SIZE);
        do {
            you_.setMinions(minions);
            float damage = run(count);
            LOG(INFO) << damage;
            if (damage > bestDamage) {
                bestOrder = minions;
                bestDamage = damage;
            }
        } while (std::next_permutation(minions.begin(), minions.end()));

        you_.setMinions(bestOrder);
        LOG(INFO) << "Best damage " << bestDamage << ", board: " << you_.toString();
    } else {
        run(count);
    }
}

float Simulation::run(int count) {
    results_.clear();
    for (int i = 0; i < count; i++) {
        Battle battle(you_, opponent_);
        results_.emplace_back(battle.run());
    }
    return meanDamage();
}

std::string Simulation::result() {
    return "Mean damage: " + std::to_string(meanDamage());
}

std::string Simulation::detail() {
    std::stringstream ss;
    ss << "\n";
    for (const auto& result : results_) {
        ss << result.toString() << "\n";
    }
    return ss.str();
}

float Simulation::meanDamage() {
    float sum = 0;
    std::for_each(results_.begin(), results_.end(),[&] (const BattleResult& result) {
        sum += result.damage();
    });
    return sum / results_.size();
}
