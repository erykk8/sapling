#pragma once

#include "Token.h"

#include <map>
#include <memory>
#include <vector>

class Productions {
    public:
        typedef std::vector<Token> symbol_sequence;
        const std::vector<symbol_sequence> operator[] (TokenType::Type n) { return data[n]; }
    private:
        static std::map<TokenType::Type, const std::vector<symbol_sequence>> data;
};