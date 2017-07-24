#ifndef INTERPRETER_INTERPRETER_HPP
#define INTERPRETER_INTERPRETER_HPP


#include "parser.hpp"


class Interpreter : public ASTVisitor
{
public:
    Interpreter(const std::string &code);

    int run();

    void visit(BinaryOperator &ast_node) override;
    void visit(IntegerConstant &ast_node) override;

    void visit(UnaryOperator &un_op) override;

private:
    Parser parser;
    int    last_value;
};


#endif //INTERPRETER_INTERPRETER_HPP
