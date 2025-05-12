#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

// Token types
enum Token {
    tok_eof = -1,

    // Keywords
    tok_func = -2,
    tok_return = -3,

    // Identifiers and literals
    tok_identifier = -4,
    tok_number = -5,
    
    // Add some additional tokens for future expansion
    tok_if = -6,
    tok_else = -7,
    tok_while = -8,
    tok_semicolon = -9,
};

// These are defined in lexer.cpp and used elsewhere
extern std::string IdentifierStr; // For tok_identifier
extern double NumVal;             // For tok_number

/**
 * Returns the next token from standard input
 * Updates IdentifierStr or NumVal as appropriate
 */
int gettok();

#endif