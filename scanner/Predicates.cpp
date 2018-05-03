#include "Scanner.h"
#include <functional>
#include <cctype>

std::function<bool(int)> Scanner::whiteSpace = isspace;
        
std::function<bool(int)> Scanner::alphanumericOrUnderscore = [](int c) -> bool { 
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
};

std::function<bool(int)> Scanner::digit = isdigit;

std::function<bool(int)> Scanner::stringable = [](int c) -> bool { 
    return (c >= ' ' && c <= '~' && c != '"');
};