#ifndef INTERPRETER_INTERPRETER_HPP
#define INTERPRETER_INTERPRETER_HPP


#include "parser.hpp"
#include "types.hpp"


class RuntimeError : std::runtime_error
{
public:
    RuntimeError(const std::string &message);
};


/**
 * @brief Interpreter executes
 */
class Interpreter : public AST::Visitor
{
public:
    /**
     * @brief Creates interpreter
     * @param tree AST built by parser
     */
    Interpreter(std::shared_ptr<AST::AbstractSyntaxTree>  tree);

    /**
     * @brief Executes commands represented by AST
     */
    void run();

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
    Object::Ref                               temporary;
    std::map<std::string, Object::Ref>        memory;
    std::shared_ptr<AST::AbstractSyntaxTree>  syntax_tree;
};


#endif //INTERPRETER_INTERPRETER_HPP
