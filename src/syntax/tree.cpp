#include "tree.hpp"


using namespace Tomato;
using namespace Tomato::AST;


AbstractNode::AbstractNode          (const CodePoint &location) : location(location) {}
StatementNode::StatementNode        (const CodePoint &location) : AbstractNode(location) {}
StatementListNode::StatementListNode(const CodePoint &location) : StatementNode(location) {}

ExpressionNode::ExpressionNode      (const Token &token) : StatementNode(token.location), token(token) {}
IdentifierNode::IdentifierNode      (const Token &token) : ExpressionNode(token), name(token.lexeme) {}

LiteralNode::LiteralNode            (const Token &token) : ExpressionNode(token), lexeme(token.lexeme)
{
    if (lexeme == "true" || lexeme == "false")
        type = Type ::Bool;

    else if (lexeme.find('.') == lexeme.npos)
        type = Type::Integer;

    else
        type = Type::Float;
}


BinaryOperatorNode::BinaryOperatorNode(
        std::shared_ptr<ExpressionNode>  left,
        const Token                      &token,
        std::shared_ptr<ExpressionNode>  right
) : ExpressionNode(token), left(left), operation(token.type), right(right) {}


UnaryOperatorNode::UnaryOperatorNode(
        const Token                      &token,
        std::shared_ptr<ExpressionNode>  expression
) : ExpressionNode(token), operation(operation), expression(expression) {}


int   LiteralNode::ivalue() { return std::stoi(lexeme); }
float LiteralNode::fvalue() { return std::stof(lexeme); }
bool  LiteralNode::bvalue() { return lexeme == "true"; }


AssignmentNode::AssignmentNode(const CodePoint &location,
                               std::shared_ptr<ExpressionNode> destination,
                               std::shared_ptr<ExpressionNode> source)
        : StatementNode(location), destination(destination), source(source) {}


DeclarationNode::DeclarationNode(const CodePoint &location,
                                 std::shared_ptr<IdentifierNode> variable,
                                 std::shared_ptr<ExpressionNode> initializer)
        : StatementNode(location), variable(variable), initializer(initializer) {}


ConditionalNode::ConditionalNode(const CodePoint &location,
                                 std::shared_ptr<ExpressionNode> condition,
                                 std::shared_ptr<StatementListNode> consequent,
                                 std::shared_ptr<StatementListNode> alternative)
        : StatementNode(location), condition(condition), consequent(consequent), alternative(alternative) {}


LoopNode::LoopNode(const CodePoint &location,
                   std::shared_ptr<ExpressionNode> condition,
                   std::shared_ptr<StatementListNode> statements)
        : StatementNode(location), condition(condition), statements(statements) {}


PrintNode::PrintNode(const CodePoint &location,
                     std::shared_ptr<ExpressionNode> expression)
        : StatementNode(location), expression(expression) {}
