#include "IO.h"
#include <exception>
#include <limits>
#include <ios>

StreamReader::StreamReader(std::shared_ptr<std::istream> stream) : stream(stream), line(0), position(0) {
}

int StreamReader::nextChar() {
    char c;
    if(stream->get(c)) {
        position++;
        if(c == '\n') {
            position = 0;
            line++;
        }
        return c;
    }
    else return -1;
}

int StreamReader::peekChar() {
    if(stream->peek() > 0) return stream->peek();
    else return -1;
}

void StreamReader::skipLine() {
    line++;
    position=0;
    stream->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void StreamReader::skip(std::function<bool(char)> predicate) {
    while(stream->peek() != EOF && predicate(stream->peek())) {
        position++;
        char c = stream->get();
        if(c == '\n') {
            position = 0;
            line++;
        }
    }
}

int StreamReader::getLine() {
    return line;
}

int StreamReader::getPosition() {
    return position;
}