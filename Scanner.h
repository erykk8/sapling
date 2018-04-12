#pragma once
#include <Token.h>
#include <IO.h>

class Scanner {
    public:
        Scanner(InputReader& reader);
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
};