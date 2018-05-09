#include "Scanner.h"
#include <sstream>

bool Scanner::operatorToken() {
    std::stringstream buf;
    switch(reader->peekChar()) {
        case '>':
            currentToken = TokenType::GREATER_THAN;
            buf << (char)reader->nextChar();
            if(reader->peekChar() == '=') {
                currentToken = TokenType::GREATER_EQUAL;
                buf << (char)reader->nextChar();
            }
            break;
        case '<':
            currentToken = TokenType::LESS_THAN;
            buf << (char)reader->nextChar();
            if(reader->peekChar() == '=') {
                currentToken = TokenType::LESS_EQUAL;
                buf << (char)reader->nextChar();
            }
            break;
        case '!':
            currentToken = TokenType::NOT_EQUAL;
            buf << (char)reader->nextChar();
            if(reader->peekChar() == '=') {
                buf << (char)reader->nextChar();
                break;
            }
            else return false;
        case '*':
            currentToken = TokenType::MULTIPLY;
            buf << (char)reader->nextChar();
            break;
        case '^':
            currentToken = TokenType::POWER;
            buf << (char)reader->nextChar();
            break;
        case '+':
            currentToken = TokenType::ADD;
            buf << (char)reader->nextChar();
            break;
        case '-':
            currentToken = TokenType::SUBTRACT;
            buf << (char)reader->nextChar();
            break;
        case '/':
            currentToken = TokenType::DIVIDE;
            buf << (char)reader->nextChar();
            break;
        case '%':
            currentToken = TokenType::MODULO;
            buf << (char)reader->nextChar();
            break;
        default:
            return false;
    }
    currentToken.setString(buf.str());
    return true;
}