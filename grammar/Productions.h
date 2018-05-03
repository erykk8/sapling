#pragma once

#include "Symbol.h"
#include "NonTerminal.h"

#include <map>
#include <memory>
#include <vector>

class Productions {
    public:
        typedef std::vector<std::shared_ptr<Symbol>> symbol_sequence;
        const std::vector<symbol_sequence> operator[](NonTerminalType::Type n) { return data[n]; }
    private:
        static std::map<NonTerminalType::Type, const std::vector<symbol_sequence>> data;
};