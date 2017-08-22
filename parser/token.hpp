#ifndef INTERPRETER_TOKEN_HPP
#define INTERPRETER_TOKEN_HPP


#include <string>


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


    /**
     * Position represents location in source code file.
     */
    struct Position
    {
        std::size_t line   = 1;
        std::size_t column = 1;
    };


    Token() = default;
    Token(const Type &type, const std::string &lexeme, std::size_t position);


    Type         type;
    std::string  lexeme;
    std::size_t  position;


    bool is_binary_op() const;
    bool is_unary_op() const;
};


#endif //INTERPRETER_TOKEN_HPP
