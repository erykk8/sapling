#pragma once
#include <string>

class Token {
    public:
        enum Type   { IF, ELSE, RETURN, RETURN_ARROW, COMMA,
                        TYPE_KEYWORD,
                        LOGICAL_OPERATOR,
                        INT_VALUE, BOOL_VALUE, REAL_VALUE, STRING_VALUE,
                        IDENTIFIER,
                        ASSIGNMENT_OPERATOR,
                        COMPARISON_OPERATOR,
                        ARITHMETIC_OPERATOR,
                        CURLY_BRACE_OPEN, CURLY_BRACE_CLOSE,
                        BRACE_OPEN, BRACE_CLOSE,
                        SQUARE_BRACE_OPEN, SQUARE_BRACE_CLOSE,
                        EOL, EOF
                    };
        Token();
        Token(Type type) : type(type) {}

        Type getType() const;
        int getInt() const;
        bool getBool() const;
        double getReal() const;
        std::string getString() const;

        void setInt(int value);
        void setBool(bool value);
        void setReal(double value);
        void setString(std::string value);
    private:
        int line;
        int position;
        Type type;
        union {
            int integer;
            bool boolean;
            double real;
            std::string string;
        } value;

};
