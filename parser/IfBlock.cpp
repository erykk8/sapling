#include "Parser.h"

using namespace TokenType;

void Parser::parseIfBlock() {
    switch(nextToken) {
        case IF:       
            parseIfClause();
            while(nextToken == ELIF) parseElifClauses();
            if(nextToken == ELSE) parseElseClause();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseIfClause() {
    switch(nextToken) {
        case IF:
            nextToken = scanner.getNextToken();
            if(nextToken != BRACE_OPEN) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
            parseLogicalExpression();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
            parseFunctionBodyBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseElifClauses() {
    switch(nextToken) {
        case ELIF:
            nextToken = scanner.getNextToken();
            if(nextToken != BRACE_OPEN) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
            parseLogicalExpression();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner.getNextToken();
            parseFunctionBodyBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

void Parser::parseElseClause() {
    switch(nextToken) {
        case ELSE:
            nextToken = scanner.getNextToken();
            parseFunctionBodyBlock();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
}