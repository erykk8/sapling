#pragma once
#include "../token/Token.h"
#include "../scanner/Scanner.h"
// #include "../ast/Program.h"

#include <stack>
#include <map>
#include <memory>

class Parser {
    public:
        void parse();
        Parser(std::shared_ptr<Scanner> s);
        ~Parser() = default;
    private:
        std::shared_ptr<Scanner> scanner;
        Token nextToken;
        // Program program;

        // Program.cpp
        void parseProgram();

        // Function.cpp
        void parseFunctionDeclaration();
        void parseFunctionCall();
        void parseFunctionBodyBlock();
        void parseParameterDeclaration();
        void parseParameterCall();
        void parseArgList();
        void parseValueList();

        // Instruction.cpp
        void parseInstructionBlock();
        void parseValueBlock();

        // ValueExpression.cpp
        void parseValueExpression();
        void parseLogicalExpression();
        void parseConjunction();
        void parseNegation();
        void parseComparison();
        void parseLogicalOperand();
        void parseNumericExpression();
        void parseMultiplication();
        void parsePowerRaising();
        void parseNumericOperand();
        
        // IfBlock.cpp
        void parseIfBlock();
        void parseIfClause();
        void parseElifClauses();
        void parseElseClause();
};