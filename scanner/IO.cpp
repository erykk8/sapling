#include "IO.h"
#include <exception>
#include <limits>
#include <ios>

int StreamReader::nextChar() {
    char c;
    if(stream->get(c)) return c;
    else return -1;
}

int StreamReader::peekChar() {
    if(stream->peek() > 0) return stream->peek();
    else return -1;
}

void StreamReader::skipLine() {
    stream->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void StreamReader::skip(std::function<bool(char)> predicate) {
    while(stream->peek() != EOF && predicate(stream->peek())) {
        stream->get();
    }
}