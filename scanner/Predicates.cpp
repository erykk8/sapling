#include "Scanner.h"
#include <functional>

std::function<bool(char)> Scanner::whiteSpace = [](char c) -> bool { return c <= ' '; };
        
std::function<bool(char)> Scanner::alphanumericOrUnderscore = [](char c) -> bool { 
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
};

std::function<bool(char)> Scanner::digit = [](char c) -> bool { 
            return (c >= '0' && c <= '9');
        };

std::function<bool(char)> Scanner::stringable = [](char c) -> bool { 
    return (c >= ' ' && c <= '~' && c != '"');
};