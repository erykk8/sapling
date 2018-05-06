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
        virtual int getLine() = 0;
        virtual int getPosition() = 0;
};

class StreamReader: public InputReader {
    public:
        StreamReader(std::shared_ptr<std::istream> stream) : stream(stream), line(0), position(0) {}
        int nextChar();
        int peekChar();
        void skipLine();
        void skip(std::function<bool(char)> predicate);
        int getLine();
        int getPosition();
    private:
        std::shared_ptr<std::istream> stream;
        int line;
        int position;
};