#include "Parser.h"

using namespace TokenType;

void Parser::parseValueExpression() {
    switch(nextToken) {
        case STRING_VALUE:       
            nextToken = scanner.getNextToken();
            break;
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseLogicalExpression();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseLogicalExpression() {
    switch(nextToken) {
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseConjunction();
            if(nextToken == OR) {
                nextToken = scanner.getNextToken();
                parseLogicalExpression();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseConjunction() {
    switch(nextToken) {
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseNegation();
            if(nextToken == AND) {
                nextToken = scanner.getNextToken();
                parseConjunction();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseNegation() {
    switch(nextToken) {
        case NOT:
            nextToken = scanner.getNextToken();
            parseComparison();
            break;
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseComparison();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseComparison() {
    switch(nextToken) {
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseLogicalOperand();
            switch(nextToken) {
                case LESS_EQUAL:
                case LESS_THAN:
                case GREATER_EQUAL:
                case GREATER_THAN:
                case EQUAL:
                case NOT_EQUAL:
                    nextToken = scanner.getNextToken();
                    parseLogicalOperand();
                    break;
                default:
                    break;
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseLogicalOperand() {
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner.getNextToken();
            parseLogicalExpression();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
        case BOOL_VALUE:
            nextToken = scanner.getNextToken();
            break;
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseNumericExpression();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseNumericExpression() {
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseMultiplication();
            if(nextToken == ADD) {
                nextToken = scanner.getNextToken();
                parseNumericExpression();
            }
            else if(nextToken == SUBTRACT) {
                nextToken = scanner.getNextToken();
                parseNumericExpression();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseMultiplication() {
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parsePowerRaising();
            if(nextToken == MULTIPLY) {
                nextToken = scanner.getNextToken();
                parseMultiplication();
            }
            else if(nextToken == DIVIDE) {
                nextToken = scanner.getNextToken();
                parseMultiplication();
            }
            else if(nextToken == INT_DIVIDE) {
                nextToken = scanner.getNextToken();
                parseMultiplication();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parsePowerRaising() {
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseNumericOperand();
            if(nextToken == POWER) {
                nextToken = scanner.getNextToken();
                parsePowerRaising();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseNumericOperand() {
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner.getNextToken();
            parseNumericExpression();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
        case INT_VALUE:
        case REAL_VALUE:
            nextToken = scanner.getNextToken();
            break;
        case IDENTIFIER:
            parseFunctionCall();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}