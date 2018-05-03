#include "Scanner.h"
#include <sstream>

bool Scanner::alphaToken() {
    std::stringstream buf;

    while(alphanumericOrUnderscore(reader->peekChar())) {
        buf << (char)reader->nextChar();
    }

    // lazy
    if(buf.str() == "return") {
        currentToken = Token::RETURN;
    }
    else if(buf.str() == "if") {
        currentToken = Token::IF;
    }
    else if(buf.str() == "elif") {
        currentToken = Token::ELIF;
    }
    else if(buf.str() == "else") {
        currentToken = Token::ELSE;
    }
    else if(buf.str() == "and") {
        currentToken = Token::AND;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "or") {
        currentToken = Token::OR;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "not") {
        currentToken = Token::NOT;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "True") {
        currentToken.setBool(true);
    }
    else if(buf.str() == "False") {
        currentToken.setBool(false);
    }
    else if(buf.str() == "Int") {
        currentToken = Token::INT_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "Bool") {
        currentToken = Token::BOOL_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "String") {
        currentToken = Token::STRING_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "Real") {
        currentToken = Token::REAL_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "Void") {
        currentToken = Token::VOID_TYPE;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str().length() > 0) {
        currentToken = Token::IDENTIFIER;
    }
    else return false;

    return true;
}