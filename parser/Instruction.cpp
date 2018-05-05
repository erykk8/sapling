#include "Parser.h"

using namespace TokenType;

void Parser::parseInstructionBlock() {
    switch(nextToken) {
        case IF:
        case STRING_VALUE:
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:        
            parseValueBlock();
            parseInstructionBlock();
            break;
        case INT_TYPE:
        case REAL_TYPE:
        case BOOL_TYPE:
        case STRING_TYPE:
            parseFunctionDeclaration();
            parseInstructionBlock();
            break;
        case RETURN:
            nextToken = scanner.getNextToken();
            parseValueBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseValueBlock() {
    switch(nextToken) {
        case IF:
            parseIfBlock();
            break;
        case STRING_VALUE:
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseValueExpression();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}