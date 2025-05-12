#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include "ast.hpp"

extern int CurTok;
int getNextToken();

std::unique_ptr<FunctionAST> ParseFunction();

#endif