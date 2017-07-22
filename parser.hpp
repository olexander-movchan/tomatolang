#ifndef INTERPRETER_PARSER_HPP
#define INTERPRETER_PARSER_HPP


#include <stdexcept>
#include "interpreter.hpp"


class SyntaxError : public std::runtime_error
{
public:
    SyntaxError(char const* const message);
};


#endif //INTERPRETER_PARSER_HPP
