#ifndef TOMATOLANG_PRINTER_HPP
#define TOMATOLANG_PRINTER_HPP


#include <sstream>

#include "visitor.hpp"


namespace Tomato::AST
{
    class Printer : private Visitor
    {
    public:
        std::string print(AbstractNode &tree);

    private:
        void visit(StatementListNode &node) override;
        void visit(PrintNode &node) override;
        void visit(AssignmentNode &node) override;
        void visit(DeclarationNode &node) override;
        void visit(BinaryOperatorNode &node) override;
        void visit(UnaryOperatorNode &node) override;
        void visit(IdentifierNode &node) override;
        void visit(LiteralNode &node) override;
        void visit(ConditionalNode &node) override;
        void visit(LoopNode &node) override;

    private:
        int indent;
        void print_indent();
        std::stringstream buffer;
    };
}


#endif //TOMATOLANG_PRINTER_HPP
