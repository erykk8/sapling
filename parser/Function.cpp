#include "Parser.h"

using namespace TokenType;

InstructionBlock Parser::parseFunctionBodyBlock() {
    InstructionBlock instructions;
    switch(nextToken) {
        case CURLY_BRACE_OPEN:
            nextToken = scanner->getNextToken();
            instructions = parseInstructionBlock();
            if(nextToken != CURLY_BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            break;
        case IF:
        case STRING_VALUE:
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            instructions.returnExpression = parseValueBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return instructions;
}

std::shared_ptr<Function> Parser::parseFunctionDeclaration() {
    std::shared_ptr<Function> function = std::make_shared<Function>();
    std::vector<Parameter> paramList;
    switch(nextToken) {
        case INT_TYPE:
        case REAL_TYPE:
        case BOOL_TYPE:
        case STRING_TYPE:
            function->returnType = nextToken;
            nextToken = scanner->getNextToken();

            if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
            function->identifier = nextToken.getString();
            nextToken = scanner->getNextToken();

            if(nextToken == BRACE_OPEN) {
                paramList = parseParameterDeclaration();
            }

            if(nextToken != ASSIGNMENT_OPERATOR) throw std::runtime_error("Unexpected token");
            
            nextToken = scanner->getNextToken();
            function->body = parseFunctionBodyBlock();
            function->parameters = paramList;
            return function;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::vector<Parameter> Parser::parseParameterDeclaration() {
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner->getNextToken();
            parseArgList();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::shared_ptr<FunctionCall> Parser::parseFunctionCall() {
    auto funcCall = std::make_shared<FunctionCall>();
    std::vector<std::shared_ptr<Expression>> parameterValues;
    Function function;
    switch(nextToken) {
        case IDENTIFIER:
            function = currentScope->functions[nextToken.getString()];
            nextToken = scanner->getNextToken();
            
            if(nextToken == BRACE_OPEN) {
                parameterValues = parseParameterCall();
            }
            if(function.parameters.size() != parameterValues.size()) {
                throw std::runtime_error("Not enough arguments given to function");
            }

            for(int i = 0; i < parameterValues.size(); ++i) {
                funcCall->parameterScope->identifiers[function.parameters[i].name] = parameterValues[i];
            }
            
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::vector<std::shared_ptr<Expression>> Parser::parseParameterCall() {
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner->getNextToken();
            parseValueList();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::vector<std::shared_ptr<Expression>> Parser::parseValueList() {
    switch(nextToken) {
        case BRACE_CLOSE:
            break;
        case STRING_VALUE:       
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseValueExpression();
            while(nextToken == COMMA) {
                nextToken = scanner->getNextToken();
                parseValueExpression();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseArgList() {
    switch(nextToken) {
        case INT_TYPE:
        case REAL_TYPE:
        case BOOL_TYPE:
        case STRING_TYPE:
            nextToken = scanner->getNextToken();
            if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            while(nextToken == COMMA) {
                nextToken = scanner->getNextToken();
                switch(nextToken) {
                    case INT_TYPE:
                    case REAL_TYPE:
                    case BOOL_TYPE:
                    case STRING_TYPE:
                        break;
                    default:
                        throw std::runtime_error("Unexpected token");
                }
                nextToken = scanner->getNextToken();
                if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
                nextToken = scanner->getNextToken();
            }
            break;
        case BRACE_CLOSE:
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}