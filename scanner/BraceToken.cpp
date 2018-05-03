#include "Scanner.h"

bool Scanner::braceToken() {
    switch(reader->peekChar()) {
        case '{':
            currentToken = TokenType::CURLY_BRACE_OPEN;
            break;
        case '}':
            currentToken = TokenType::CURLY_BRACE_CLOSE;
            break;
        case '(':
            currentToken = TokenType::BRACE_OPEN;
            break;
        case ')':
            currentToken = TokenType::BRACE_CLOSE;
            break;
        case '[':
            currentToken = TokenType::SQUARE_BRACE_OPEN;
            break;
        case ']':
            currentToken = TokenType::SQUARE_BRACE_CLOSE;
            break;
        default:
            return false;
    }
    reader->nextChar();
    return true;
}