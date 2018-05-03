#include "Scanner.h"
#include <sstream>

bool Scanner::equalsCharacterToken() {
    std::stringstream buf;

    if (reader->peekChar() == '=') {
        buf << (char)reader->nextChar();
        char c = reader->peekChar();
        switch(c) {
            case '>':
                reader->nextChar();
                currentToken = TokenType::RETURN_ARROW;
                buf << c;
                break;
            case '=':
                reader->nextChar();
                currentToken = TokenType::EQUAL;
                buf << c;
                break;
            default:
                currentToken = TokenType::ASSIGNMENT_OPERATOR;
                break;
        }
        currentToken.setOtherValue(buf.str());
        return true;
    }
    return false;
}