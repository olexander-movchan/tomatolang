#ifndef INTERPRETER_PARSER_HPP
#define INTERPRETER_PARSER_HPP


#include <memory>
#include <stdexcept>

#include "syntax_tree.hpp"
#include "lexer.hpp"


/**
 * @brief Parser builds abstract syntax tree;
 */
class Parser
{
public:
    std::shared_ptr<AST::Statements> parse(const std::string &code);

private:
    std::unique_ptr<Lexer>  lexer;
    Token                   current_token;

    void shift(Token::Type expected_type);

    std::shared_ptr<AST::Statements>  statements();
    std::shared_ptr<AST::Statement>   statement();
    std::shared_ptr<AST::Declaration> declaration();
    std::shared_ptr<AST::Conditional> conditional();
    std::shared_ptr<AST::WhileLoop>   while_loop();
    std::shared_ptr<AST::Print>       print();

    std::shared_ptr<AST::Expression> expression(int curr_precedence = 0);
    std::shared_ptr<AST::Expression> term();
};


#endif //INTERPRETER_PARSER_HPP
