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

std::string Token::getString() const {
    return string;
}

std::string Token::getName() const {
    return names[type];
}

void Token::setInt(int value) {
    type = INT_VALUE;
    integer = value;
}

void Token::setString(std::string value) {
    string = value;
}

bool Token::operator==(const Type type) const {
    return this->type == type;
}

bool Token::operator!=(const Type type) const {
    return this->type != type;
}

int Token::getLine() const {
    return line;
}

int Token::getPosition() const {
    return position;
}

void Token::setLine(int line) {
    this->line = line;
}

void Token::setPosition(int position) {
    this->position = position;
}

std::vector<std::string> Token::names = {
    "IF", "ELIF", "ELSE", "RETURN", "RETURN_ARROW",
    "COMMA", "INT_TYPE",
    "NOT", "AND", "OR", "INT_VALUE",
    "IDENTIFIER", "ASSIGNMENT_OPERATOR", "LESS_THAN", "GREATER_THAN",
    "LESS_EQUAL", "GREATER_EQUAL", "EQUAL", "NOT_EQUAL", "POWER", "MULTIPLY",
    "DIVIDE", "ADD", "SUBTRACT", "CURLY_BRACE_OPEN", "CURLY_BRACE_CLOSE",
    "BRACE_OPEN", "BRACE_CLOSE", "EOT"
};