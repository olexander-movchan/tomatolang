#ifndef TOMATO_VISITOR_HPP
#define TOMATO_VISITOR_HPP


#include "navigator.hpp"


namespace Tomato::AST
{
    /**
     * @brief Abstract class for performing syntax tree traversal.
     */
    class Visitor
    {
    public:
        void visit(class AbstractNode &node);

        virtual void visit(class StatementListNode   &node) = 0;

        virtual void visit(class PrintNode           &node) = 0;
        virtual void visit(class AssignmentNode      &node) = 0;
        virtual void visit(class DeclarationNode     &node) = 0;

        // Expressions
        virtual void visit(class BinaryOperatorNode  &node) = 0;
        virtual void visit(class UnaryOperatorNode   &node) = 0;
        virtual void visit(class IdentifierNode      &node) = 0;
        virtual void visit(class LiteralNode         &node) = 0;

        // Flow-control statements
        virtual void visit(class ConditionalNode     &node) = 0;
        virtual void visit(class LoopNode            &node) = 0;

    protected:
        CodeNavigator navigator;
    };
}


#endif //TOMATO_VISITOR_HPP
