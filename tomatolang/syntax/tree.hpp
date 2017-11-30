#ifndef TOMATO_AST_HPP
#define TOMATO_AST_HPP


#include <memory>
#include <list>

#include "token.hpp"
#include "visitor.hpp"


#define ACCEPT_VISITOR protected: void accept(Visitor &visitor) { visitor.visit(*this); }

/**
 * @brief Abstract syntax tree.
 */
namespace Tomato::AST
{
    /**
     * @brief Base class for abstract AST nodes.
     *
     * @note Visitable nodes should derive from VisitableNode.
     */
    class AbstractNode
    {
    public:
        explicit AbstractNode(const CodePoint &location);

        virtual ~AbstractNode() = default;

        CodePoint location;

    protected:
        friend class Visitor;

        virtual void accept(class Visitor &visitor) = 0;
    };


    /**
     * @brief Abstract base class for AST statement nodes.
     */
    class StatementNode : public AbstractNode
    {
    public:
        explicit StatementNode(const CodePoint &location);
    };


    /**
     * @brief List of statements
     */
    class StatementListNode : public StatementNode
    {
    public:
        explicit StatementListNode(const CodePoint &location);
        std::list<std::shared_ptr<StatementNode>> statements;

        ACCEPT_VISITOR
    };


    /**
     * @brief Abstract base class for AST expression nodes.
     */
    class ExpressionNode : public StatementNode
    {
    public:
        explicit ExpressionNode(const Token &token);

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

        explicit LiteralNode(const Token &token);

        Type        type;
        std::string lexeme;

        int    ivalue();
        float  fvalue();
        bool   bvalue();

        ACCEPT_VISITOR
    };


    /**
     * @brief Identifier AST node.
     */
    class IdentifierNode : public ExpressionNode
    {
    public:
        explicit IdentifierNode(const Token &token);

        std::string name;

        ACCEPT_VISITOR
    };


    /**
     * @brief Binary operator AST node.
     */
    class BinaryOperatorNode : public ExpressionNode
    {
    public:
        BinaryOperatorNode(
                std::shared_ptr<ExpressionNode> left,
                const Token                     &token,
                std::shared_ptr<ExpressionNode> right
        );

        std::shared_ptr<ExpressionNode> left;
        Token::Type                     operation;
        std::shared_ptr<ExpressionNode> right;

        ACCEPT_VISITOR
    };


    /**
     * @brief Unary operator AST node.
     */
    class UnaryOperatorNode : public ExpressionNode
    {
    public:
        UnaryOperatorNode(
                const Token                     &token,
                std::shared_ptr<ExpressionNode> expression
        );

        Token::Type                     operation;
        std::shared_ptr<ExpressionNode> expression;

        ACCEPT_VISITOR
    };


    /**
     * @brief Assignment AST node.
     */
    class AssignmentNode : public StatementNode
    {
    public:
        /**
         * @param destination Expression to be changed (i.e. l-value).
         * @param source New value expression.
         */
        AssignmentNode(const CodePoint &location,
                       std::shared_ptr<ExpressionNode> destination,
                       std::shared_ptr<ExpressionNode> source);

        std::shared_ptr<ExpressionNode> destination;
        std::shared_ptr<ExpressionNode> source;

        ACCEPT_VISITOR
    };


    /**
     * @brief Variable declaration AST node.
     */
    class DeclarationNode : public StatementNode
    {
    public:
        DeclarationNode(const CodePoint &location,
                        std::shared_ptr<IdentifierNode> variable,
                        std::shared_ptr<ExpressionNode> initializer);

        std::shared_ptr<IdentifierNode> variable;
        std::shared_ptr<ExpressionNode> initializer;

        ACCEPT_VISITOR
    };


    /**
     * @brief Conditional 'if-then-else' statement.
     */
    class ConditionalNode : public StatementNode
    {
    public:
        ConditionalNode(const CodePoint &location,
                        std::shared_ptr<ExpressionNode>    condition,
                        std::shared_ptr<StatementListNode> consequent,
                        std::shared_ptr<StatementListNode> alternative);

        std::shared_ptr<ExpressionNode>    condition;
        std::shared_ptr<StatementListNode> consequent;
        std::shared_ptr<StatementListNode> alternative;

        ACCEPT_VISITOR
    };


    /**
     * @brief Loop with boolean expression condition.
     */
    class LoopNode : public StatementNode
    {
    public:
        LoopNode(const CodePoint &location,
                 std::shared_ptr<ExpressionNode>    condition,
                 std::shared_ptr<StatementListNode> statements);

        std::shared_ptr<ExpressionNode>    condition;
        std::shared_ptr<StatementListNode> statements;

        ACCEPT_VISITOR
    };


    /**
     * @brief Print statement, prints expression value.
     *
     * @warning Class is temporary and will exist until functions have been implemented.
     */
    class PrintNode : public StatementNode
    {
    public:
        PrintNode(const CodePoint &location, std::shared_ptr<ExpressionNode> expression);

        std::shared_ptr<ExpressionNode> expression;

        ACCEPT_VISITOR
    };
}


#endif //TOMATO_AST_HPP
