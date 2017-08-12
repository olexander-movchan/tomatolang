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
     * @brief Abstract base class for AST statement nodes.
     */
    class Statement : public AbstractSyntaxTree {};


    /**
     * @brief Abstract base class for AST expression nodes.
     */
    class Expression : public Statement {};


    /**
     * @brief Integer constant AST node.
     */
    class Literal : public Expression
    {
    public:
        enum class Type
        {
            Integer, Float,
        };

        Literal(const std::string &lexeme);

        Type        type;
        std::string lexeme;

        int    ivalue();
        float  fvalue();

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Identifier AST node.
     */
    class Identifier : public Expression
    {
    public:
        Identifier(const std::string &name);

        std::string name;

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
         * @param left       Expression to the left of operator
         * @param operation  Operator type
         * @param right      Expression to the right of operator
         */
        BinaryOperator(std::shared_ptr<Expression> left,
                       Token::Type                 operation,
                       std::shared_ptr<Expression> right);

        std::shared_ptr<Expression> left;
        Token::Type                 operation;
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
         * @param operation  Operator type
         * @param expression Operand
         */
        UnaryOperator(Token::Type operation, std::shared_ptr<Expression> expression);

        Token::Type                 operation;
        std::shared_ptr<Expression> expression;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Assignment AST node.
     */
    class Assignment : public Statement
    {
    public:
        /**
         * @param lvalue Reference to update value (i.e. Variable)
         * @param rvalue Value that should be assigned
         */
        Assignment(std::shared_ptr<Expression> lvalue,
                   std::shared_ptr<Expression> rvalue);

        std::shared_ptr<Expression> lvalue;
        std::shared_ptr<Expression> rvalue;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Variable declaration AST node.
     */
    class Declaration : public Statement
    {
    public:
        Declaration(std::shared_ptr<Identifier>   variable,
                    std::shared_ptr<Expression> value);

        std::shared_ptr<Identifier>    variable;
        std::shared_ptr<Expression>  value;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Program AST node, i.e. tree root.
     */
    class Program : public AbstractSyntaxTree
    {
    public:
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
        virtual void visit(Identifier      &node) = 0;
        virtual void visit(Literal         &node) = 0;
        virtual void visit(Assignment      &node) = 0;
        virtual void visit(Declaration     &node) = 0;
    };
}


#endif //INTERPRETER_SYNTAX_TREE_HPP
