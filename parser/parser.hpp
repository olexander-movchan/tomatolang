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
    Parser(const std::string &code);

    std::shared_ptr<AST::Program> parse();

private:
    Lexer lexer;
    Token current_token;

    void shift(Token::Type expected_type);

    std::shared_ptr<AST::Statement> statement();
    std::shared_ptr<AST::Statement> declaration();

    std::shared_ptr<AST::Expression> expression(int curr_precedence = 0);
    std::shared_ptr<AST::Expression> term();
};


#endif //INTERPRETER_PARSER_HPP
