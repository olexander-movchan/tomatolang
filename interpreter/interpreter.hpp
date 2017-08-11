#ifndef INTERPRETER_INTERPRETER_HPP
#define INTERPRETER_INTERPRETER_HPP


#include "../parser/parser.hpp"
#include "object.hpp"


class RuntimeError : public std::runtime_error
{
public:
    RuntimeError(const std::string &message);
};


class Interpreter : public AST::Visitor
{
public:
    /**
     * @brief Executes commands represented by AST
     */
    void interpret(const std::string &code);

    /**
     * @brief Prints interpreter state (i.e. all variable's values)
     */
    void print_state();

private:
    void visit(AST::Program         &node) override;
    void visit(AST::UnaryOperator   &node) override;
    void visit(AST::BinaryOperator  &node) override;
    void visit(AST::Variable        &node) override;
    void visit(AST::Literal         &node) override;
    void visit(AST::Assignment      &node) override;
    void visit(AST::Declaration     &node) override;

private:
    Object::Ref                         temporary;
    std::map<std::string, Object::Ref>  memory;
};


#endif //INTERPRETER_INTERPRETER_HPP
