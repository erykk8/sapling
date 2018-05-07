#include "Parser.h"

using namespace TokenType;

void Parser::parseProgram() {
    std::shared_ptr<Function> function;
    nextToken = scanner->getNextToken();
    while(true) {
        currentScope = program;
        switch(nextToken) {
            case EOT:
                return;
            case INT_TYPE:
            case REAL_TYPE:
            case BOOL_TYPE:
            case STRING_TYPE:
                function = parseFunctionDeclaration();
                currentScope->functions.push_back(parseFunctionDeclaration());
                break;
            default:
                throw std::runtime_error("Unexpected token");
        }
    }
}