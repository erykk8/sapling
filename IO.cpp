#include "IO.h"
#include <exception>

char StreamReader::nextChar() {
    char c;
    if(stream.get(c)) return c;
    else return EOT;
}

void StreamReader::skipLine() {
    stream.ignore(MAX_LINE_LENGTH, '\n');
}

void StreamReader::skip(std::function<bool(char)> predicate) {
    while(stream.peek() != EOF && predicate(stream.peek())) {
        stream.get();
    }
}