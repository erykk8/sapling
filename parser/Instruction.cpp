#include "Parser.h"

using namespace TokenType;

InstructionBlock Parser::parseInstructionBlock() {
    InstructionBlock instructions;
    switch(nextToken) {
        case IF:
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:        
            instructions.returnExpression = parseValueBlock();
            break;
        case INT_TYPE:
            while(nextToken != RETURN) {
                if(nextToken == INT_TYPE) {
                    auto function = parseFunctionDeclaration();
                    program->scope->functions[function->identifier] = function;
                }
            }
            if(nextToken != RETURN) throw std::runtime_error("Unexpected token");
        case RETURN:
            nextToken = scanner->getNextToken();
            instructions.returnExpression = parseValueBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return instructions;
}

std::shared_ptr<Expression> Parser::parseValueBlock() {
    std::shared_ptr<Expression> expression;
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