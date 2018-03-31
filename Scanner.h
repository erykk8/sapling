#pragma once
#include <Token.h>

class Scanner {
    public:
        Scanner(InputReader& reader);
        Token getNextToken();
    private:
        bool tryKeyword();
        bool trySpecialCharacter();
        bool tryOperator();
        bool tryIdentifier();

        void readNextToken();

        void throwUnknownToken();

        Token currentToken;
};