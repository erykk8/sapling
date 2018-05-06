#include "Parser.h"

using namespace TokenType;

void Parser::parseProgram() {
    nextToken = scanner->getNextToken();
    while(true) {
        switch(nextToken) {
            case EOT:
                return;
            case INT_TYPE:
            case REAL_TYPE:
            case BOOL_TYPE:
            case STRING_TYPE:
                parseFunctionDeclaration();
                break;
            default:
                throw std::runtime_error("Unexpected token");
        }
    }
}