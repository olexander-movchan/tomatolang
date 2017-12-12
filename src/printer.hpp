#ifndef TOMATO_PRINTER_HPP
#define TOMATO_PRINTER_HPP


#include <ostream>

#include "visitor.hpp"
#include "syntax_tree.hpp"


namespace Tomato::Syntax
{
    class Printer : private Visitor
    {
    public:
        explicit Printer(std::ostream &stream);

        void print(ASTNode &tree);

    private:
        void process(StatementBlock &node) override;

        void process(Identifier &node) override;

        void process(Literal &node) override;

        void process(BinaryOperation &node) override;

        void process(UnaryOperation &node) override;

        void process(Indexation &node) override;

        void process(Call &node) override;

        void process(MemberAccess &node) override;

        void process(ConditionalStatement &node) override;

        void process(ConditionalLoop &node) override;

        void process(PrintStatement &node) override;

        void process(ReadStatement &node) override;

    private:
        std::ostream &stream;
        int indent = 0;
    };
}


#endif //TOMATO_PRINTER_HPP
