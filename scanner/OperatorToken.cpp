#include "Scanner.h"
#include <sstream>

bool Scanner::operatorToken() {
    std::stringstream buf;
    switch(reader->peekChar()) {
        case '>':
            currentToken = Token::GREATER_THAN;
            buf << (char)reader->nextChar();
            if(reader->peekChar() == '=') {
                currentToken = Token::GREATER_EQUAL;
                buf << (char)reader->nextChar();
            }
            break;
        case '<':
            currentToken = Token::LESS_THAN;
            buf << (char)reader->nextChar();
            if(reader->peekChar() == '=') {
                currentToken = Token::LESS_EQUAL;
                buf << (char)reader->nextChar();
            }
            break;
        case '!':
            currentToken = Token::NOT_EQUAL;
            buf << (char)reader->nextChar();
            if(reader->peekChar() == '=') {
                buf << (char)reader->nextChar();
                break;
            }
            else return false;
        case '*':
            currentToken = Token::MULTIPLY;
            buf << (char)reader->nextChar();
            break;
        case '^':
            currentToken = Token::POWER;
            buf << (char)reader->nextChar();
            break;
        case '+':
            currentToken = Token::ADD;
            buf << (char)reader->nextChar();
            break;
        case '-':
            currentToken = Token::SUBTRACT;
            buf << (char)reader->nextChar();
            break;
        case '/':
            currentToken = Token::DIVIDE;
            buf << (char)reader->nextChar();
            if(reader->peekChar() == '/') {
                currentToken = Token::INT_DIVIDE;
                buf << (char)reader->nextChar();
            }
            break;
        default:
            return false;
    }
    currentToken.setOtherValue(buf.str());
    return true;
}