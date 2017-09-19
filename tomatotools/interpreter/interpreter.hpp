#ifndef TOMATO_INTERPRETER_HPP
#define TOMATO_INTERPRETER_HPP


#include <map>

#include "syntax/syntax_tree.hpp"
#include "objects/object.hpp"


namespace Tomato
{
    class InterpretationError : public std::runtime_error
    {
    public:
        InterpretationError(const std::string &message);
    };


    class Interpreter : public AST::Visitor
    {
    public:
        /**
         * @brief Executes commands represented by AST
         */
        void interpret(std::shared_ptr<AST::Node> ast);
        Object::Ref evaluate(AST::ExpressionNode &expression);

    private:
        void visit(AST::StatementListNode   &node) override;

        void visit(AST::DeclarationNode     &node) override;
        void visit(AST::AssignmentNode      &node) override;
        void visit(AST::PrintNode           &node) override;

        void visit(AST::BinaryOperatorNode  &node) override;
        void visit(AST::UnaryOperatorNode   &node) override;
        void visit(AST::IdentifierNode      &node) override;
        void visit(AST::LiteralNode         &node) override;

        void visit(AST::ConditionalNode     &node) override;
        void visit(AST::LoopNode            &node) override;

    private:
        Object::Ref                         temporary;
        std::map<std::string, Object::Ref>  memory;
    };
}


#endif //TOMATO_INTERPRETER_HPP
