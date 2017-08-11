#ifndef INTERPRETER_PARSER_HPP
#define INTERPRETER_PARSER_HPP


#include <memory>
#include <stdexcept>

#include "syntax_tree.hpp"


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

    void eat(Token::Type expected_type);

    std::shared_ptr<AST::Statement> statement();
    std::shared_ptr<AST::Statement> assignment();
    std::shared_ptr<AST::Statement> declaration();

    std::shared_ptr<AST::Expression> expression();
    std::shared_ptr<AST::Expression> term();
    std::shared_ptr<AST::Expression> power();
    std::shared_ptr<AST::Expression> factor();
};


#endif //INTERPRETER_PARSER_HPP
