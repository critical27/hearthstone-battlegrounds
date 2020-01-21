#pragma once

#include <cstring>
#include <iostream>
#include "Minion.h"

// -----------------------------------------------------------------------------
// Error handling
// -----------------------------------------------------------------------------
struct ErrorHandler {
    std::ostream& os_;
    const char* filename_;
    int lineNo_{0};

    ErrorHandler(std::ostream& os, const char* filename)
        : os_(os), filename_(filename) {}

    std::ostream& operator()() const {
        if (lineNo_) {
            return os_ << filename_ << ":" << lineNo_ << ": Error: ";
        } else {
            return os_ << "Error: ";
        }
    }
};

struct StringParser {
    const char* data_;
    ErrorHandler const& handler_;

    StringParser(const char* data, const ErrorHandler& handler)
        : data_(data), handler_(handler) {}

    // Matching/parsing functions
    // Convention: match_X does nothing on failure
    // parse_X shows error message on failure

    // try to match a string, if there is a match, advance
    bool match(const char* query) {
        const char* after = match_name_or_prefix(data_, query);
        if (after) {
            data_ = after;
            return true;
        } else {
            return false;
        }
    }

    bool match_exact(const char* query) {
        const char* after = data_;
        while (*query) {
            if (*after != *query) {
                return false;
            }
            ++after; ++query;
        }
        data_ = after;
        return true;
    }

    bool match_int(int& out) {
        int n = 0;
        if (sscanf(data_, "%d%n", &out, &n) >= 1) {
            data_ += n;
            return true;
        } else {
            return false;
        }
    }

    bool match_string(std::string& out, char end=0, bool allow_empty=true) {
        const char* after = data_;
        while (*after && *after != end) ++after;
        if (allow_empty || after != data_) {
            out.assign(data_,after);
            data_ = after;
            return true;
        } else {
            return false;
        }
    }

    bool match_end() {
        const char* at = data_;
        while (*data_) {
            if (*data_ == '#') break; // comment
            if (!isspace(*data_)) {
                data_ = at;
                return false;
            }
            ++data_;
        }
        return true;
    }

    void skip_ws() {
        while (isspace(*data_)) {
            ++data_;
        }
    }

    bool skip_until(const char* query) {
        const char* pos = strstr(data_, query);
        if (pos) {
            data_ = pos + strlen(query);
            return true;
        } else {
            return false;
        }
    }

    // skip all characters up to and including the query string
    bool skip_until(char query) {
        const char* pos = strchr(data_,query);
        if (pos) {
            data_ = pos + 1;
            return true;
        } else {
            return false;
        }
    }

    // Error raising versions

    bool parse_exact(const char* query) {
        if (match_exact(query)) {
            return true;
        }
        expected(query);
        return false;
    }

    bool parse_end() {
        if (match_end()) {
            return true;
        }
        expected("end of line");
        return false;
    }

    bool parse_int(int& out) {
        if (match_int(out)) {
            return true;
        }
        expected("number");
        return false;
    }

    bool parse_positive(int& out) {
        const char* at = data_;
        if (match_int(out) && out > 0) {
            return true;
        }
        data_ = at;
        expected("positive number");
        return false;
    }
    
    bool parse_non_negative(int& out) {
        const char* at = data_;
        if (match_int(out) && out >= 0) {
            return true;
        }
        data_ = at;
        expected("non-negative number");
        return false;
    }

    bool parse_string(std::string& out, char end=0) {
        if (match_string(out,end)) {
            return true;
        }
        expected("string");
        return false;
    }

    // Errors

    void unknown(const char* what) const {
        handler_() << "Unknown " << what << ": " << next_token() << std::endl;
    }

    void expected(const char* what) const {
        handler_() << "Expected " << what << ", instead of " << next_token() << std::endl;
    }

    // Peeking/queries

    char peek() const {
        return *data_;
    }

    bool end() const {
        return !*data_;
    }

    std::string next_token(char endChar = 0) const {
        const char* start = data_;
        while (isspace(*start)) {
            ++start;
        }
        if (!*start) {
            return "<end of line>";
        }
        const char* end = start;
        while (!is_token_end(*end) && *end != endChar) {
            ++end;
        }
        return std::string(start,end);
    }
};


// -----------------------------------------------------------------------------
// Name lookup utilities
// -----------------------------------------------------------------------------
bool ignored_char(char x) {
    return !isalpha(x) && !isdigit(x) && x != '/';
    //return isspace(x) || x == '\'' || x == '-' || x == '_' || x == ':';
}

bool is_word_end(char x) {
    return x == 0 || isspace(x) || x == ',' || x == ':';
}

bool is_token_end(char x) {
    return x == 0 || x == ',';
}

// compare strings, ignoring case and allow skipping of joining characters
// b is the query
bool match_name(const char* a, const char* b) {
    while (*a && ignored_char(*a)) {
        ++a;
    }
    while (*b && ignored_char(*b)) {
        ++b;
    }
    while (*a && *b) {
        if (tolower(*a) != tolower(*b)) {
            return false;
        }
        ++a;
        ++b;
        while (*a && ignored_char(*a)) {
            ++a;
        }
        while (*b && ignored_char(*b)) {
            ++b;
        }
    }
    return !*a && !*b;
}

