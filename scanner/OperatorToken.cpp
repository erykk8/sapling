#include "Scanner.h"
#include <sstream>

bool Scanner::operatorToken() {
    std::stringstream buf;
    switch(reader->peekChar()) {
        case '>':
            currentToken = Token::GREATER_THAN;
            buf << reader->nextChar();
            if(reader->peekChar() == '=') {
                currentToken = Token::GREATER_EQUAL;
                buf << reader->nextChar();
            }
            break;
        case '<':
            currentToken = Token::LESS_THAN;
            buf << reader->nextChar();
            if(reader->peekChar() == '=') {
                currentToken = Token::LESS_EQUAL;
                buf << reader->nextChar();
            }
            break;
        case '!':
            currentToken = Token::NOT_EQUAL;
            buf << reader->nextChar();
            if(reader->peekChar() == '=') {
                buf << reader->nextChar();
                break;
            }
            else return false;
        case '*':
            currentToken = Token::MULTIPLY;
            buf << reader->nextChar();
            break;
        case '^':
            currentToken = Token::POWER;
            buf << reader->nextChar();
            break;
        case '+':
            currentToken = Token::ADD;
            buf << reader->nextChar();
            break;
        case '-':
            currentToken = Token::SUBTRACT;
            buf << reader->nextChar();
            break;
        case '/':
            currentToken = Token::DIVIDE;
            buf << reader->nextChar();
            if(reader->peekChar() == '/') {
                currentToken = Token::INT_DIVIDE;
                buf << reader->nextChar();
            }
            break;
        default:
            return false;
    }
    currentToken.setOtherValue(buf.str());
    return true;
}