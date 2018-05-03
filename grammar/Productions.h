#pragma once

#include "Symbol.h"
#include "NonTerminal.h"

#include <unordered_map>
#include <vector>

class Productions {
    public:
        typedef std::vector<Symbol> symbol_sequence;
        symbol_sequence operator[](NonTerminal n) { return data[n]; }
    private:
        static std::unordered_map<NonTerminal, std::vector<symbol_sequence>> data;
};