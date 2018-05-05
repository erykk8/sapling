#include "Token.h"
using namespace TokenType;

bool Token::isTerminal() const {
    return type <= EOT;
}

Type Token::getType() const {
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
    type = INT_VALUE;
    integer = value;
}

void Token::setBool(bool value) {
    type = BOOL_VALUE;
    boolean = value;
}

void Token::setReal(double value) {
    type = REAL_VALUE;
    real = value;
}

void Token::setString(std::string value) {
    type = STRING_VALUE;
    string = value;
}

void Token::setOtherValue(std::string value) {
    string = value;
}

bool Token::operator==(const Type type) const {
    return this->type == type;
}

bool Token::operator!=(const Type type) const {
    return this->type != type;
}