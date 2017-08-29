#ifndef TOMATO_TOKEN_HPP
#define TOMATO_TOKEN_HPP


#include <string>

#include "codepoint.hpp"


namespace Tomato
{
    /**
     * Token represents lexical token in source code.
     */
    class Token
    {
    public:
        enum class Type
        {
            Invalid, EndOfLine, EndOfFile,

            Literal, Identifier, Assign, Print,

            And, Or, Not,
            LT, LE, GT, GE, EQ, NE,
            Add, Sub, Mul, Div, IntDiv, Mod, Exp,

            LParen, RParen,

            Var, Let,

            If, Then, Else, End, For, In, While, Do,
        };

        Token() = default;

        Token(const Type &type, const std::string &lexeme, const CodePoint &position = CodePoint());

        Type         type;
        std::string  lexeme;
        CodePoint    position;

        bool is_binary_op() const;

        bool is_unary_op() const;
    };
}


#endif //TOMATO_TOKEN_HPP
