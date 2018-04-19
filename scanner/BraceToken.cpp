#include "Scanner.h"

bool Scanner::braceToken() {
    switch(reader->peekChar()) {
        case '{':
            currentToken = Token::CURLY_BRACE_OPEN;
            break;
        case '}':
            currentToken = Token::CURLY_BRACE_CLOSE;
            break;
        case '(':
            currentToken = Token::BRACE_OPEN;
            break;
        case ')':
            currentToken = Token::BRACE_CLOSE;
            break;
        case '[':
            currentToken = Token::SQUARE_BRACE_OPEN;
            break;
        case ']':
            currentToken = Token::SQUARE_BRACE_CLOSE;
            break;
        default:
            return false;
    }
    reader->nextChar();
    return true;
}