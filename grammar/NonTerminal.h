#pragma once
#include "Symbol.h"

namespace NonTerminalType {
    enum Type { 
                    PROGRAM,
                    FUNCTION_DECLARATION, FUNCTION_CALL,
                    FUNCTION_BODY_BLOCK, VALUE_OR_INSTRUCTION_BLOCK,

                    PARAMETER_DECLARATION, PARAMETER_CALL,
                    ARG_LIST, ARG_LIST_P,
                    VALUE_LIST, VALUE_LIST_P,
                    TYPE, TYPE_LIST, TYPE_LIST_P,
                    LAMBDA_TYPE_LIST,
                    LAMBDA_TYPE, LAMBDA,

                    VALUE_BLOCK, VALUE_EXPRESSION,

                    LOGICAL_EXPRESSION,
                    DISJUNCTION_P,
                    CONJUNCTION, CONJUNCTION_P,
                    NEGATION,
                    COMPARISON, COMPARISON_P,
                    COMPARISON_OPERATOR,
                    LOGICAL_OPERAND,

                    NUMERIC_EXPRESSION,
                    ADDITION_P,
                    MULTIPLICATION, MULTIPLICATION_P,
                    POWER_RAISING, POWER_P,
                    NUMERIC_OPERAND,

                    INSTRUCTION_BLOCK, INSTRUCTION,
                    RETURN_INSTRUCTION,
                    IF_BLOCK, IF_CLAUSE,
                    ELIF_CLAUSES, ELIF_CLAUSE,
                    ELSE_CLAUSE
                };
}

class NonTerminal: public Symbol {
    public:
        bool isTerminal() { return false; }
        
        NonTerminal() = default;
        NonTerminal(const NonTerminalType::Type& type) : type(type) {};
        ~NonTerminal() = default;

        bool operator==(const NonTerminalType::Type type) const;
        bool operator!=(const NonTerminalType::Type type) const;
        operator NonTerminalType::Type() const { return type; }
    private:
        NonTerminalType::Type type;
};