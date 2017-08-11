#include "error.hpp"
#include "lexer.hpp"


SyntaxError::SyntaxError(const std::string &message) : runtime_error(message) {}

SyntaxError::SyntaxError(const Token &token) : runtime_error("Unexpected token: " + token.lexeme) {}
