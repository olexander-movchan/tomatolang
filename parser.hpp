#ifndef INTERPRETER_PARSER_HPP
#define INTERPRETER_PARSER_HPP


#include <memory>
#include <stdexcept>

#include "syntax_tree.hpp"


/**
 *
 */
class SyntaxError : public std::runtime_error
{
public:
    /**
     * @brief Constructs an exception for unexpected token
     * @param token Unexpected token
     */
    SyntaxError(const Token &token);

    /**
     * @brief Constructs an exception with custom message
     * @param message Error message
     */
    SyntaxError(std::string message);
};


/**
 * @brief Parser builds abstract syntax tree;
 */
class Parser
{
public:
    Parser(const std::string &code);

    std::shared_ptr<AST::Program> parse();

private:
    Lexer lexer;
    Token current_token;

    void eat(TokenType expected_type);

    std::shared_ptr<AST::Statement> statement();
    std::shared_ptr<AST::Statement> assignment();
    std::shared_ptr<AST::Statement> declaration();

    std::shared_ptr<AST::Expression> expression();
    std::shared_ptr<AST::Expression> sum();
    std::shared_ptr<AST::Expression> product();
    std::shared_ptr<AST::Expression> power();
    std::shared_ptr<AST::Expression> factor();
};


#endif //INTERPRETER_PARSER_HPP
