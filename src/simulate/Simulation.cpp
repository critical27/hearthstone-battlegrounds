#include "Simulation.h"

void Simulation::run(int count, bool optimize) {
    for (int i = 0; i < count; i++) {
        Battle battle(you_, opponent_);
        results_.emplace_back(battle.run());
    }
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
    int sum = 0;
    std::for_each(results_.begin(), results_.end(),[&] (const BattleResult& result) {
        sum += result.damage();
    });
    return (float) sum / results_.size();
}
