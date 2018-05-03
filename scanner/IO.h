#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <memory>

class InputReader {
    public:
        virtual int nextChar() = 0;
        virtual int peekChar() = 0;
        virtual void skipLine() = 0;
        virtual void skip(std::function<bool(char)> predicate) = 0;
};

class StreamReader: public InputReader {
    public:
        StreamReader(std::shared_ptr<std::istream> stream) : stream(stream) {}
        int nextChar();
        int peekChar();
        void skipLine();
        void skip(std::function<bool(char)> predicate);
    private:
        std::shared_ptr<std::istream> stream;
};