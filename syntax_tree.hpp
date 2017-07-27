#ifndef INTERPRETER_SYNTAX_TREE_HPP
#define INTERPRETER_SYNTAX_TREE_HPP


#include <memory>
#include <queue>

#include "lexer.hpp"


/**
 * @brief Abstract syntax tree.
 */
namespace AST
{
    /**
     * @brief Abstract base class for all AST nodes.
     */
    class AbstractSyntaxTree
    {
    public:
        /**
         * @param token Token that corresponds to AST node.
         */
        AbstractSyntaxTree(const Token &token);

        Token token;

    protected:
        friend class Visitor;

        /**
         * @brief Virtual method provides double dispatch (see visitor design pattern).
         *
         * @param visitor Visitor instance
         */
        virtual void accept(class Visitor &visitor) = 0;
    };


    /**
     * @brief Abstract base class for AST expression nodes.
     */
    class Expression : public AbstractSyntaxTree
    {
    public:
        Expression(const Token &token);
    };


    /**
     * @brief Integer constant AST node.
     */
    class Constant : public Expression
    {
    public:
        Constant(const Token &token);

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Variable AST node.
     */
    class Variable : public Expression
    {
    public:
        Variable(const Token &token);

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Binary operator AST node.
     */
    class BinaryOperator : public Expression
    {
    public:
        /**
         * @param left   Expression to the left of operator
         * @param token  Operator token
         * @param right  Expression to the right of operator
         */
        BinaryOperator(std::shared_ptr<Expression> left,
                       const Token &token,
                       std::shared_ptr<Expression> right);

        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Unary operator AST node.
     */
    class UnaryOperator : public Expression
    {
    public:
        /**
         * @param token  Operator token
         * @param expr   Operand expression
         */
        UnaryOperator(const Token &token, std::shared_ptr<Expression> expr);

        std::shared_ptr<Expression> operand;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Abstract base class for AST statement nodes.
     */
    class Statement : public AbstractSyntaxTree
    {
    public:
        Statement(const Token &token);
    };


    /**
     * @brief Assignment AST node.
     */
    class Assignment : public Statement
    {
    public:
        Assignment(std::shared_ptr<Variable> variable,
                   Token token,
                   std::shared_ptr<Expression> expression);

        std::shared_ptr<Variable>    variable;
        std::shared_ptr<Expression>  expression;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Program AST node, i.e. tree root.
     *
     * @note Doesn't have corresponding token.
     */
    class Program : public AbstractSyntaxTree
    {
    public:
        Program(const Token &token = Token());

        std::vector<std::shared_ptr<Statement>> statements;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Abstract AST node visitor.
     *
     * Visitor design pattern:
     * Visitor's primary purpose is to abstract functionality that can be
     * applied to an aggregate hierarchy of "element" objects. The approach
     * encourages designing lightweight Element classes - because processing
     * functionality is removed from their list of responsibilities.
     * New functionality can easily be added to the original inheritance
     * hierarchy by creating a new Visitor subclass.
     */
    class Visitor
    {
    public:
        void visit(AbstractSyntaxTree &node);

        virtual void visit(Program         &node) = 0;
        virtual void visit(UnaryOperator   &node) = 0;
        virtual void visit(BinaryOperator  &node) = 0;
        virtual void visit(Variable        &node) = 0;
        virtual void visit(Constant        &node) = 0;
        virtual void visit(Assignment      &node) = 0;
    };
}


#endif //INTERPRETER_SYNTAX_TREE_HPP
