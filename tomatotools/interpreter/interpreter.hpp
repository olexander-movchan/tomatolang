#ifndef TOMATO_INTERPRETER_HPP
#define TOMATO_INTERPRETER_HPP


#include <map>

#include "syntax/visitor.hpp"
#include "types/object.hpp"


namespace Tomato
{
    class InterpretationError : public std::runtime_error
    {
    public:
        explicit InterpretationError(const std::string &message);
    };


    class Interpreter : public AST::Visitor
    {
    public:
        explicit Interpreter(std::ostream &out);

        void interpret(const std::string &code);
        void interpret(std::shared_ptr<AST::AbstractNode> ast);

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
        Object::Ref     temporary;
        std::ostream    &out;

        std::map<std::string, Object::Ref>  memory;
    };
}


#endif //TOMATO_INTERPRETER_HPP
