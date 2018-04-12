#pragma once
#include "Token.h"
#include "IO.h"
#include <memory>

class Scanner {
    public:
        Scanner(std::shared_ptr<InputReader> reader);
        Token getNextToken();
    private:
        bool tryKeyword();
        bool tryReturnArrow();
        bool tryBraces();
        bool tryConstant();
        bool trySeparator();
        bool tryOperator();
        bool tryIdentifier();

        void readNextToken();

        void throwUnknownToken();

        Token currentToken;
        std::shared_ptr<InputReader> reader;
};