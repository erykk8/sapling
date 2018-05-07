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
                currentToken = TokenType::SUBTRACT;
                currentToken.setString(buf.str());
            }
            else {
                currentToken.setInt(std::stoi(buf.str()));
            }
            break;
        default:
            while(digit(reader->peekChar())) {
                buf << (char)reader->nextChar();
            }
            if(buf.str() != "") {
                currentToken.setInt(std::stoi(buf.str()));
            }
            else return false;
            break;
            
    }
    return true;
}