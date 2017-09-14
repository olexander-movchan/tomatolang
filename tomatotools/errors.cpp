#include "errors.hpp"

#include "syntax/syntax_tree.hpp"
#include "syntax/lexer.hpp"


using namespace Tomato;


CodeError::CodeError(const CodePoint &location, const std::string &message)
        : location(location), message(message) {}


const char *CodeError::what() const throw()
{
    return message.c_str();
}


SyntaxError::SyntaxError(const std::string &message) : CodeError(Lexer::Pointer, message)
{
    location = Lexer::Pointer;
}


SemanticError::SemanticError(const std::string &message) : CodeError(AST::Visitor::Pointer, message) {}


NameError::NameError(const std::string &message) : SemanticError(message) {}


TypeError::TypeError(const std::string &message) : SemanticError(message) {}
