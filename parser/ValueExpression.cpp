#include "Parser.h"

using namespace TokenType;

std::unique_ptr<LogicalExpression> Parser::parseValueExpression() {
    auto expression = std::make_unique<LogicalExpression>();
    switch(nextToken) {
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            expression->a = parseLogicalExpression();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return expression;
}

std::unique_ptr<Disjunction> Parser::parseLogicalExpression() {
    auto expression = std::make_unique<Disjunction>();
    switch(nextToken) {
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            expression->a = parseConjunction();
            if(nextToken == OR) {
                nextToken = scanner->getNextToken();
                expression->b = parseLogicalExpression();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return expression;
}

std::unique_ptr<Conjunction> Parser::parseConjunction() {
    auto conjunction = std::make_unique<Conjunction>();
    switch(nextToken) {
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            conjunction->a = parseNegation();
            if(nextToken == AND) {
                nextToken = scanner->getNextToken();
                conjunction->b = parseConjunction();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return conjunction;
}

std::unique_ptr<Negation> Parser::parseNegation() {
    auto negation = std::make_unique<Negation>();
    switch(nextToken) {
        case NOT:
            negation->isActuallyNegation = true;
            nextToken = scanner->getNextToken();
            negation->a = parseComparison();
            break;
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            negation->isActuallyNegation = false;
            negation->a = parseComparison();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return negation;
}

std::unique_ptr<Comparison> Parser::parseComparison() {
    auto comparison = std::make_unique<Comparison>();
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            comparison->a = parseLogicalOperand();
            switch(nextToken) {
                case LESS_EQUAL:
                case LESS_THAN:
                case GREATER_EQUAL:
                case GREATER_THAN:
                case EQUAL:
                case NOT_EQUAL:
                    switch(nextToken) {
                        case LESS_EQUAL:
                            comparison->op = Comparison::LESS_EQUAL;
                            break;
                        case LESS_THAN:
                            comparison->op = Comparison::LESS_THAN;
                            break;
                        case GREATER_EQUAL:
                            comparison->op = Comparison::GREATER_EQUAL;
                            break;
                        case GREATER_THAN:
                            comparison->op = Comparison::GREATER_THAN;
                            break;
                        case EQUAL:
                            comparison->op = Comparison::EQUAL;
                            break;
                        case NOT_EQUAL:
                            comparison->op = Comparison::NOT_EQUAL;
                            break;
                        default:
                            break;
                    }
                    nextToken = scanner->getNextToken();
                    comparison->b = parseLogicalOperand();
                    break;
                default:
                    break;
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return comparison;
}

std::unique_ptr<Expression> Parser::parseLogicalOperand() {
    auto numericExpression = std::make_unique<NumericExpression>();
    auto value = std::make_unique<IntValue>();
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            numericExpression->a = parseNumericExpression();
            return numericExpression;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::unique_ptr<Addition> Parser::parseNumericExpression() {
    auto expression = std::make_unique<Addition>();
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            expression->a = parseMultiplication();
            if(nextToken == ADD) {
                nextToken = scanner->getNextToken();
                expression->isSubtraction = false;
                expression->b = parseNumericExpression();
            }
            else if(nextToken == SUBTRACT) {
                nextToken = scanner->getNextToken();
                expression->isSubtraction = true;
                expression->b = parseNumericExpression();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return expression;
}

std::unique_ptr<Multiplication> Parser::parseMultiplication() {
    auto multiplication = std::make_unique<Multiplication>();
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            multiplication->a = parsePowerRaising();
            switch(nextToken) {
                case MULTIPLY:
                case DIVIDE:
                case MODULO:
                    switch(nextToken) {
                        case MULTIPLY:
                            multiplication->type = Multiplication::MULTIPLY;
                            break;
                        case DIVIDE:
                            multiplication->type = Multiplication::DIVIDE;
                            break;
                        case MODULO:
                            multiplication->type = Multiplication::MODULO;
                            break;
                        default:
                            break;
                    }
                    nextToken = scanner->getNextToken();
                    multiplication->b = parseMultiplication();
                    break;
                default:
                    break;
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return multiplication;
}

std::unique_ptr<PowerRaising> Parser::parsePowerRaising() {
    auto power = std::make_unique<PowerRaising>();
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            power->base = parseNumericOperand();
            if(nextToken == POWER) {
                nextToken = scanner->getNextToken();
                power->power = parsePowerRaising();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return power;
}

std::unique_ptr<Expression> Parser::parseNumericOperand() {
    auto intValue = std::make_unique<IntValue>();
    auto funcCall = std::make_unique<FunctionCall>();
    auto expression = std::make_unique<LogicalExpression>();
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner->getNextToken();
            expression = parseValueExpression();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            return expression;
        case INT_VALUE:
            intValue->value = nextToken.getInt();
            nextToken = scanner->getNextToken();
            return intValue;
        case IDENTIFIER:
            funcCall = parseFunctionCall();
            return funcCall;
        default:
            throw std::runtime_error("Unexpected token");
    }
}