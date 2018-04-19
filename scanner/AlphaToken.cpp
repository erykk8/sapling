#include "Scanner.h"
#include <sstream>

bool Scanner::alphaToken() {
    std::stringstream buf;

    while(alphanumericOrUnderscore(reader->peekChar())) {
        buf << reader->nextChar();
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
    else if(buf.str() == "and" || buf.str() == "or" || buf.str() == "not") {
        currentToken = Token::LOGICAL_OPERATOR;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "True") {
        currentToken.setBool(true);
    }
    else if(buf.str() == "False") {
        currentToken.setBool(false);
    }
    else if(buf.str() == "Int" || buf.str() == "String" || buf.str() == "Real" || buf.str() == "Bool"
            || buf.str() == "List" || buf.str() == "Set" || buf.str() == "Void") {
        currentToken = Token::TYPE_KEYWORD;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str().length() > 0) {
        currentToken = Token::IDENTIFIER;
    }
    else return false;

    return true;
}