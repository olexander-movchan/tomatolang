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
     * @brief Base class for abstract AST nodes.
     *
     * @note Visitable nodes should derive from VisitableNode.
     */
    class AbstractNode
    {
    public:
        AbstractNode() = default;
        AbstractNode(const CodePoint &location);

        virtual ~AbstractNode() = default;

        CodePoint location;

    protected:
        friend class Visitor;

        virtual void accept(class Visitor &visitor) = 0;
    };


    /**
     * @brief Base class for visitable AST nodes.
     * @tparam NodeType Actual node type.
     * @tparam AbstractBase Abstract node class to inherit from.
     * @note Look for curiously recurring template pattern
     *
     * @code
     * class MyNode : public VisitableNode<MyNode, MyAbstractNode>
     * {
     *     // ...
     * }
     * @endcode
     */
    template<typename NodeType, typename AbstractBase = AbstractNode>
    class VisitableNode : public AbstractBase
    {
    public:
        template <typename ... Args>
        explicit VisitableNode(Args... args) : AbstractBase(args...) {}

    protected:
        void accept(class Visitor& visitor) override;
    };

    /**
     * @brief Abstract base class for AST statement nodes.
     */
    class StatementNode : public AbstractNode {};


    /**
     * @brief List of statements
     */
    class StatementListNode : public VisitableNode<StatementListNode>
    {
    public:
        std::list<std::shared_ptr<StatementNode>> statements;
    };


    /**
     * @brief Abstract base class for AST expression nodes.
     */
    class ExpressionNode : public StatementNode
    {
    public:
        ExpressionNode() = default;
        explicit ExpressionNode(const Token &token);

        Token token;
    };


    /**
     * @brief Literal AST node.
     */
    class LiteralNode : public VisitableNode<LiteralNode, ExpressionNode>
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
    };


    /**
     * @brief Identifier AST node.
     */
    class IdentifierNode : public VisitableNode<IdentifierNode, ExpressionNode>
    {
    public:
        explicit IdentifierNode(const std::string &name);
        explicit IdentifierNode(const Token &token);

        std::string name;
    };


    /**
     * @brief Binary operator AST node.
     */
    class BinaryOperatorNode : public VisitableNode<BinaryOperatorNode, ExpressionNode>
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
    };


    /**
     * @brief Unary operator AST node.
     */
    class UnaryOperatorNode : public VisitableNode<UnaryOperatorNode, ExpressionNode>
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
    };


    /**
     * @brief Assignment AST node.
     */
    class AssignmentNode : public VisitableNode<AssignmentNode, StatementNode>
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
    };


    /**
     * @brief Variable declaration AST node.
     */
    class DeclarationNode : public VisitableNode<DeclarationNode, StatementNode>
    {
    public:
        DeclarationNode(std::shared_ptr<IdentifierNode> variable,
                        std::shared_ptr<ExpressionNode> value);

        std::shared_ptr<IdentifierNode> variable;
        std::shared_ptr<ExpressionNode> value;
    };


    /**
     * @brief Conditional statement.
     *
     * Classical if-then-else statement.
     */
    class ConditionalNode : public VisitableNode<ConditionalNode, StatementNode>
    {
    public:
        ConditionalNode(std::shared_ptr<ExpressionNode>    condition,
                        std::shared_ptr<StatementListNode> consequent,
                        std::shared_ptr<StatementListNode> alternative);

        std::shared_ptr<ExpressionNode>    condition;
        std::shared_ptr<StatementListNode> consequent;
        std::shared_ptr<StatementListNode> alternative;;
    };


    /**
     * @brief Loop with boolean expression condition.
     */
    class LoopNode : public VisitableNode<LoopNode, StatementNode>
    {
    public:
        LoopNode(std::shared_ptr<ExpressionNode>    condition,
                 std::shared_ptr<StatementListNode> statements);

        std::shared_ptr<ExpressionNode>    condition;
        std::shared_ptr<StatementListNode> statements;
    };


    /**
     * @brief Print statement, prints expression value.
     *
     * @warning Class is temporary and will exist until functions have been implemented.
     */
    class PrintNode : public VisitableNode<PrintNode, StatementNode>
    {
    public:
        explicit PrintNode(std::shared_ptr<ExpressionNode> expression);

        std::shared_ptr<ExpressionNode> expression;
    };
}


#include "visitor.hpp"


namespace Tomato::AST
{
    template<typename NodeType, typename AbstractBase>
    void VisitableNode<NodeType, AbstractBase>::accept(class Visitor& visitor)
    {
        visitor.visit(static_cast<NodeType&>(*this));
    }
}


#endif //TOMATO_AST_HPP
