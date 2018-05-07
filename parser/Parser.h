#pragma once
#include "../token/Token.h"
#include "../scanner/Scanner.h"
#include "../ast/Program.h"
#include "../ast/Function.h"
#include "../ast/IfBlock.h"
#include "../ast/Parameter.h"

#include <vector>
#include <memory>

class Parser {
    public:
        void parse();
        int evaluate();
        Parser(std::shared_ptr<Scanner> s);
        ~Parser() = default;
    private:
        std::shared_ptr<Scanner> scanner;
        Token nextToken;
        std::shared_ptr<Program> program;
        std::shared_ptr<Scope> currentScope;

        // Program.cpp
        void parseProgram();

        // Function.cpp
        std::shared_ptr<Function> parseFunctionDeclaration();
        std::shared_ptr<FunctionCall> parseFunctionCall();
        InstructionBlock parseFunctionBodyBlock();
        std::vector<Parameter> parseParameterDeclaration();
        std::vector<std::shared_ptr<Expression>> parseParameterCall();
        std::vector<Parameter> parseArgList();
        std::vector<std::shared_ptr<Expression>> parseValueList();

        // Instruction.cpp
        InstructionBlock parseInstructionBlock();
        std::shared_ptr<Expression> parseValueBlock();

        // ValueExpression.cpp
        std::shared_ptr<LogicalExpression> parseValueExpression();
        std::shared_ptr<Disjunction> parseLogicalExpression();
        std::shared_ptr<Conjunction> parseConjunction();
        std::shared_ptr<Negation> parseNegation();
        std::shared_ptr<Comparison> parseComparison();
        std::shared_ptr<Expression> parseLogicalOperand();
        std::shared_ptr<Addition> parseNumericExpression();
        std::shared_ptr<Multiplication> parseMultiplication();
        std::shared_ptr<PowerRaising> parsePowerRaising();
        std::shared_ptr<Expression> parseNumericOperand();
        
        // IfBlock.cpp
        std::shared_ptr<IfBlock> parseIfBlock();
        ConditionalClause parseIfClause();
        ConditionalClause parseElifClauses();
        ConditionalClause parseElseClause();
};