#ifndef INTERPRETER_ERROR_HPP
#define INTERPRETER_ERROR_HPP


#include <stdexcept>

#include "token.hpp"


/**
 * @brief CodeError represents error in the source code.
 */
class CodeError : public std::exception
{
public:
    CodeError(const Token &token, const std::string &message);

    const char *what() const throw () override;

public:
    Token        token;
    std::string  message;
};


/**
 * @brief SyntaxError represents invalid tokens or syntactic structures.
 */
class SyntaxError : public CodeError
{
public:
    SyntaxError(const struct Token &token, const std::string &message);
};


/**
 * @brief NameError represents undefined references or repeated definitions.
 */
class NameError : public CodeError
{
public:
    NameError(const struct Token &token, const std::string &message);
};


/**
 * @brief TypeError represents operation on incompatible types.
 */
class TypeError : public CodeError
{
public:
    TypeError() : CodeError(Token(), "") {}
};


#endif //INTERPRETER_ERROR_HPP
