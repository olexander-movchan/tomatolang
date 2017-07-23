#ifndef INTERPRETER_PARSER_HPP
#define INTERPRETER_PARSER_HPP


#include <memory>
#include <stdexcept>

#include "syntax_tree.hpp"


class SyntaxError : public std::runtime_error
{
public:
    SyntaxError(std::string message);
    SyntaxError(char const* const message);
};


class Parser
{
public:
    Parser(const std::string &code);

    std::shared_ptr<Expression> parse();

private:
    Lexer lexer;
    Token current_token;

    void eat(TokenType expected_type);
};

#endif //INTERPRETER_PARSER_HPP
