#pragma once
#include "../token/Token.h"
#include "../scanner/Scanner.h"

#include <stack>
#include <map>

class Parser {
    public:
        void parse();
        Parser(Scanner &s);
        ~Parser() = default;
    private:
        Scanner& scanner;
        Token nextToken;

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