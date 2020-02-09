#include "Board.h"
#include <glog/logging.h>
#include "utils/Enums.h"
#include "utils/Random.h"

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << board.toString();
    return os;
}

std::string Board::toString() const {
    std::stringstream ss;
    ss << "\n";
    ss << "level " << level_ << ", health " << health_ << "\n";
    if (useHeroPower_) {
        // doodle: show hero name instead
        ss << "hero power " << static_cast<size_t>(hero_) << "\n";
    }
    for (const auto& minion : minions()) {
        ss << "* " << minion.toSimpleString() << "\n";
    }
    return ss.str();
}
