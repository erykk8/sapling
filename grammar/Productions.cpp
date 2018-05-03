#include "Productions.h"
#include "NonTerminal.h"
#include "Token.h"

std::unordered_map<NonTerminal, std::vector<symbol_sequence>> Productions::data = 
{
    { NonTerminal::PROGRAM, {{Token::EOF}, {NonTerminal::FUNCTION_DECLARATION, NonTerminal::PROGRAM}} },
    // TODO
}