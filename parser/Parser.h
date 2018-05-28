#pragma once
#include "../token/Token.h"
#include "../scanner/Scanner.h"
#include "../ast/Program.h"
#include "../ast/Function.h"
#include "../ast/IfBlock.h"

#include <vector>
#include <memory>

class Parser {
    public:
        std::unique_ptr<Program> parse();
        Parser(std::unique_ptr<Scanner> s);
        ~Parser() = default;
    private:
        typedef std::pair<std::string, std::shared_ptr<Expression>> parameter;
        std::unique_ptr<Scanner> scanner;
        Token nextToken;
        std::unique_ptr<Program> program;

        // Program.cpp
        void parseProgram();

        // Function.cpp
        void parseFunctionDeclaration();
        std::unique_ptr<FunctionCall> parseFunctionCall();
        std::unique_ptr<InstructionBlock> parseFunctionBodyBlock();
        std::vector<std::string> parseParameterDeclaration();
        std::vector<std::unique_ptr<Expression>> parseParameterCall();
        std::vector<std::string> parseArgList();
        std::vector<std::unique_ptr<Expression>> parseValueList();

        // Instruction.cpp
        std::unique_ptr<InstructionBlock> parseInstructionBlock();
        std::unique_ptr<Expression> parseValueBlock();

        // ValueExpression.cpp
        std::unique_ptr<LogicalExpression> parseValueExpression();
        std::unique_ptr<Disjunction> parseLogicalExpression();
        std::unique_ptr<Conjunction> parseConjunction();
        std::unique_ptr<Negation> parseNegation();
        std::unique_ptr<Comparison> parseComparison();
        std::unique_ptr<Expression> parseLogicalOperand();
        std::unique_ptr<Addition> parseNumericExpression();
        std::unique_ptr<Multiplication> parseMultiplication();
        std::unique_ptr<PowerRaising> parsePowerRaising();
        std::unique_ptr<Expression> parseNumericOperand();
        
        // IfBlock.cpp
        std::unique_ptr<IfBlock> parseIfBlock();
        std::unique_ptr<ConditionalClause> parseIfClause();
        std::unique_ptr<ConditionalClause> parseElifClause();
        std::unique_ptr<ConditionalClause> parseElseClause();
};