#ifndef INTERPRETER_LEXER_HPP
#define INTERPRETER_LEXER_HPP


#include <iostream>


enum class TokenType
{
    Unknown,
    Integer,
    OperatorPlus,
    OperatorMinus,
    OperatorMul,
    OperatorDiv,
    OperatorPow,
    LeftParen,
    RightParen,
    EndOfFile,
};


std::ostream& operator<<(std::ostream& stream, const TokenType type);


struct Token
{
    TokenType   type;
    std::string lexeme;
};


std::ostream& operator<<(std::ostream& stream, const Token &token);


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

    Token integer();
};


#endif //INTERPRETER_LEXER_HPP
