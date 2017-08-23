#ifndef INTERPRETER_INTERPRETER_HPP
#define INTERPRETER_INTERPRETER_HPP


#include <map>

#include "parser/syntax_tree.hpp"
#include "objects/object.hpp"


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
    void interpret(std::shared_ptr<AST::AbstractSyntaxTree> ast);

private:
    void visit(AST::Program         &node) override;
    void visit(AST::UnaryOperator   &node) override;
    void visit(AST::BinaryOperator  &node) override;
    void visit(AST::Identifier      &node) override;
    void visit(AST::Literal         &node) override;
    void visit(AST::Assignment      &node) override;
    void visit(AST::Declaration     &node) override;

private:
    Object::Ref                         temporary;
    std::map<std::string, Object::Ref>  memory;
};


#endif //INTERPRETER_INTERPRETER_HPP
