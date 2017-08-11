#ifndef INTERPRETER_ERROR_HPP
#define INTERPRETER_ERROR_HPP


#include <stdexcept>


/**
 * @brief Syntax error represents invalid tokens or syntactic structures.
 */
class SyntaxError : public std::runtime_error
{
public:
    SyntaxError(const std::string &message);

    SyntaxError(const struct Token &token);
};


#endif //INTERPRETER_ERROR_HPP
