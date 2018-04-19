#include "Scanner.h"
#include <sstream>

bool Scanner::operatorToken() {
    std::stringstream buf;
    switch(reader->peekChar()) {
        case '>':
        case '<':
        case '!':
            currentToken = Token::COMPARISON_OPERATOR;
            buf << reader->nextChar();
            if(reader->peekChar() == '=') {
                buf << reader->nextChar();
            }
            break;
        case '*':
        case '^':
        case '+':
        case '-':
            currentToken = Token::ARITHMETIC_OPERATOR;
            buf << reader->nextChar();
            break;
        case '/':
            currentToken = Token::ARITHMETIC_OPERATOR;
            buf << reader->nextChar();
            if(reader->peekChar() == '/') {
                buf << reader->nextChar();
            }
            break;
        default:
            return false;
    }
    currentToken.setOtherValue(buf.str());
    return true;
}