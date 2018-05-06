#pragma once
#include <string>
#include <vector>

namespace TokenType {
    enum Type   {
                    IF, ELIF, ELSE, RETURN, RETURN_ARROW, COMMA,
                        INT_TYPE, BOOL_TYPE, REAL_TYPE, STRING_TYPE, VOID_TYPE,
                        NOT, AND, OR,
                        INT_VALUE, BOOL_VALUE, REAL_VALUE, STRING_VALUE,
                        IDENTIFIER,
                        ASSIGNMENT_OPERATOR,
                        LESS_THAN, GREATER_THAN, LESS_EQUAL, GREATER_EQUAL,
                        EQUAL, NOT_EQUAL,
                        POWER, MULTIPLY, INT_DIVIDE, DIVIDE, ADD, SUBTRACT,
                        CURLY_BRACE_OPEN, CURLY_BRACE_CLOSE,
                        BRACE_OPEN, BRACE_CLOSE,
                        SQUARE_BRACE_OPEN, SQUARE_BRACE_CLOSE,
                        EOT,
                };
}

class Token {
    public:
        Token() : type(TokenType::EOT) {}
        Token(const TokenType::Type& type) : type(type) {};
        ~Token() = default;

        bool isTerminal() const;

        TokenType::Type getType() const;
        int getInt() const;
        bool getBool() const;
        double getReal() const;
        std::string getString() const;

        std::string getName() const;

        void setInt(int value);
        void setBool(bool value);
        void setReal(double value);
        void setString(std::string value);

        void setOtherValue(std::string value);

        void setLine(int line);
        void setPosition(int position);

        bool operator==(const TokenType::Type type) const;
        bool operator!=(const TokenType::Type type) const;
        operator TokenType::Type() const { return type; }

        int getLine() const;
        int getPosition() const;

    private:
        int line;
        int position;
        TokenType::Type type;
        union {
            int integer;
            bool boolean;
            double real;
        };
        std::string string; // lazy

        static std::vector<std::string> names;
};
