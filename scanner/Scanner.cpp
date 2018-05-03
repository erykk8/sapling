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

    if (eotToken()) {
        currentToken = TokenType::EOT;
        return;
    }

    if (alphaToken() || braceToken() || separatorToken() || valueToken()
        || operatorToken() || equalsCharacterToken() )
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

bool Scanner::separatorToken() {
    switch(reader->peekChar()) {
        case ',':
            currentToken = TokenType::COMMA;
            break;
        default:
            return false;
    }
    reader->nextChar();
    return true;
}

bool Scanner::eotToken() {
    return reader->peekChar() == -1;
}


