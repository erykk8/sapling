#pragma once
#include "Symbol.h"

class NonTerminal: public Symbol {
    public:
        bool isTerminal() { return false; }

        enum Type { 
                    PROGRAM,
                    FUNCTION_DECLARATION, FUNCTION_CALL,
                    FUNCTION_BODY_BLOCK,

                    PARAMETER_DECLARATION, PARAMETER_CALL,
                    ARG_LIST, ARG_LIST_P,
                    VALUE_LIST, VALUE_LIST_P,
                    TYPE, TYPE_LIST, TYPE_LIST_P,
                    LAMBDA_TYPE,

                    VALUE_BLOCK, VALUE_EXPRESSION,

                    LOGICAL_EXPRESSION,
                    DISJUNCTION, DISJUNCTION_P,
                    CONJUNCTION, CONJUNCTION_P,
                    NEGATION,
                    COMPARISON, COMPARISON_P,
                    LOGICAL_OPERAND,

                    NUMERIC_EXPRESSION,
                    ADDITION, ADDITION_P,
                    MULTIPLICATION, MULTIPLICATION_P,
                    POWER, POWER_P,
                    NUMERIC_OPERAND,

                    INSTRUCTION_BLOCK, INSTRUCTION,
                    RETURN_INSTRUCTION,
                    IF_BLOCK, IF_CLAUSE,
                    ELIF_CLAUSES, ELIF_CLAUSES_P,
                    ELIF_CLAUSE,
                    ELSE_CLAUSE, ELSE_CLAUSE_P
                };
};