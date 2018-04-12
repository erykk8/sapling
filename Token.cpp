#include "Token.h"

Token::Token() : type(Token::EOT) {}
Token::Token(Type type) : type(type) {}
Token::~Token() {}

Token::Type Token::getType() const {
    return type;
}

int Token::getInt() const {
    return integer;
}

bool Token::getBool() const {
    return boolean;
}
double Token::getReal() const {
    return real;
}

std::string Token::getString() const {
    return string;
}

void Token::setInt(int value) {
    type = Token::INT_VALUE;
    integer = value;
}

void Token::setBool(bool value) {
    type = Token::BOOL_VALUE;
    boolean = value;
}

void Token::setReal(double value) {
    type = Token::REAL_VALUE;
    real = value;
}

void Token::setString(std::string value) {
    type = Token::STRING_VALUE;
    string = value;
}