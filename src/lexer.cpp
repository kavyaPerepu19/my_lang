#include "lexer.hpp"
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>

std::string IdentifierStr; // filled in if tok_identifier
double NumVal;             // filled in if tok_number

int gettok() {
    static int LastChar = ' ';

    // Skip whitespace
    while (isspace(LastChar))
        LastChar = getchar();

    // Identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(LastChar) || LastChar == '_') {
        IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())) || LastChar == '_')
            IdentifierStr += LastChar;

        if (IdentifierStr == "func")
            return tok_func;
        if (IdentifierStr == "return")
            return tok_return;
        if (IdentifierStr == "if")
            return tok_if;
        if (IdentifierStr == "else")
            return tok_else;
        if (IdentifierStr == "while")
            return tok_while;
        return tok_identifier;
    }

    // Number: [0-9]+[.]?[0-9]*
    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        bool hasDecimal = false;
        
        do {
            if (LastChar == '.')
                hasDecimal = true;
                
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || (LastChar == '.' && !hasDecimal));

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    // Check for semicolon
    if (LastChar == ';') {
        LastChar = getchar();
        return tok_semicolon;
    }

    // Comment until end of line
    if (LastChar == '#') {
        do
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }

    // Check for end of file. Don't eat the EOF.
    if (LastChar == EOF)
        return tok_eof;

    // Otherwise, return the character as its ASCII value.
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}