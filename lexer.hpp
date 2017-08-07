#ifndef INTERPRETER_LEXER_HPP
#define INTERPRETER_LEXER_HPP


#include <iostream>
#include <set>
#include <map>


enum class TokenType
{
    None,
    EndOfFile,

    Literal,
    Identifier,

    OperatorPlus,
    OperatorMinus,
    OperatorMul,
    OperatorDiv,
    OperatorPow,
    Assignment,

    LeftParen,
    RightParen,
    VariableDeclaration,
};


struct Token
{
    TokenType   type;
    std::string lexeme;

    operator std::string() const;
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
