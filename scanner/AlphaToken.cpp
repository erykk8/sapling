#include "Scanner.h"
#include <sstream>

bool Scanner::alphaToken() {
    std::stringstream buf;

    while(alphanumericOrUnderscore(reader->peekChar())) {
        buf << (char)reader->nextChar();
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
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "or") {
        currentToken = TokenType::OR;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "not") {
        currentToken = TokenType::NOT;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "True") {
        currentToken.setBool(true);
    }
    else if(buf.str() == "False") {
        currentToken.setBool(false);
    }
    else if(buf.str() == "Int") {
        currentToken = TokenType::INT_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "Bool") {
        currentToken = TokenType::BOOL_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "String") {
        currentToken = TokenType::STRING_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "Real") {
        currentToken = TokenType::REAL_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "Void") {
        currentToken = TokenType::VOID_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str().length() > 0) {
        currentToken = TokenType::IDENTIFIER;
    }
    else return false;

    return true;
}