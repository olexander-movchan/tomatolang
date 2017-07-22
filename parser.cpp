#include "parser.hpp"


SyntaxError::SyntaxError(char const *const message) : runtime_error(message) {}
