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
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            instructions.returnExpression = parseValueBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return instructions;
}

std::shared_ptr<Function> Parser::parseFunctionDeclaration() {
    auto function = std::make_shared<Function>();
    std::vector<Parameter> paramList;
    switch(nextToken) {
        case INT_TYPE:
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
            funcCall->functionName = nextToken.getString();
            function = currentScope->functions[funcCall->functionName];
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
    return funcCall;
}

std::vector<std::shared_ptr<Expression>> Parser::parseParameterCall() {
    std::vector<std::shared_ptr<Expression>> values;
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner->getNextToken();
            values = parseValueList();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return values;
}

std::vector<std::shared_ptr<Expression>> Parser::parseValueList() {
    std::vector<std::shared_ptr<Expression>> values;
    switch(nextToken) {
        case BRACE_CLOSE:
            break;    
        case NOT:
        case BRACE_OPEN:
        case INT_VALUE:
        case IDENTIFIER:
            values.push_back(parseValueExpression());
            while(nextToken == COMMA) {
                nextToken = scanner->getNextToken();
                values.push_back(parseValueExpression());
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return values;
}

std::vector<Parameter> Parser::parseArgList() {
    std::vector<Parameter> parameters;
    Parameter parameter;
    switch(nextToken) {
        case INT_TYPE:
            do {
                parameter.type = nextToken;
                nextToken = scanner->getNextToken();
                if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
                parameter.name = nextToken.getString();
                nextToken = scanner->getNextToken();
                parameters.push_back(parameter);
            } while(nextToken == COMMA);
            break;
        case BRACE_CLOSE:
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return parameters;
}