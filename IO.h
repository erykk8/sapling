#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

#define EOT 4
#define MAX_LINE_LENGTH 8192

class InputReader {
    public:
        virtual char nextChar() = 0;
        virtual void skipLine() = 0;
        virtual void skip(std::function<bool(char)> predicate) = 0;
};

class StreamReader: public InputReader {
    public:
        StreamReader(std::istream& stream) : stream(stream) {}
        char nextChar();
        void skipLine();
        void skip(std::function<bool(char)> predicate);
    private:
        std::istream& stream;
};