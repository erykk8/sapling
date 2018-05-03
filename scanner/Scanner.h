#pragma once
#include "../grammar/Token.h"
#include "IO.h"
#include <memory>
#include <functional>

class Scanner {
    public:
        Scanner(std::shared_ptr<InputReader> reader);
        Token getNextToken();
    private:
        static std::function<bool(char)> whiteSpace;
        static std::function<bool(char)> alphanumericOrUnderscore;
        static std::function<bool(char)> digit;
        static std::function<bool(char)> stringable;

        bool alphaToken();
        bool equalsCharacterToken();
        bool braceToken();
        bool valueToken();
        bool separatorToken();
        bool operatorToken();
        bool eotToken();

        void readNextToken();

        void throwUnknownToken();
        void throwInvalidString();

        Token currentToken;
        std::shared_ptr<InputReader> reader;
};