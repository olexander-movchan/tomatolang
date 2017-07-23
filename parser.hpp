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


/**
 * @brief Expression parser.
 *
 * Expression parser builds abstract syntax tree from token sequence produced by lexer.
 *
 * expression := sum
 * sum        := product ( (PLUS | MINUS) product )*
 * product    := power ( (MUL | DIV) power )*
 * power      := factor [ POW power ]
 * factor     := CONSTANT | LPAREN expression RPAREN
 */
class Parser
{
public:
    Parser(const std::string &code);

    std::shared_ptr<Expression> parse();

private:
    Lexer lexer;
    Token current_token;

    void eat(TokenType expected_type);

    std::shared_ptr<Expression> expression();
    std::shared_ptr<Expression> sum();
    std::shared_ptr<Expression> product();
    std::shared_ptr<Expression> power();
    std::shared_ptr<Expression> factor();
};

#endif //INTERPRETER_PARSER_HPP
