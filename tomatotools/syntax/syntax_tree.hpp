#ifndef TOMATO_AST_HPP
#define TOMATO_AST_HPP


#include <memory>
#include <list>
#include "token.hpp"


/**
 * @brief Abstract syntax tree.
 */
namespace Tomato::AST
{
    /**
     * @brief Abstract base class for all AST nodes.
     *
     * @note AST users should implement visitor pattern.
     */
    class Node
    {
    public:
        Node() {}
        Node(const CodePoint &location);

        virtual ~Node() = default;

        CodePoint location;

    protected:
        friend class Visitor;

        /**
         * @brief Provides double dispatch (see visitor design pattern).
         * @param visitor Visitor instance
         *
         * Every non-abstract Node subclass should define accept method as follows:
         * @code{.cpp}
         * void accept(Visitor &visitor) { visitor.visit(*this); }
         * @endcode
         */
        virtual void accept(class Visitor &visitor) = 0;
    };


    /**
     * @brief Abstract base class for AST statement nodes.
     */
    class StatementNode : public Node {};


    /**
     * @brief List of statements
     */
    class StatementListNode : public Node
    {
    public:
        std::list<std::shared_ptr<StatementNode>> statements;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Abstract base class for AST expression nodes.
     */
    class ExpressionNode : public StatementNode
    {
    public:
        ExpressionNode() = default;
        ExpressionNode(const Token &token);

        Token token;
    };


    /**
     * @brief Literal AST node.
     */
    class LiteralNode : public ExpressionNode
    {
    public:
        enum class Type
        {
            Integer, Float, Bool,
        };

        LiteralNode(const std::string &lexeme);
        LiteralNode(const Token &token);

        Type        type;
        std::string lexeme;

        int    ivalue();
        float  fvalue();
        bool   bvalue();

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Identifier AST node.
     */
    class IdentifierNode : public ExpressionNode
    {
    public:
        IdentifierNode(const std::string &name);
        IdentifierNode(const Token &token);

        std::string name;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Binary operator AST node.
     */
    class BinaryOperatorNode : public ExpressionNode
    {
    public:
        BinaryOperatorNode(
                std::shared_ptr<ExpressionNode> left,
                Token::Type                     operation,
                std::shared_ptr<ExpressionNode> right
        );

        BinaryOperatorNode(
                std::shared_ptr<ExpressionNode> left,
                const Token                     &token,
                std::shared_ptr<ExpressionNode> right
        );

        std::shared_ptr<ExpressionNode> left;
        Token::Type                     operation;
        std::shared_ptr<ExpressionNode> right;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Unary operator AST node.
     */
    class UnaryOperatorNode : public ExpressionNode
    {
    public:
        UnaryOperatorNode(
                Token::Type                     operation,
                std::shared_ptr<ExpressionNode> expression
        );

        UnaryOperatorNode(
                const Token                     &token,
                std::shared_ptr<ExpressionNode> expression
        );

        Token::Type                     operation;
        std::shared_ptr<ExpressionNode> expression;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Assignment AST node.
     */
    class AssignmentNode : public StatementNode
    {
    public:
        /**
         * @param lvalue  Reference to update value (i.e. Variable)
         * @param rvalue  Value that should be assigned
         */
        AssignmentNode(std::shared_ptr<ExpressionNode> lvalue,
                       std::shared_ptr<ExpressionNode> rvalue);

        std::shared_ptr<ExpressionNode> lvalue;
        std::shared_ptr<ExpressionNode> rvalue;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Variable declaration AST node.
     */
    class DeclarationNode : public StatementNode
    {
    public:
        DeclarationNode(std::shared_ptr<IdentifierNode> variable,
                        std::shared_ptr<ExpressionNode> value);

        std::shared_ptr<IdentifierNode> variable;
        std::shared_ptr<ExpressionNode> value;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Conditional statement.
     *
     * Classical if-then-else statement.
     */
    class ConditionalNode : public StatementNode
    {
    public:
        ConditionalNode(std::shared_ptr<ExpressionNode>    condition,
                        std::shared_ptr<StatementListNode> consequent,
                        std::shared_ptr<StatementListNode> alternative);

        std::shared_ptr<ExpressionNode>    condition;
        std::shared_ptr<StatementListNode> consequent;
        std::shared_ptr<StatementListNode> alternative;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Loop with boolean expression condition.
     */
    class LoopNode : public StatementNode
    {
    public:
        LoopNode(std::shared_ptr<ExpressionNode>    condition,
                 std::shared_ptr<StatementListNode> statements);

        std::shared_ptr<ExpressionNode>    condition;
        std::shared_ptr<StatementListNode> statements;

    protected:
        void accept(Visitor &visitor) override;
    };


    /**
     * @brief Print statement, prints expression value.
     *
     * @warning Class is temporary and will exist until functions have been implemented.
     */
    class PrintNode : public StatementNode
    {
    public:
        PrintNode(std::shared_ptr<ExpressionNode> expression);

        std::shared_ptr<ExpressionNode> expression;

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
        void visit(Node &node);

        virtual void visit(StatementListNode   &node) = 0;

        virtual void visit(PrintNode           &node) = 0;
        virtual void visit(AssignmentNode      &node) = 0;
        virtual void visit(DeclarationNode     &node) = 0;

        // Expressions
        virtual void visit(BinaryOperatorNode  &node) = 0;
        virtual void visit(UnaryOperatorNode   &node) = 0;
        virtual void visit(IdentifierNode      &node) = 0;
        virtual void visit(LiteralNode         &node) = 0;

        // Flow-control statements
        virtual void visit(ConditionalNode     &node) = 0;
        virtual void visit(LoopNode            &node) = 0;

        static CodePoint Pointer;
    };
}


#endif //TOMATO_AST_HPP
