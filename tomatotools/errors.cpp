#include "errors.hpp"


using namespace Tomato;


CodeError::CodeError(const Token &token, const std::string &message)
        : token(token), message(message) {}

const char *CodeError::what() const throw()
{
    return message.c_str();
}


SyntaxError::SyntaxError(const struct Token &token, const std::string &message)
        : CodeError(token, message) {}

NameError::NameError(const struct Token &token, const std::string &message)
        : CodeError(token, message) {}
