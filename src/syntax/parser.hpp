#ifndef TOMATO_SYNTAX_PARSER_H
#define TOMATO_SYNTAX_PARSER_H


#include "lexer.hpp"
#include "syntax_tree.hpp"


namespace Tomato::Syntax
{
    class SyntaxError : public std::runtime_error
    {
    public:
        using runtime_error::runtime_error;
    };


    /**
     * @brief Tomato language syntax parser.
     *
     * Handwritten recursive descent LL(1) parser.
     */
    class Parser
    {
    public:
        void set_text(const std::string &text);
        std::shared_ptr<ASTNode> parse();
        bool eof() const;

    private:
        std::shared_ptr<Expression> expression();
        std::shared_ptr<Expression> expression(int precedence);

        std::shared_ptr<Expression> term();

        std::shared_ptr<Identifier> identifier();
        std::shared_ptr<Literal> literal();

        std::shared_ptr<Statement> statement();
        std::shared_ptr<ValueDeclaration> value_declaration();
        std::shared_ptr<PrintStatement> print_statement();
        std::shared_ptr<ReadStatement> read_statement();

    private:
        /**
         * @brief Accept current token, proceed to the next.
         */
        void accept();

        /**
         * @brief Reject current token, cause syntax error.
         * @param expected Part of error description, what terminals/nonterminals were expected.
         * @throw SyntaxError
         */
        void reject(const std::string &expected);

        /**
         * @brief Accept token if it matches, else reject.
         * @param expected Expected terminal.
         * @throw SyntaxError
         */
        void expect(Terminal expected);

    private:
        Lexer lexer;
        Token current;
    };
}


#endif //TOMATO_SYNTAX_PARSER_H
