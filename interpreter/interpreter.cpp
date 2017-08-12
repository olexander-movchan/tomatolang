#include "interpreter.hpp"
#include "float.hpp"
#include "integer.hpp"
#include "../parser/error.hpp"
#include "bool.hpp"

#include <iostream>


using namespace AST;


void Interpreter::interpret(const std::string &code)
{
    auto syntax_tree = Parser(code).parse();
    visit(*syntax_tree);
}


void Interpreter::visit(BinaryOperator &ast_node)
{
    Visitor::visit(*ast_node.left);

    Object::Ref left = temporary;

    Visitor::visit(*ast_node.right);

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
            throw SyntaxError("Invalid operator");
    }
}


void Interpreter::visit(Literal &node)
{
    switch (node.type)
    {
        case Literal::Type::Integer:
            temporary = std::make_shared<Integer>(node.ivalue());
            break;

        case Literal::Type::Float:
            temporary = std::make_shared<Float>(node.fvalue());
            break;

        case Literal::Type::Bool:
            temporary = std::make_shared<Bool>(node.bvalue());
            break;
    }
}


void Interpreter::visit(UnaryOperator &node)
{
    switch (node.operation)
    {
        case Token::Type::Add:
            Visitor::visit(*node.expression);
            temporary = temporary->un_plus();
            break;

        case Token::Type::Sub:
            Visitor::visit(*node.expression);
            temporary = temporary->un_minus();
            break;

        case Token::Type::Not:
            Visitor::visit(*node.expression);
            temporary = temporary->op_not();
            break;

        default:
            throw SyntaxError("Invalid unary operator");
    }
}


void Interpreter::visit(AST::Program &node)
{
    for (auto &statement : node.statements)
    {
        Visitor::visit(*statement);
    }

    if (node.statements.size() == 1 && temporary != nullptr)
    {
        std::cout << temporary->str() << std::endl;
    }

    temporary = nullptr;
}


void Interpreter::visit(AST::Identifier &node)
{
    if (memory.find(node.name) != memory.end())
        temporary = memory[node.name];
    else
        throw RuntimeError("Undefined variable: " + node.name);
}


void Interpreter::visit(AST::Assignment &node)
{
    Visitor::visit(*node.lvalue);
    auto var = temporary;

    Visitor::visit(*node.rvalue);
    auto value = temporary;

    var->assign(*value);

    temporary = nullptr;
}


void Interpreter::visit(AST::Declaration &node)
{
    Visitor::visit(*node.value);

    // TODO: Define interpretation exception.
    if (memory.find(node.variable->name) != memory.end())
        throw RuntimeError("Redeclare variable: " + node.variable->name);

    memory[node.variable->name] = temporary;

    temporary = nullptr;
}


RuntimeError::RuntimeError(const std::string &message) : std::runtime_error(message.c_str()) {}
