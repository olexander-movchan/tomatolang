#include "syntax_tree.hpp"


using namespace Tomato;
using namespace Tomato::AST;


ExpressionNode::ExpressionNode(const Token &token) : token(token) {}


IdentifierNode::IdentifierNode(const Token &token) : IdentifierNode(token.lexeme)
{
    this->token = token;
}


IdentifierNode::IdentifierNode(const std::string &name) : name(name) {}


BinaryOperatorNode::BinaryOperatorNode(
        std::shared_ptr<ExpressionNode>  left,
        Token::Type                      operation,
        std::shared_ptr<ExpressionNode>  right
) : left(left), operation(operation), right(right) {}


BinaryOperatorNode::BinaryOperatorNode(
        std::shared_ptr<ExpressionNode>  left,
        const Token                      &token,
        std::shared_ptr<ExpressionNode>  right
) : BinaryOperatorNode(left, token.type, right)
{
    this->token = token;
}


UnaryOperatorNode::UnaryOperatorNode(
        Token::Type                      operation,
        std::shared_ptr<ExpressionNode>  expression
) : operation(operation), expression(expression) {}


UnaryOperatorNode::UnaryOperatorNode(
        const Token                      &token,
        std::shared_ptr<ExpressionNode>  expression
) : UnaryOperatorNode(token.type, expression)
{
    this->token = token;
}


AssignmentNode::AssignmentNode(
        std::shared_ptr<ExpressionNode> lvalue,
        std::shared_ptr<ExpressionNode> rvalue
) : lvalue(lvalue), rvalue(rvalue) {}


DeclarationNode::DeclarationNode(
        std::shared_ptr<IdentifierNode> variable,
        std::shared_ptr<ExpressionNode> value
) : variable(variable), value(value) {}


ConditionalNode::ConditionalNode(
        std::shared_ptr<ExpressionNode>     condition,
        std::shared_ptr<StatementListNode>  consequent,
        std::shared_ptr<StatementListNode>  alternative
) : condition(condition), consequent(consequent), alternative(alternative) {}


LoopNode::LoopNode(
        std::shared_ptr<ExpressionNode>     condition,
        std::shared_ptr<StatementListNode>  statements
) : condition(condition), statements(statements) {}


PrintNode::PrintNode(
        std::shared_ptr<ExpressionNode> expression
) : expression(expression) {}



LiteralNode::LiteralNode(const Token &token) : LiteralNode(token.lexeme)
{
    this->token = token;
}


LiteralNode::LiteralNode(const std::string &lexeme) : lexeme(lexeme)
{
    if (lexeme == "true" || lexeme == "false")
        type = Type ::Bool;

    else if (lexeme.find('.') == lexeme.npos)
        type = Type::Integer;

    else
        type = Type::Float;
}


int   LiteralNode::ivalue() { return std::stoi(lexeme); }
float LiteralNode::fvalue() { return std::stof(lexeme); }
bool  LiteralNode::bvalue() { return lexeme == "true"; }


// Visitor-related methods

CodePoint Visitor::Pointer;
void Visitor::visit(Node &node)
{
    CodePoint tmp = Pointer;

    Pointer = node.location;
    node.accept(*this);
    Pointer = tmp;
}

void StatementListNode   ::accept(Visitor &visitor) { visitor.visit(*this); }

void PrintNode           ::accept(Visitor &visitor) { visitor.visit(*this); }
void AssignmentNode      ::accept(Visitor &visitor) { visitor.visit(*this); }
void DeclarationNode     ::accept(Visitor &visitor) { visitor.visit(*this); }

void BinaryOperatorNode  ::accept(Visitor &visitor) { visitor.visit(*this); }
void UnaryOperatorNode   ::accept(Visitor &visitor) { visitor.visit(*this); }
void IdentifierNode      ::accept(Visitor &visitor) { visitor.visit(*this); }
void LiteralNode         ::accept(Visitor &visitor) { visitor.visit(*this); }

void ConditionalNode     ::accept(Visitor &visitor) { visitor.visit(*this); }
void LoopNode            ::accept(Visitor &visitor) { visitor.visit(*this); }
