#include "Parser.h"

using namespace TokenType;

void Parser::parseProgram() {
    std::shared_ptr<Function> function;
    nextToken = scanner->getNextToken();
    while(true) {
        currentScope = program->scope;
        switch(nextToken) {
            case EOT:
                return;
            case INT_TYPE:
                parseFunctionDeclaration();
                break;
            default:
                throw std::runtime_error("Unexpected token");
        }
    }
}