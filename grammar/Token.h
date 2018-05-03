#pragma once
#include "Symbol.h"
#include <string>

class Token: public Symbol {
    public:
        enum Type   {   IF, ELIF, ELSE, RETURN, RETURN_ARROW, COMMA, COLON,
                        INT_TYPE, BOOL_TYPE, REAL_TYPE, STRING_TYPE, VOID_TYPE,
                        NOT, AND, OR,
                        INT_VALUE, BOOL_VALUE, REAL_VALUE, STRING_VALUE,
                        IDENTIFIER,
                        ASSIGNMENT_OPERATOR,
                        COMPARISON_OPERATOR,
                        POWER, MULTIPLY, INT_DIVIDE, DIVIDE, ADD, SUBTRACT,
                        CURLY_BRACE_OPEN, CURLY_BRACE_CLOSE,
                        BRACE_OPEN, BRACE_CLOSE,
                        SQUARE_BRACE_OPEN, SQUARE_BRACE_CLOSE,
                        EOT
                    };
        Token();
        Token(Type type);
        ~Token();

        bool isTerminal() { return true; }

        Type getType() const;
        int getInt() const;
        bool getBool() const;
        double getReal() const;
        std::string getString() const;

        void setInt(int value);
        void setBool(bool value);
        void setReal(double value);
        void setString(std::string value);

        void setOtherValue(std::string value);

        bool operator==(const Type type) const;
        bool operator!=(const Type type) const;
        operator Type() const { return type; }

    private:
        int line;
        int position;
        Type type;
        union {
            int integer;
            bool boolean;
            double real;
        };
        std::string string; // lazy

};
