#include "Board.h"
#include <glog/logging.h>
#include "utils/enums.h"
#include "utils/random.h"

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << board.toString();
    return os;
}

std::string Board::toString() const {
    std::stringstream ss;
    ss << "\n";
    if (level_) {
        ss << "level " << level_ << "\n";
    }
    if (health_) {
        ss << "health " << health_ << "\n";
    }
    if (useHeroPower_) {
        ss << "hero power " << hero_ << "\n";
    }
    for (const auto& minion : minions()) {
        ss << "* " << minion.toString() << "\n";
    }
    return ss.str();
}
