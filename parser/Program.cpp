#include "Parser.h"

using namespace TokenType;

void Parser::parseProgram() {
    std::shared_ptr<Function> function;
    nextToken = scanner->getNextToken();
    while(true) {
        switch(nextToken) {
            case EOT:
                return;
            case LET:
                parseFunctionDeclaration();
                break;
            default:
                throw std::runtime_error("Unexpected token");
        }
    }
}