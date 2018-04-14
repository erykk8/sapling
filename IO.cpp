#include "IO.h"
#include <exception>

char StreamReader::nextChar() {
    char c;
    if(stream->get(c)) return c;
    else return IO_EOT;
}

char StreamReader::peekChar() {
    if(stream->peek() > 0) return stream->peek();
    else return IO_EOT;
}

void StreamReader::skipLine() {
    stream->ignore(MAX_LINE_LENGTH, '\n');
}

void StreamReader::skip(std::function<bool(char)> predicate) {
    while(stream->peek() != EOF && predicate(stream->peek())) {
        stream->get();
    }
}