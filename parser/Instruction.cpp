#include "Parser.h"

using namespace TokenType;

InstructionBlock Parser::parseInstructionBlock() {
    InstructionBlock instructions;
    switch(nextToken) {
        case IF:
        case STRING_VALUE:
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:        
            instructions.returnExpression = parseValueBlock();
            return instructions;
        case INT_TYPE:
        case REAL_TYPE:
        case BOOL_TYPE:
        case STRING_TYPE:
            while(nextToken != RETURN) {
                switch(nextToken) {
                    case INT_TYPE:
                    case REAL_TYPE:
                    case BOOL_TYPE:
                    case STRING_TYPE:
                        auto function = parseFunctionDeclaration();
                        currentScope->functions[function->identifier] = function;
                }
            }
            if(nextToken != RETURN) throw std::runtime_error("Unexpected token");
        case RETURN:
            nextToken = scanner->getNextToken();
            instructions.returnExpression = parseValueBlock();
            return instructions;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::shared_ptr<Expression> Parser::parseValueBlock() {
    std::shared_ptr<Expression> expression;
    switch(nextToken) {
        case IF:
            expression = parseIfBlock();
            break;
        case STRING_VALUE:
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            expression = parseValueExpression();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return expression;
}