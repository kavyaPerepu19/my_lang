#include "lexer.hpp"
#include <cctype>
#include <string>
#include <iostream>

std::string IdentifierStr;
double NumVal;

int getNextToken() {
    static int LastChar = ' ';

    // Skip whitespaces
    while (isspace(LastChar))
        LastChar = getchar();

    // Identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;

        if (IdentifierStr == "func") return tok_func;
        if (IdentifierStr == "return") return tok_return;
        return tok_identifier;
    }

    // Number: [0-9.]+
    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    // Comments
    if (LastChar == '#') {
        do LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        return getNextToken();
    }

    // EOF
    if (LastChar == EOF)
        return tok_eof;

    // Otherwise, return the character as its ASCII value
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}
