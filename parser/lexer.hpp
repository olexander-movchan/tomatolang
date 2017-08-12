#ifndef INTERPRETER_LEXER_HPP
#define INTERPRETER_LEXER_HPP


#include <string>
#include <map>


struct Token
{
    enum class Type
    {
        None,
        EndOfFile,

        Literal,
        Identifier,

        Add,
        Sub,
        Mul,
        Div,
        Exp,
        Assign,

        LT, LE, GT, GE, EQ, NE,

        And, Or, Not,

        LParen,
        RParen,
        Var,
    };

    Type        type;
    std::string lexeme;

    bool is_bin_operator() const;
};


class Lexer
{
public:
    Lexer(std::string source_code);

    Token next_token();

    bool eof() const;

private:
    std::string code;
    std::size_t offset;

    void skip_whitespace();

    Token literal();
    Token identifier();

    static std::map<std::string, Token> keywords;
};


#endif //INTERPRETER_LEXER_HPP
