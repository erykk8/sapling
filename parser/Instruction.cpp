#include "Parser.h"

using namespace TokenType;

std::unique_ptr<InstructionBlock> Parser::parseInstructionBlock() {
    auto instructions = std::make_unique<InstructionBlock>();
    switch(nextToken) {
        case IF:
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:        
            instructions->returnExpression = parseValueBlock();
            break;
        case LET:
            while(nextToken == LET) {
                parseFunctionDeclaration(); // adds to global scope for now
            }
            if(nextToken != RETURN) instructions->returnExpression = parseValueBlock();
        case RETURN:
            nextToken = scanner->getNextToken();
            instructions->returnExpression = parseValueBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return instructions;
}

std::unique_ptr<Expression> Parser::parseValueBlock() {
    std::unique_ptr<Expression> expression;
    switch(nextToken) {
        case IF:
            expression = parseIfBlock();
            break;
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            expression = parseValueExpression();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return expression;
}