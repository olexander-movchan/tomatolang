#ifndef TOMATO_PARSER_HPP
#define TOMATO_PARSER_HPP


#include <memory>
#include <stdexcept>

#include "syntax_tree.hpp"
#include "lexer.hpp"


namespace Tomato
{
    /**
     * @brief Parser builds abstract syntax tree;
     */
    class Parser
    {
    public:
        std::shared_ptr<AST::AbstractNode> parse(const std::string &code);
        std::shared_ptr<AST::ExpressionNode> expression(const std::string &code);

    private:
        Lexer           lexer;
        Token           current_token;
        CodeNavigator   navigator;

        void shift();
        void shift(Token::Type expected_type);

        std::shared_ptr<AST::StatementListNode>  statement_list();
        std::shared_ptr<AST::StatementNode>      statement();
        std::shared_ptr<AST::DeclarationNode>    declaration();
        std::shared_ptr<AST::ConditionalNode>    conditional();
        std::shared_ptr<AST::LoopNode>           while_loop();
        std::shared_ptr<AST::PrintNode>          print();
        std::shared_ptr<AST::ExpressionNode>     expression(int curr_precedence = 0);
        std::shared_ptr<AST::ExpressionNode>     term();
    };
}


#endif //TOMATO_PARSER_HPP
