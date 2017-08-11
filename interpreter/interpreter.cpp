#include "interpreter.hpp"
#include "float.hpp"
#include "integer.hpp"
#include "../parser/error.hpp"

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

    switch (ast_node.token.lexeme[0])
    {
        case '+':
            temporary = left->add(*temporary);
            break;

        case '-':
            temporary = left->sub(*temporary);
            break;

        case '*':
            temporary = left->mul(*temporary);
            break;

        case '/':
            temporary = left->div(*temporary);
            break;

        case '^':
            temporary = left->pow(*temporary);
            break;

        default:
            throw SyntaxError("Invalid operator: " + ast_node.token.lexeme);
    }
}


void Interpreter::visit(Literal &node)
{
    if (node.token.lexeme.find('.') != std::string::npos)
    {
        try
        {
            temporary = std::make_shared<Float>(std::stof(node.token.lexeme));
        }
        catch (std::invalid_argument)
        {
            throw SyntaxError("Invalid numerical literal");
        }
    }
    else
    {
        try
        {
            temporary = std::make_shared<Integer>(std::stoi(node.token.lexeme));
        }
        catch (std::invalid_argument)
        {
            throw SyntaxError("Invalid numerical literal");
        }
    }
}


void Interpreter::visit(UnaryOperator &node)
{
    switch (node.token.type)
    {
        case Token::Type::Add:
            Visitor::visit(*node.operand);
            temporary = temporary->un_plus();
            break;

        case Token::Type::Sub:
            Visitor::visit(*node.operand);
            temporary = temporary->un_minus();
            break;

        default:
            throw SyntaxError(node.token);
    }
}


void Interpreter::visit(AST::Program &node)
{
    for (auto &statement : node.statements)
    {
        Visitor::visit(*statement);
    }
}


void Interpreter::visit(AST::Variable &node)
{
    if (memory.find(node.token.lexeme) != memory.end())
        temporary = memory[node.token.lexeme];
    else // TODO: Define interpretation exception.
        throw RuntimeError("Variable used before defined: " + node.token.lexeme);
}


void Interpreter::visit(AST::Assignment &node)
{
    Visitor::visit(*node.expression);

    // TODO: Define interpretation exception.
    if (memory.find(node.variable->token.lexeme) == memory.end())
        throw RuntimeError("Assign to undefined variable: " + node.variable->token.lexeme);

    memory[node.variable->token.lexeme]->assign(*temporary);
}


void Interpreter::visit(AST::Declaration &node)
{
    Visitor::visit(*node.expression);

    // TODO: Define interpretation exception.
    if (memory.find(node.variable->token.lexeme) != memory.end())
        throw RuntimeError("Redeclare variable: " + node.variable->token.lexeme);

    memory[node.variable->token.lexeme] = temporary;
}


void Interpreter::print_state()
{
    std::cout << "var | value" << std::endl;
    std::cout << "-----------" << std::endl;

    for (auto pair : memory)
    {
        std::cout << pair.first << "\t| " << pair.second->str() << std::endl;
    }
}


RuntimeError::RuntimeError(const std::string &message) : std::runtime_error(message.c_str()) {}
