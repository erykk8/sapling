#include "Parser.h"

using namespace TokenType;

std::shared_ptr<LogicalExpression> Parser::parseValueExpression() {
    auto expression = std::make_shared<LogicalExpression>();
    switch(nextToken) {
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            expression->a = *parseLogicalExpression();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return expression;
}

std::shared_ptr<Disjunction> Parser::parseLogicalExpression() {
    auto expression = std::make_shared<Disjunction>();
    switch(nextToken) {
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            expression->a = *parseConjunction();
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

std::shared_ptr<Conjunction> Parser::parseConjunction() {
    auto conjunction = std::make_shared<Conjunction>();
    switch(nextToken) {
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            conjunction->a = *parseNegation();
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

std::shared_ptr<Negation> Parser::parseNegation() {
    auto negation = std::make_shared<Negation>();
    switch(nextToken) {
        case NOT:
            negation->isActuallyNegation = true;
            nextToken = scanner->getNextToken();
            negation->a = *parseComparison();
            break;
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            negation->isActuallyNegation = false;
            negation->a = *parseComparison();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return negation;
}

std::shared_ptr<Comparison> Parser::parseComparison() {
    auto comparison = std::make_shared<Comparison>();
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
                    comparison->op = nextToken;
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

std::shared_ptr<Expression> Parser::parseLogicalOperand() {
    auto numericExpression = std::make_shared<NumericExpression>();
    auto value = std::make_shared<IntValue>();
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            numericExpression->a = *parseNumericExpression();
            return numericExpression;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::shared_ptr<Addition> Parser::parseNumericExpression() {
    auto expression = std::make_shared<Addition>();
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            expression->a = *parseMultiplication();
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

std::shared_ptr<Multiplication> Parser::parseMultiplication() {
    auto multiplication = std::make_shared<Multiplication>();
    switch(nextToken) {
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            multiplication->a = *parsePowerRaising();
            if(nextToken == MULTIPLY) {
                multiplication->isDivision = false;
                nextToken = scanner->getNextToken();
                multiplication->b = parseMultiplication();
            }
            else if(nextToken == DIVIDE) {
                multiplication->isDivision = true;
                nextToken = scanner->getNextToken();
                multiplication->b = parseMultiplication();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return multiplication;
}

std::shared_ptr<PowerRaising> Parser::parsePowerRaising() {
    auto power = std::make_shared<PowerRaising>();
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

std::shared_ptr<Expression> Parser::parseNumericOperand() {
    auto intValue = std::make_shared<IntValue>();
    auto funcCall = std::make_shared<FunctionCall>();
    auto expression = std::make_shared<LogicalExpression>();
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner->getNextToken();
            expression = parseValueExpression();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            return expression;
        case INT_VALUE:
            intValue->value = nextToken;
            nextToken = scanner->getNextToken();
            return intValue;
        case IDENTIFIER:
            funcCall = parseFunctionCall();
            return funcCall;
        default:
            throw std::runtime_error("Unexpected token");
    }
}