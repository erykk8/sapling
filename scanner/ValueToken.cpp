#include "Scanner.h"
#include <sstream>

bool Scanner::valueToken() {
    std::stringstream buf;

    switch(reader->peekChar()) {
        case '-':
            buf << (char)reader->nextChar();
            while(digit(reader->peekChar())) {
                buf << (char)reader->nextChar();
            }

            if(buf.str() == "-") {
                currentToken = Token::SUBTRACT;
                currentToken.setOtherValue(buf.str());
            }
            else if(reader->peekChar() == '.') {
                buf << (char)reader->nextChar();
                while(digit(reader->peekChar())) {
                    buf << (char)reader->nextChar();
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
                buf << (char)reader->nextChar();
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
                buf << (char)reader->nextChar();
            }
            if(reader->peekChar() == '.') {
                buf << (char)reader->nextChar();
                while(digit(reader->peekChar())) {
                    buf << (char)reader->nextChar();
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