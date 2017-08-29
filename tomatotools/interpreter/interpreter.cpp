#include "interpreter.hpp"

#include "objects/types.hpp"

#include <iostream>


using namespace Tomato;


void Interpreter::interpret(std::shared_ptr<AST::Node> ast)
{
    AST::Visitor::visit(*ast);
}


void Interpreter::visit(AST::BinaryOperatorNode &ast_node)
{
    AST::Visitor::visit(*ast_node.left);

    Object::Ref left = temporary;

    AST::Visitor::visit(*ast_node.right);

    switch (ast_node.operation)
    {
        case Token::Type::Add: temporary = left->add(*temporary); break;
        case Token::Type::Sub: temporary = left->sub(*temporary); break;
        case Token::Type::Mul: temporary = left->mul(*temporary); break;
        case Token::Type::Div: temporary = left->div(*temporary); break;
        case Token::Type::Exp: temporary = left->exp(*temporary); break;

        case Token::Type::And: temporary = left->op_and(*temporary); break;
        case Token::Type::Or : temporary = left->op_or (*temporary); break;

        case Token::Type::LT: temporary = left->lt(*temporary); break;
        case Token::Type::GT: temporary = left->gt(*temporary); break;
        case Token::Type::LE: temporary = left->le(*temporary); break;
        case Token::Type::GE: temporary = left->ge(*temporary); break;
        case Token::Type::EQ: temporary = left->eq(*temporary); break;
        case Token::Type::NE: temporary = left->ne(*temporary); break;

        default:
            throw std::runtime_error("Parsing or interpretation error.");
    }
}


void Interpreter::visit(AST::LiteralNode &node)
{
    switch (node.type)
    {
        case AST::LiteralNode::Type::Integer:
            temporary = std::make_shared<Integer>(node.ivalue());
            break;

        case AST::LiteralNode::Type::Float:
            temporary = std::make_shared<Float>(node.fvalue());
            break;

        case AST::LiteralNode::Type::Bool:
            temporary = std::make_shared<Bool>(node.bvalue());
            break;
    }
}


void Interpreter::visit(AST::UnaryOperatorNode &node)
{
    switch (node.operation)
    {
        case Token::Type::Add:
            AST::Visitor::visit(*node.expression);
            temporary = temporary->un_plus();
            break;

        case Token::Type::Sub:
            AST::Visitor::visit(*node.expression);
            temporary = temporary->un_minus();
            break;

        case Token::Type::Not:
            AST::Visitor::visit(*node.expression);
            temporary = temporary->op_not();
            break;

        default:
            throw std::runtime_error("Parsing or interpretation error.");
    }
}


void Interpreter::visit(AST::StatementListNode &node)
{
    for (auto &statement : node.statements)
    {
        AST::Visitor::visit(*statement);
    }
}


void Interpreter::visit(AST::IdentifierNode &node)
{
    if (memory.find(node.name) != memory.end())
        temporary = memory[node.name];
    else
        throw InterpretationError("Undefined variable: " + node.name);
}


void Interpreter::visit(AST::AssignmentNode &node)
{
    AST::Visitor::visit(*node.lvalue);
    auto var = temporary;

    AST::Visitor::visit(*node.rvalue);
    auto value = temporary;

    var->assign(*value);
}


void Interpreter::visit(AST::DeclarationNode &node)
{
    AST::Visitor::visit(*node.value);

    // TODO: Define interpretation exception.
    if (memory.find(node.variable->name) != memory.end())
        throw InterpretationError("Redeclare variable: " + node.variable->name);

    memory[node.variable->name] = temporary;
}


void Interpreter::visit(AST::PrintNode &node)
{
    AST::Visitor::visit(*node.expression);

    std::cout << temporary->str() << std::endl;
}


void Interpreter::visit(AST::ConditionalNode &node)
{
    AST::Visitor::visit(*node.condition);

    if (temporary->as<Bool>().value)
    {
        visit(*node.consequent);
    }
    else if (node.alternative != nullptr)
    {
        visit(*node.alternative);
    }
}


void Interpreter::visit(AST::LoopNode &node)
{
    AST::Visitor::visit(*node.condition);

    while (temporary->as<Bool>().value)
    {
        visit(*node.statements);
        AST::Visitor::visit(*node.condition);
    }
}


InterpretationError::InterpretationError(const std::string &message) : std::runtime_error(message.c_str()) {}
