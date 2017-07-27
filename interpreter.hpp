#ifndef INTERPRETER_INTERPRETER_HPP
#define INTERPRETER_INTERPRETER_HPP


#include "parser.hpp"


class Interpreter : public AST::Visitor
{
public:
    void run(const std::string &code);
    void print_state();

    void visit(AST::Program         &node) override;
    void visit(AST::UnaryOperator   &node) override;
    void visit(AST::BinaryOperator  &node) override;
    void visit(AST::Variable        &node) override;
    void visit(AST::Constant        &node) override;
    void visit(AST::Assignment      &node) override;
    void visit(AST::Declaration     &node) override;

private:
    int    temp_value;

    std::map<std::string, int> variables;
};


#endif //INTERPRETER_INTERPRETER_HPP
