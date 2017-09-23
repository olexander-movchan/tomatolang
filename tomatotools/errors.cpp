#include "errors.hpp"


using namespace Tomato;


CodeError::CodeError(const CodePoint &location, const std::string &message)
        : location(location), message(message) {}


const char *CodeError::what() const throw()
{
    return message.c_str();
}


SyntaxError::SyntaxError     (const CodePoint &location, const std::string &message) : CodeError(location, message) {}
SemanticError::SemanticError (const CodePoint &location, const std::string &message) : CodeError(location, message) {}
NameError::NameError         (const CodePoint &location, const std::string &message) : SemanticError(location, message) {}
TypeError::TypeError         (const CodePoint &location, const std::string &message) : SemanticError(location, message) {}
