#ifndef INTERPRETER_SYNTAX_TREE_HPP
#define INTERPRETER_SYNTAX_TREE_HPP


#include <memory>

#include "lexer.hpp"


class AbstractSyntaxTree
{
public:
    AbstractSyntaxTree(const Token &token);

    Token token;

protected:
    friend class ASTVisitor;
    virtual void accept(class ASTVisitor &visitor) = 0;
};


class Expression : public AbstractSyntaxTree
{
public:
    Expression(const Token &token);
};


class IntegerConstant : public Expression
{
public:
    IntegerConstant(const Token &token);

protected:
    void accept(ASTVisitor &visitor) override;
};


class BinaryOperator : public Expression
{
public:
    BinaryOperator(std::shared_ptr<Expression> left,
                   const Token &token,
                   std::shared_ptr<Expression> right);

    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

protected:
    void accept(ASTVisitor &visitor) override;
};


class UnaryOperator : public Expression
{
public:
    UnaryOperator(const Token &token, std::shared_ptr<Expression> expr);

    std::shared_ptr<Expression> operand;

    void accept(ASTVisitor &visitor) override;
};


/**
 * @brief Visitor pattern for AbstractSyntaxTree.
 */
class ASTVisitor
{
public:
    /**
     * @brief Abstract visit method
     * @param ast_node
     */
    void visit(AbstractSyntaxTree &ast_node);

    virtual void visit(BinaryOperator  &bin_op) = 0;
    virtual void visit(IntegerConstant &constant) = 0;
    virtual void visit(UnaryOperator   &un_op) = 0;
};


#endif //INTERPRETER_SYNTAX_TREE_HPP
