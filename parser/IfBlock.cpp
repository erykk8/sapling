#include "Parser.h"

using namespace TokenType;

std::unique_ptr<IfBlock> Parser::parseIfBlock() {
    auto ifBlock = std::make_unique<IfBlock>();
    switch(nextToken) {
        case IF:       
            ifBlock->ifClause = parseIfClause();
            while(nextToken == ELIF) ifBlock->elifClauses.push_back(std::move(parseElifClause()));
            ifBlock->elseClause = parseElseClause();
            break;
        default:
            throw std::runtime_error("Unexpected token");
    }
    return ifBlock;
}

std::unique_ptr<ConditionalClause> Parser::parseIfClause() {
    auto clause = std::make_unique<ConditionalClause>();
    switch(nextToken) {
        case IF:
            nextToken = scanner->getNextToken();
            if(nextToken != BRACE_OPEN) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            clause->condition = std::move(parseLogicalExpression());
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            clause->body = std::move(parseFunctionBodyBlock());
            return clause;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::unique_ptr<ConditionalClause> Parser::parseElifClause() {
    auto clause = std::make_unique<ConditionalClause>();
    switch(nextToken) {
        case ELIF:
            nextToken = scanner->getNextToken();
            if(nextToken != BRACE_OPEN) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            clause->condition = std::move(parseLogicalExpression());
            if(nextToken != BRACE_CLOSE) throw std::runtime_error("Unexpected token");
            nextToken = scanner->getNextToken();
            clause->body = std::move(parseFunctionBodyBlock());
            return clause;
        default:
            throw std::runtime_error("Unexpected token");
    }
}

std::unique_ptr<ConditionalClause> Parser::parseElseClause() {
    auto clause = std::make_unique<ConditionalClause>();
    switch(nextToken) {
        case ELSE:
            nextToken = scanner->getNextToken();
            clause->body = std::move(parseFunctionBodyBlock());
            return clause;
        default:
            throw std::runtime_error("Unexpected token");
    }
}