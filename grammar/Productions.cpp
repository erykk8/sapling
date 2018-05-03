#include "Productions.h"
#include "Token.h"

using namespace TokenType;


std::map<TokenType::Type, const std::vector<Productions::symbol_sequence>> Productions::data =
{
    { PROGRAM, 
        {
            {(Token)EOT},
            {(Token)FUNCTION_DECLARATION, 
            (Token)PROGRAM}
        }
    },

    { FUNCTION_DECLARATION,
        {
            {(Token)TYPE,
            (Token)IDENTIFIER,
            (Token)PARAMETER_DECLARATION,
            (Token)ASSIGNMENT_OPERATOR,
            (Token)FUNCTION_BODY_BLOCK}
        }
    },
    
    { FUNCTION_CALL,
        {
            {(Token)IDENTIFIER,
            (Token)PARAMETER_CALL}
        }
    },

    { PARAMETER_DECLARATION,
        {
            {(Token)BRACE_OPEN,
            (Token)ARG_LIST,
            (Token)BRACE_CLOSE}
        }
    },

    { PARAMETER_CALL,
        {
            {(Token)BRACE_OPEN,
            (Token)VALUE_LIST,
            (Token)BRACE_CLOSE}
        }
    },
    
    { ARG_LIST,
        {
            {},
            {(Token)TYPE,
            (Token)IDENTIFIER,
            (Token)ARG_LIST_P}
        }
    },

    { ARG_LIST_P,
        {
            {},
            {(Token)COMMA,
            (Token)TYPE,
            (Token)IDENTIFIER,
            (Token)ARG_LIST_P}
        }
    },

    { VALUE_LIST,
        {
            {},
            {(Token)VALUE_EXPRESSION,
            (Token)VALUE_LIST_P}
        }
    },

    { VALUE_LIST_P,
        {
            {},
            {(Token)COMMA,
            (Token)VALUE_EXPRESSION,
            (Token)VALUE_LIST_P}
        }
    },

    { TYPE,
        {
            {(Token)INT_TYPE},
            {(Token)REAL_TYPE},
            {(Token)BOOL_TYPE},
            {(Token)STRING_TYPE},
            {(Token)LAMBDA_TYPE}
        }
    },

    { LAMBDA_TYPE_LIST,
        {   
            {},
            {(Token)VOID_TYPE},
            {(Token)TYPE,
            (Token)TYPE_LIST_P}
        }
    },

    { TYPE_LIST,
        {
            {(Token)TYPE,
            (Token)TYPE_LIST_P}
        }
    },

    { VALUE_LIST_P,
        {
            {},
            {(Token)COMMA,
            (Token)TYPE,
            (Token)TYPE_LIST_P}
        }
    },

    { LAMBDA_TYPE,
        {
            {(Token)BRACE_OPEN,
            (Token)LAMBDA_TYPE_LIST,
            (Token)BRACE_CLOSE,
            (Token)RETURN_ARROW,
            (Token)BRACE_OPEN,
            (Token)TYPE_LIST,
            (Token)BRACE_CLOSE}
        }
    },

    { LAMBDA,
        {
            {(Token)BRACE_OPEN,
            (Token)ARG_LIST,
            (Token)BRACE_CLOSE,
            (Token)RETURN_ARROW,
            (Token)FUNCTION_BODY_BLOCK}
        }
    },

    { VALUE_OR_INSTRUCTION_BLOCK,
        {
            {(Token)VALUE_BLOCK},
            {(Token)INSTRUCTION_BLOCK}
        }
    },

    { FUNCTION_BODY_BLOCK,
        {
            {(Token)VALUE_BLOCK},
            {(Token)CURLY_BRACE_OPEN,
            (Token)VALUE_OR_INSTRUCTION_BLOCK,
            (Token)CURLY_BRACE_CLOSE}
        }
    },

    { VALUE_BLOCK,
        {
            {(Token)IF_BLOCK},
            {(Token)VALUE_EXPRESSION}
        }
    },

    { VALUE_EXPRESSION,
        {
            {(Token)LOGICAL_EXPRESSION,
            (Token)STRING_VALUE,
            (Token)LAMBDA}
        }
    },

    { NUMERIC_EXPRESSION,
        {
            {(Token)MULTIPLICATION,
            (Token)ADDITION_P}
        }
    },

    { ADDITION_P,
        {
            {},
            {(Token)ADD,
            (Token)NUMERIC_EXPRESSION},
            {(Token)SUBTRACT,
            (Token)NUMERIC_EXPRESSION}
        }
    },

    { MULTIPLICATION,
        {
            {(Token)POWER_RAISING,
            (Token)MULTIPLICATION_P}
        }
    },

    { MULTIPLICATION_P,
        {
            {},
            {(Token)MULTIPLY,
            (Token)MULTIPLICATION},
            {(Token)DIVIDE,
            (Token)MULTIPLICATION},
            {(Token)INT_DIVIDE,
            (Token)MULTIPLICATION}
        }
    },

    { POWER_RAISING,
        {
            {(Token)NUMERIC_OPERAND,
            (Token)POWER_P}
        }
    },

    { POWER_P,
        {
            {},
            {(Token)POWER,
            (Token)POWER_RAISING},
        }
    },

    { NUMERIC_OPERAND,
        {
            {(Token)INT_VALUE},
            {(Token)REAL_VALUE},
            {(Token)IDENTIFIER},
            {(Token)FUNCTION_CALL},
            {(Token)BRACE_OPEN,
            (Token)NUMERIC_EXPRESSION,
            (Token)BRACE_CLOSE}
        }
    },

    { LOGICAL_EXPRESSION,
        {
            {(Token)CONJUNCTION,
            (Token)DISJUNCTION_P}
        }
    },

    { DISJUNCTION_P,
        {
            {},
            {(Token)OR,
            (Token)LOGICAL_EXPRESSION}
        }
    },

    { CONJUNCTION,
        {
            {(Token)NEGATION,
            (Token)CONJUNCTION_P}
        }
    },

    { CONJUNCTION_P,
        {
            {},
            {(Token)AND,
            (Token)CONJUNCTION}
        }
    },

    { NEGATION,
        {
            {(Token)COMPARISON},
            {(Token)NOT,
            (Token)COMPARISON}
        }
    },

    { COMPARISON,
        {
            {(Token)LOGICAL_OPERAND,
            (Token)COMPARISON_P}
        }
    },

    { COMPARISON_OPERATOR,
        {
            {(Token)LESS_THAN},
            {(Token)LESS_EQUAL},
            {(Token)GREATER_THAN},
            {(Token)GREATER_EQUAL},
            {(Token)EQUAL},
            {(Token)NOT_EQUAL}
        }
    },

    { COMPARISON_P,
        {
            {},
            {(Token)COMPARISON_OPERATOR,
            (Token)LOGICAL_OPERAND}
        }
    },

    { LOGICAL_OPERAND,
        {
            {(Token)BOOL_VALUE},
            {(Token) NUMERIC_EXPRESSION},
            {(Token)BRACE_OPEN,
            (Token)LOGICAL_EXPRESSION,
            (Token)BRACE_CLOSE}
        }
    },

    { INSTRUCTION_BLOCK,
        {
            {(Token)RETURN_INSTRUCTION},
            {(Token)INSTRUCTION,
            (Token)INSTRUCTION_BLOCK},
        }
    },

    { INSTRUCTION,
        {
            {(Token)FUNCTION_DECLARATION},
            {(Token)VALUE_BLOCK},
        }
    },

    { RETURN_INSTRUCTION,
        {
            {(Token)RETURN,
            (Token)VALUE_BLOCK},
        }
    },

    { IF_BLOCK,
        {
            {(Token)IF_CLAUSE,
            (Token)ELIF_CLAUSES,
            (Token)ELSE_CLAUSE}
        }
    },

    { IF_CLAUSE,
        {
            {(Token)IF,
            (Token)BRACE_OPEN,
            (Token)LOGICAL_EXPRESSION,
            (Token)BRACE_CLOSE,
            (Token)FUNCTION_BODY_BLOCK}
        }
    },

    { ELIF_CLAUSES,
        {
            {},
            {(Token)ELIF_CLAUSE,
            (Token)ELIF_CLAUSES}
        }
    },

    { ELIF_CLAUSE,
        {
            {(Token)ELIF,
            (Token)BRACE_OPEN,
            (Token)LOGICAL_EXPRESSION,
            (Token)BRACE_CLOSE,
            (Token)FUNCTION_BODY_BLOCK}
        }
    },

    { ELSE_CLAUSE,
        {
            {},
            {(Token)ELSE,
            (Token)BRACE_OPEN,
            (Token)LOGICAL_EXPRESSION,
            (Token)BRACE_CLOSE,
            (Token)FUNCTION_BODY_BLOCK}
        }
    }
};