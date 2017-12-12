#ifndef TOMATO_PARSER_H
#define TOMATO_PARSER_H


#include "lexer.hpp"
#include "syntax_tree.hpp"


namespace Tomato::Syntax
{
    class SyntaxError : public std::runtime_error
    {
    public:
        using runtime_error::runtime_error;
    };


    class Parser
    {
    public:
        void set_text(const std::string &text);

        std::shared_ptr<StatementBlock> statement_block();
        std::shared_ptr<Statement> statement();
        std::shared_ptr<Expression> expression();

        bool eof() const;

    private:
        void accept();
        void expect(Terminal terminal);
        void error(const std::string &expected);

    private:
        std::shared_ptr<Expression> expression(int precedence);
        std::shared_ptr<Expression> term();

        std::shared_ptr<ConditionalStatement>  if_statement();
        std::shared_ptr<ConditionalLoop>       while_statement();
        std::shared_ptr<Statement>             for_statement();
        std::shared_ptr<PrintStatement>        print_statement();
        std::shared_ptr<ReadStatement>         read_statement();
        std::shared_ptr<ValueDeclaration>      value_declaration();

        std::shared_ptr<Identifier> identifier();
    private:
        Lexer lexer;
        Token current;

        std::vector<SyntaxError> m_errors;
    };
}


#endif //TOMATO_PARSER_H
