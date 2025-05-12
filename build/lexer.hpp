#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

// Token enumeration (if not already added)
enum Token {
    tok_eof = -1,
    tok_func = -2,
    tok_identifier = -3,
    tok_number = -4,
    tok_return = -5,
    tok_op = -6
    // ... add other tokens if needed
};

// Externs to be shared across files
extern std::string IdentifierStr;
extern double NumVal;

// Declare the function here
int getNextToken();

#endif
