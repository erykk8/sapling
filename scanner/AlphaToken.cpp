#include "Scanner.h"
#include <sstream>

bool Scanner::alphaToken() {
    std::stringstream buf;

    if(alphaOrUnderscore(reader->peekChar())) {
        while(alphaOrUnderscore(reader->peekChar()) || isdigit(reader->peekChar())) {
            buf << (char)reader->nextChar();
        }
    }

    // lazy
    if(buf.str() == "return") {
        currentToken = TokenType::RETURN;
    }
    else if(buf.str() == "if") {
        currentToken = TokenType::IF;
    }
    else if(buf.str() == "elif") {
        currentToken = TokenType::ELIF;
    }
    else if(buf.str() == "else") {
        currentToken = TokenType::ELSE;
    }
    else if(buf.str() == "and") {
        currentToken = TokenType::AND;
        currentToken.setString(buf.str());
    }
    else if(buf.str() == "or") {
        currentToken = TokenType::OR;
        currentToken.setString(buf.str());
    }
    else if(buf.str() == "not") {
        currentToken = TokenType::NOT;
        currentToken.setString(buf.str());
    }
    else if(buf.str() == "True") {
        currentToken.setInt(1);
    }
    else if(buf.str() == "False") {
        currentToken.setInt(0);
    }
    else if(buf.str() == "Int") {
        currentToken = TokenType::INT_TYPE;
        currentToken.setString(buf.str());
    }
    else if(buf.str().length() > 0) {
        currentToken = TokenType::IDENTIFIER;
        currentToken.setString(buf.str());
    }
    else return false;

    return true;
}