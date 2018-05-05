#include "Parser.h"

using namespace TokenType;

void Parser::parseProgram() {
    while(true) {
        nextToken = scanner.getNextToken();
        switch(nextToken) {
            case EOT:
                return;
            case INT_TYPE:
            case REAL_TYPE:
            case BOOL_TYPE:
            case STRING_TYPE:
                parseFunctionDeclaration();
            default:
                throw std::runtime_error("Unexpected token");
        }
    }
}