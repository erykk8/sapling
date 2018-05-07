#include "Parser.h"

using namespace TokenType;

std::shared_ptr<IfBlock> Parser::parseIfBlock() {
    std::shared_ptr<IfBlock> ifBlock;
    switch(nextToken) {
        case IF:       
            ifBlock->ifClause = parseIfClause();
            while(nextToken == ELIF) ifBlock->elifClauses.push_back(parseElifClauses());
            ifBlock->elseClause = parseElseClause();
            return ifBlock;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

ConditionalClause Parser::parseIfClause() {
    ConditionalClause clause;
    switch(nextToken) {
        case IF:
            nextToken = scanner->getNextToken();
            if(nextToken != BRACE_OPEN) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            clause.condition.a = *parseLogicalExpression();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            clause.body = parseFunctionBodyBlock();
            return clause;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

ConditionalClause Parser::parseElifClauses() {
    ConditionalClause clause;
    switch(nextToken) {
        case ELIF:
            nextToken = scanner->getNextToken();
            if(nextToken != BRACE_OPEN) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            clause.condition.a = *parseLogicalExpression();
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            clause.body = parseFunctionBodyBlock();
            return clause;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

ConditionalClause Parser::parseElseClause() {
    ConditionalClause clause;
    switch(nextToken) {
        case ELSE:
            nextToken = scanner->getNextToken();
            clause.body = parseFunctionBodyBlock();
            return clause;
        default:
            throw std::runtime_error("Unexpected token");
    }
}