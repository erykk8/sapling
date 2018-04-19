#include "Scanner.h"
#include <sstream>

bool Scanner::valueToken() {
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