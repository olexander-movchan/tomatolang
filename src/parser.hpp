#ifndef TOMATO_PARSER_H
#define TOMATO_PARSER_H


#include "lexer.hpp"
#include "syntax_tree.hpp"


namespace Tomato::Syntax
{
    class Parser
    {
    public:
        void reset(const std::string &text);

        std::shared_ptr<Statement> statement();
        std::shared_ptr<Expression> expression();

    private:
        void accept();
        void expect(Terminal terminal);

        std::shared_ptr<Expression> expression(int precedence);
        std::shared_ptr<Expression> term();

    private:
        Lexer lexer;
        Token current;
    };
}


#endif //TOMATO_PARSER_H
