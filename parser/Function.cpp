#include "Parser.h"

using namespace TokenType;

std::unique_ptr<InstructionBlock> Parser::parseFunctionBodyBlock() {
    std::unique_ptr<InstructionBlock> instructions;
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
            instructions = std::make_unique<InstructionBlock>();
            instructions->returnExpression = parseValueBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return instructions;
}

void Parser::parseFunctionDeclaration() {
    auto function = std::make_unique<Function>();
    std::string identifier;
    std::vector<std::string> paramList;
    switch(nextToken) {
        case LET:
            nextToken = scanner->getNextToken();

            if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
            identifier = nextToken.getString();
            function->identifier = identifier;
            nextToken = scanner->getNextToken();

            if(nextToken == BRACE_OPEN) {
                paramList = parseParameterDeclaration();
            }
            function->parameters = paramList;

            program->scope->functions[identifier] = std::move(function); // move ownership to scope

            if(nextToken != ASSIGNMENT_OPERATOR) throw std::runtime_error("Unexpected token");
            
            nextToken = scanner->getNextToken();
            program->scope->functions[identifier]->body = std::move(parseFunctionBodyBlock());
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::vector<std::string> Parser::parseParameterDeclaration() {
    std::vector<std::string> paramList;
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner->getNextToken();
            paramList = parseArgList();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return paramList;
}

std::unique_ptr<FunctionCall> Parser::parseFunctionCall() {
    auto funcCall = std::make_unique<FunctionCall>();
    std::vector<std::unique_ptr<Expression>> parameterValues;
    const Function* function;
    auto it = program->scope->functions.end();
    switch(nextToken) {
        case IDENTIFIER:
            funcCall->functionName = nextToken.getString();

            nextToken = scanner->getNextToken();

            if(nextToken == BRACE_OPEN) {
                parameterValues = parseParameterCall();
            }

            if(parameterValues.size() > 0) {
                // its an actual function, find it and its parameters
                function = &(program->scope->getFunction(funcCall->functionName));

                if(function->parameters.size() != parameterValues.size()) {
                    throw std::runtime_error("Not enough arguments given to function");
                }

                for(int i = 0; i < parameterValues.size(); ++i) {
                    funcCall->parameters[function->parameters[i]] = std::move(parameterValues[i]);
                }
            }            
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return funcCall;
}

std::vector<std::unique_ptr<Expression>> Parser::parseParameterCall() {
    std::vector<std::unique_ptr<Expression>> values;
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

std::vector<std::unique_ptr<Expression>> Parser::parseValueList() {
    std::vector<std::unique_ptr<Expression>> values;
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
                values.push_back(std::move(parseValueExpression()));
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return values;
}

std::vector<std::string> Parser::parseArgList() {
    std::vector<std::string> parameters;
    std::string name;
    switch(nextToken) {
        case IDENTIFIER:
            name = nextToken.getString();
            nextToken = scanner->getNextToken();
            parameters.push_back(name);
            while(nextToken == COMMA) {
                nextToken = scanner->getNextToken();
                if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
                name = nextToken.getString();
                nextToken = scanner->getNextToken();
                parameters.push_back(name);
            }
            break;
        case BRACE_CLOSE:
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return parameters;
}