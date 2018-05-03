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
                currentToken = Token::RETURN_ARROW;
                buf << c;
                break;
            case '=':
                reader->nextChar();
                currentToken = Token::EQUAL;
                buf << c;
                break;
            default:
                currentToken = Token::ASSIGNMENT_OPERATOR;
                break;
        }
        currentToken.setOtherValue(buf.str());
        return true;
    }
    return false;
}