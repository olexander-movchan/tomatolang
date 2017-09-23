#ifndef TOMATO_ERRORS_HPP
#define TOMATO_ERRORS_HPP


#include <stdexcept>

#include "syntax/codepoint.hpp"


namespace Tomato
{
    /**
     * @brief CodeError represents error in the source code.
     */
    class CodeError : public std::exception
    {
    public:
        CodeError(const CodePoint &location, const std::string &message);

        const char *what() const throw() override;

    public:
        CodePoint   location;
        std::string message;
    };


    /**
     * @brief SyntaxError represents invalid tokens or syntactic structures.
     */
    class SyntaxError : public CodeError
    {
    public:
        SyntaxError(const CodePoint &location, const std::string &message);
    };


    class SemanticError : public CodeError
    {
    public:
        SemanticError(const CodePoint &location, const std::string &message);
    };


    /**
     * @brief NameError represents undefined references or repeated definitions.
     */
    class NameError : public SemanticError
    {
    public:
        NameError(const CodePoint &location, const std::string &message);
    };


    /**
     * @brief TypeError represents operation on incompatible types.
     */
    class TypeError : public SemanticError
    {
    public:
        TypeError(const CodePoint &location, const std::string &message);
    };
}


#endif //TOMATO_ERRORS_HPP
