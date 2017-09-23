#ifndef TOMATO_VISITOR_HPP
#define TOMATO_VISITOR_HPP


#include "codepoint.hpp"
#include "syntax_tree.hpp"
#include "navigator.hpp"


namespace Tomato::AST
{
    /**
     * @brief Abstract class for performing syntax tree traversal.
     */
    class Visitor
    {
    public:
        void visit(AbstractNode &node)
        {
            navigator.push(node.location);

            node.accept(*this);

            navigator.pop();
        }

        virtual void visit(StatementListNode   &node) = 0;

        virtual void visit(PrintNode           &node) = 0;
        virtual void visit(AssignmentNode      &node) = 0;
        virtual void visit(DeclarationNode     &node) = 0;

        // Expressions
        virtual void visit(BinaryOperatorNode  &node) = 0;
        virtual void visit(UnaryOperatorNode   &node) = 0;
        virtual void visit(IdentifierNode      &node) = 0;
        virtual void visit(LiteralNode         &node) = 0;

        // Flow-control statements
        virtual void visit(ConditionalNode     &node) = 0;
        virtual void visit(LoopNode            &node) = 0;

    protected:
        CodeNavigator navigator;
    };
}


#endif //TOMATO_VISITOR_HPP
