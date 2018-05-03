#include "Productions.h"
#include "Token.h"

using namespace TokenType;


std::map<TokenType::Type, const std::vector<Productions::symbol_sequence>> Productions::data =
{
    { PROGRAM, 
        {
            {EOT},
            {FUNCTION_DECLARATION, 
            PROGRAM}
        }
    },

    { FUNCTION_DECLARATION,
        {
            {TYPE,
            IDENTIFIER,
            PARAMETER_DECLARATION,
            ASSIGNMENT_OPERATOR,
            FUNCTION_BODY_BLOCK}
        }
    },
    
    { FUNCTION_CALL,
        {
            {IDENTIFIER,
            PARAMETER_CALL}
        }
    },

    { PARAMETER_DECLARATION,
        {
            {BRACE_OPEN,
            ARG_LIST,
            BRACE_CLOSE}
        }
    },

    { PARAMETER_CALL,
        {
            {BRACE_OPEN,
            VALUE_LIST,
            BRACE_CLOSE}
        }
    },
    
    { ARG_LIST,
        {
            {},
            {TYPE,
            IDENTIFIER,
            ARG_LIST_P}
        }
    },

    { ARG_LIST_P,
        {
            {},
            {COMMA,
            TYPE,
            IDENTIFIER,
            ARG_LIST_P}
        }
    },

    { VALUE_LIST,
        {
            {},
            {VALUE_EXPRESSION,
            VALUE_LIST_P}
        }
    },

    { VALUE_LIST_P,
        {
            {},
            {COMMA,
            VALUE_EXPRESSION,
            VALUE_LIST_P}
        }
    },

    { TYPE,
        {
            {INT_TYPE},
            {REAL_TYPE},
            {BOOL_TYPE},
            {STRING_TYPE},
            {LAMBDA_TYPE}
        }
    },

    { LAMBDA_TYPE_LIST,
        {   
            {},
            {VOID_TYPE},
            {TYPE,
            TYPE_LIST_P}
        }
    },

    { TYPE_LIST,
        {
            {TYPE,
            TYPE_LIST_P}
        }
    },

    { VALUE_LIST_P,
        {
            {},
            {COMMA,
            TYPE,
            TYPE_LIST_P}
        }
    },

    { LAMBDA_TYPE,
        {
            {BRACE_OPEN,
            LAMBDA_TYPE_LIST,
            BRACE_CLOSE,
            RETURN_ARROW,
            BRACE_OPEN,
            TYPE_LIST,
            BRACE_CLOSE}
        }
    },

    { LAMBDA,
        {
            {BRACE_OPEN,
            ARG_LIST,
            BRACE_CLOSE,
            RETURN_ARROW,
            FUNCTION_BODY_BLOCK}
        }
    },

    { VALUE_OR_INSTRUCTION_BLOCK,
        {
            {VALUE_BLOCK},
            {INSTRUCTION_BLOCK}
        }
    },

    { FUNCTION_BODY_BLOCK,
        {
            {VALUE_BLOCK},
            {CURLY_BRACE_OPEN,
            VALUE_OR_INSTRUCTION_BLOCK,
            CURLY_BRACE_CLOSE}
        }
    },

    { VALUE_BLOCK,
        {
            {IF_BLOCK},
            {VALUE_EXPRESSION}
        }
    },

    { VALUE_EXPRESSION,
        {
            {LOGICAL_EXPRESSION,
            STRING_VALUE,
            LAMBDA}
        }
    },

    { NUMERIC_EXPRESSION,
        {
            {MULTIPLICATION,
            ADDITION_P}
        }
    },

    { ADDITION_P,
        {
            {},
            {ADD,
            NUMERIC_EXPRESSION},
            {SUBTRACT,
            NUMERIC_EXPRESSION}
        }
    },

    { MULTIPLICATION,
        {
            {POWER_RAISING,
            MULTIPLICATION_P}
        }
    },

    { MULTIPLICATION_P,
        {
            {},
            {MULTIPLY,
            MULTIPLICATION},
            {DIVIDE,
            MULTIPLICATION},
            {INT_DIVIDE,
            MULTIPLICATION}
        }
    },

    { POWER_RAISING,
        {
            {NUMERIC_OPERAND,
            POWER_P}
        }
    },

    { POWER_P,
        {
            {},
            {POWER,
            POWER_RAISING},
        }
    },

    { NUMERIC_OPERAND,
        {
            {INT_VALUE},
            {REAL_VALUE},
            {IDENTIFIER},
            {FUNCTION_CALL},
            {BRACE_OPEN,
            NUMERIC_EXPRESSION,
            BRACE_CLOSE}
        }
    },

    { LOGICAL_EXPRESSION,
        {
            {CONJUNCTION,
            DISJUNCTION_P}
        }
    },

    { DISJUNCTION_P,
        {
            {},
            {OR,
            LOGICAL_EXPRESSION}
        }
    },

    { CONJUNCTION,
        {
            {NEGATION,
            CONJUNCTION_P}
        }
    },

    { CONJUNCTION_P,
        {
            {},
            {AND,
            CONJUNCTION}
        }
    },

    { NEGATION,
        {
            {COMPARISON},
            {NOT,
            COMPARISON}
        }
    },

    { COMPARISON,
        {
            {LOGICAL_OPERAND,
            COMPARISON_P}
        }
    },

    { COMPARISON_OPERATOR,
        {
            {LESS_THAN},
            {LESS_EQUAL},
            {GREATER_THAN},
            {GREATER_EQUAL},
            {EQUAL},
            {NOT_EQUAL}
        }
    },

    { COMPARISON_P,
        {
            {},
            {COMPARISON_OPERATOR,
            LOGICAL_OPERAND}
        }
    },

    { LOGICAL_OPERAND,
        {
            {BOOL_VALUE},
            { NUMERIC_EXPRESSION},
            {BRACE_OPEN,
            LOGICAL_EXPRESSION,
            BRACE_CLOSE}
        }
    },

    { INSTRUCTION_BLOCK,
        {
            {RETURN_INSTRUCTION},
            {INSTRUCTION,
            INSTRUCTION_BLOCK},
        }
    },

    { INSTRUCTION,
        {
            {FUNCTION_DECLARATION},
            {VALUE_BLOCK},
        }
    },

    { RETURN_INSTRUCTION,
        {
            {RETURN,
            VALUE_BLOCK},
        }
    },

    { IF_BLOCK,
        {
            {IF_CLAUSE,
            ELIF_CLAUSES,
            ELSE_CLAUSE}
        }
    },

    { IF_CLAUSE,
        {
            {IF,
            BRACE_OPEN,
            LOGICAL_EXPRESSION,
            BRACE_CLOSE,
            FUNCTION_BODY_BLOCK}
        }
    },

    { ELIF_CLAUSES,
        {
            {},
            {ELIF_CLAUSE,
            ELIF_CLAUSES}
        }
    },

    { ELIF_CLAUSE,
        {
            {ELIF,
            BRACE_OPEN,
            LOGICAL_EXPRESSION,
            BRACE_CLOSE,
            FUNCTION_BODY_BLOCK}
        }
    },

    { ELSE_CLAUSE,
        {
            {},
            {ELSE,
            BRACE_OPEN,
            LOGICAL_EXPRESSION,
            BRACE_CLOSE,
            FUNCTION_BODY_BLOCK}
        }
    }
};