// compare strings, allow a to be longer (ending in a word ending charater)
// ignore joining characters in the middle of the query, and space at the start
// return point in a, or nullptr if no match
const char* match_name_or_prefix(const char* a, const char* b) {
    while (*a && isspace(*a)) {
        ++a;
    }
    while (*b && isspace(*b)) {
        ++b;
    }
    while (*a && *b) {
        if (tolower(*a) != tolower(*b)) {
            return nullptr;
        }
        ++a;
        ++b;
        if (*b) {
            while (*a && ignored_char(*a)) {
                ++a;
            }
            while (*b && ignored_char(*b)) {
                ++b;
            }
        }
    }
    if (!*b && is_word_end(*a)) {
        return a;
    } else {
        return nullptr;
    }
}

// -----------------------------------------------------------------------------
// Parsers
// -----------------------------------------------------------------------------

bool match_tribe(StringParser& in, Tribe& out) {
    for (int i = 0; i < TRIBE_COUNT; ++i) {
        if (in.match(gTribeName[i])) {
            out = static_cast<Tribe>(i);
            return true;
        }
    }
    return false;
}

bool match_minion_type(StringParser& in, MinionType& out) {
    for (int i = 0; i < MINIONTYPE_COUNT; ++i) {
        if (in.match(gMinionInfo[i].name_.c_str())) {
            out = static_cast<MinionType>(i);
            return true;
        }
    }
    return false;
}

bool match_hero_type(StringParser& in, HeroType& out) {
    for (int i = 0; i < HEROTYPE_COUNT; ++i) {
        if (in.match(gHeroInfo[i].name_.c_str()) ||
            in.match(gHeroInfo[i].heroPower_.name_.c_str())) {
            out = static_cast<HeroType>(i);
            return true;
        }
    }
    return false;
}

bool parse_minion_type(StringParser& in, MinionType& out) {
    if (!match_minion_type(in, out)) {
        in.unknown("minion type");
        return false;
    }
    return true;
}

bool parse_hero_type(StringParser& in, HeroType& out) {
    if (!match_hero_type(in, out)) {
        in.unknown("hero / hero power");
        return false;
    }
    return true;
}

// Parse one or more buffs, apply them to a minion
bool parse_buffs(StringParser& in, Minion& minion) {
    // read buffs
    while (true) {
        in.skip_ws();
        if (in.peek() == '+' || in.peek() == '-') {
            const char* at = in.data_;
            int attack = 0;
            if (!in.parse_int(attack)) {
                return false;
            }
            if (in.match_exact("/")) {
                int health = 0;
                if (in.match_int(health)) {
                    minion.buff(attack, health);
                } else {
                    in.data_ = at;
                    in.unknown("minion buff");
                    return false;
                }
            } else if (in.match("attack")) {
                minion.buff(attack, 0);
            } else if (in.match("health")) {
                minion.buff(0, attack);
            } else {
                in.data_ = at;
                in.unknown("minion buff");
                return false;
            }
        } else if (in.match("taunt")) {
            minion.taunt_ = true;
        } else if (in.match("divine shield")) {
            minion.divineShield_ = true;
        } else if (in.match("poison") || in.match("poisonous")) {
            minion.poison_ = true;
        } else if (in.match("windfury")) {
            minion.windfury_ = true;
        } else if (in.match("reborn")) {
            minion.reborn_ = true;
        } else if (in.match("microbots")) {
            minion.add_deathrattle_microbots();
        } else if (in.match("golden microbots")) {
            minion.add_deathrattle_golden_microbots();
        } else if (in.match("plants")) {
            minion.add_deathrattle_plants();
        } else if (in.match("Annoy-o-Module")) {
            minion.taunt_ = true;
            minion.divineShield_ = true;
            minion.buff(2, 4);
        } else if (in.match("golden Annoy-o-Module")) {
            minion.taunt_ = true;
            minion.divineShield_ = true;
            minion.buff(4, 8);
        } else if (in.match("Replicating Menace")) {
            minion.buff(3, 1);
            minion.add_deathrattle_microbots();
        } else if (in.match("golden Replicating Menace")) {
            minion.buff(6, 2);
            minion.add_deathrattle_golden_microbots();
        } else if (in.end()) {
            in.expected("a buff");
            return false;
        } else {
            in.unknown("minion buff");
            return false;
        }
        if (!in.match(",")) {
            return true;
        }
    }
}

bool parse_minion(StringParser& in, Minion& minion) {
    int attack = -1, health = -1;
    bool golden = false;
    // read stats
    in.skip_ws();
    if (isdigit(in.peek())) {
        const char* at = in.data_;
        if (!(in.match_int(attack) && in.match_exact("/") && in.match_int(health))) {
            in.data_ = at;
            in.expected("'attack/health'");
            return false;
        }
    }
    // golden?
    if (in.match("gold") || in.match("golden")) {
        golden = true;
    }
    // find minion by name
    MinionType type;
    in.skip_ws();
    if (in.end()) {
        in.handler_() << "Expected minion, see help command for the syntax" << std::endl;
        return false;
    }
    if (!parse_minion_type(in, type)) {
        return false;
    }
    // construct
    minion = Minion(type, golden);
    minion.attack_ = attack;
    minion.health_ = health;

    // buff?
    if (in.match(",")) {
        if (!parse_buffs(in, minion)) {
            return false;
        }
    }
    return true;
}