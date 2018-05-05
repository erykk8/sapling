#include "Parser.h"

using namespace TokenType;

void Parser::parseFunctionBodyBlock() {
    switch(nextToken) {
        case CURLY_BRACE_OPEN:
            nextToken = scanner.getNextToken();
            parseInstructionBlock();
            if(nextToken != CURLY_BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
            break;
        case IF:
        case STRING_VALUE:
        case NOT:
        case BRACE_OPEN:
        case BOOL_VALUE:
        case INT_VALUE:
        case REAL_VALUE:
        case IDENTIFIER:
            parseValueBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseFunctionDeclaration() {
    switch(nextToken) {
        case INT_TYPE:
        case REAL_TYPE:
        case BOOL_TYPE:
        case STRING_TYPE:
            nextToken = scanner.getNextToken();
            if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
            
            nextToken = scanner.getNextToken();
            parseParameterDeclaration();

            if(nextToken != ASSIGNMENT_OPERATOR) throw std::runtime_error("Unexpected token");
            
            nextToken = scanner.getNextToken();
            parseFunctionBodyBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseParameterDeclaration() {
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner.getNextToken();
            parseArgList();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseFunctionCall() {
    switch(nextToken) {
        case IDENTIFIER:
            nextToken = scanner.getNextToken();
            if(nextToken == BRACE_OPEN) {
                nextToken = scanner.getNextToken();
                parseParameterCall();
            }
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseParameterCall() {
    switch(nextToken) {
        case BRACE_OPEN:
            nextToken = scanner.getNextToken();
            parseValueList();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseValueList() {
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
                nextToken = scanner.getNextToken();
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
            nextToken = scanner.getNextToken();
            if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
            while(nextToken == COMMA) {
                nextToken = scanner.getNextToken();
                switch(nextToken) {
                    case INT_TYPE:
                    case REAL_TYPE:
                    case BOOL_TYPE:
                    case STRING_TYPE:
                        break;
                    default:
                        throw std::runtime_error("Unexpected token");
                }
                nextToken = scanner.getNextToken();
                if(nextToken != IDENTIFIER) throw std::runtime_error("Unexpected token");
                nextToken = scanner.getNextToken();
            }
            break;
        case BRACE_CLOSE:
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}