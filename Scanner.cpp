#include "Scanner.h"
#include <sstream>

Scanner::Scanner(std::shared_ptr<InputReader> reader) : reader(reader) {}

Token Scanner::getNextToken() {
    readNextToken();
    return currentToken;
}

void Scanner::readNextToken() {
    reader->skip(whiteSpace);

    while(reader->peekChar() == '#') {
        reader->skipLine();
        reader->skip(whiteSpace);
    }

    if (tryEot()) {
        currentToken = Token::EOT;
        return;
    }

    if (tryKeywordOrIdentifier() || tryBraces() || trySeparator() || tryConstant()
        || tryOperator() || tryReturnArrowComparisonAssignment() )
        return;

    throwUnknownToken();
        
}

void Scanner::throwUnknownToken() {
    std::stringstream buf;
    buf << "Unknown token, starting with: " << (int)(reader->peekChar());
    throw std::runtime_error(buf.str());

}

void Scanner::throwInvalidString() {
    const std::string msg = "Invalid character in string constant: ";
    throw std::runtime_error(msg + static_cast<char>(reader->peekChar()));
}

bool Scanner::tryKeywordOrIdentifier() {
    std::stringstream buf;

    while(alphanumericOrUnderscore(reader->peekChar())) {
        buf << reader->nextChar();
    }

    // lazy
    if(buf.str() == "return") {
        currentToken = Token::RETURN;
    }
    else if(buf.str() == "if") {
        currentToken = Token::IF;
    }
    else if(buf.str() == "elif") {
        currentToken = Token::ELIF;
    }
    else if(buf.str() == "else") {
        currentToken = Token::ELSE;
    }
    else if(buf.str() == "and" || buf.str() == "or" || buf.str() == "not") {
        currentToken = Token::LOGICAL_OPERATOR;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str() == "True") {
        currentToken.setBool(true);
    }
    else if(buf.str() == "False") {
        currentToken.setBool(false);
    }
    else if(buf.str() == "Int" || buf.str() == "String" || buf.str() == "Real" || buf.str() == "Bool"
            || buf.str() == "List" || buf.str() == "Set" || buf.str() == "Void") {
        currentToken = Token::TYPE_KEYWORD;
        currentToken.setOtherValue(buf.str());
    }
    else if(buf.str().length() > 0) {
        currentToken = Token::IDENTIFIER;
    }
    else return false;

    return true;
}

bool Scanner::tryReturnArrowComparisonAssignment() {
    std::stringstream buf;

    if (reader->peekChar() == '=') {
        buf << reader->nextChar();
        char c = reader->peekChar();
        switch(c) {
            case '>':
                reader->nextChar();
                currentToken = Token::RETURN_ARROW;
                buf << c;
                break;
            case '=':
                reader->nextChar();
                currentToken = Token::COMPARISON_OPERATOR;
                buf << c;
                break;
            default:
                currentToken = Token::ASSIGNMENT_OPERATOR;
                break;
        }
        currentToken.setOtherValue(buf.str());
        return true;
    }
    return false;
}

bool Scanner::tryBraces() {
    switch(reader->peekChar()) {
        case '{':
            currentToken = Token::CURLY_BRACE_OPEN;
            break;
        case '}':
            currentToken = Token::CURLY_BRACE_CLOSE;
            break;
        case '(':
            currentToken = Token::BRACE_OPEN;
            break;
        case ')':
            currentToken = Token::BRACE_CLOSE;
            break;
        case '[':
            currentToken = Token::SQUARE_BRACE_OPEN;
            break;
        case ']':
            currentToken = Token::SQUARE_BRACE_CLOSE;
            break;
        default:
            return false;
    }
    reader->nextChar();
    return true;
}

bool Scanner::tryConstant() {
    std::stringstream buf;

    switch(reader->peekChar()) {
        case '-':
            buf << reader->nextChar();
            while(digit(reader->peekChar())) {
                buf << reader->nextChar();
            }

            if(buf.str() == "-") {
                currentToken = Token::ARITHMETIC_OPERATOR;
                currentToken.setOtherValue(buf.str());
            }
            else if(reader->peekChar() == '.') {
                buf << reader->nextChar();
                while(digit(reader->peekChar())) {
                    buf << reader->nextChar();
                }
                currentToken.setReal(std::stod(buf.str()));
            }
            else {
                currentToken.setInt(std::stoi(buf.str()));
            }
            break;
        case '"':
            reader->nextChar();
            while(stringable(reader->peekChar())) {
                buf << reader->nextChar();
            }
            if(reader->peekChar() == '"') {
                reader->nextChar();
                currentToken.setString(buf.str());
            }
            else
                throwInvalidString();
            break;
        default:
            while(digit(reader->peekChar())) {
                buf << reader->nextChar();
            }
            if(reader->peekChar() == '.') {
                buf << reader->nextChar();
                while(digit(reader->peekChar())) {
                    buf << reader->nextChar();
                }
                currentToken.setReal(std::stod(buf.str()));
            }
            else if(buf.str() != "" && buf.str() != ".") {
                currentToken.setInt(std::stoi(buf.str()));
            }
            else return false;
            break;
            
    }
    return true;

}


bool Scanner::trySeparator() {
    switch(reader->peekChar()) {
        case ',':
            currentToken = Token::COMMA;
            break;
        case ':':
            currentToken = Token::COLON;
            break;
        default:
            return false;
    }
    reader->nextChar();
    return true;
}

bool Scanner::tryOperator() {
    std::stringstream buf;
    switch(reader->peekChar()) {
        case '>':
        case '<':
        case '!':
            currentToken = Token::COMPARISON_OPERATOR;
            buf << reader->nextChar();
            if(reader->peekChar() == '=') {
                buf << reader->nextChar();
            }
            break;
        case '*':
        case '^':
        case '+':
        case '-':
            currentToken = Token::ARITHMETIC_OPERATOR;
            buf << reader->nextChar();
            break;
        case '/':
            currentToken = Token::ARITHMETIC_OPERATOR;
            buf << reader->nextChar();
            if(reader->peekChar() == '/') {
                buf << reader->nextChar();
            }
            break;
        default:
            return false;
    }
    currentToken.setOtherValue(buf.str());
    return true;
}


bool Scanner::tryEot() {
    return reader->peekChar() == IO_EOT;
}


