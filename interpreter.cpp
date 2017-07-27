#include "interpreter.hpp"


using namespace AST;


int pow(int base, int exp)
{
    int power = 1;

    for (int i = 0; i < exp; ++i)
    {
        power *= base;
    }

    return power;
}


void Interpreter::run(const std::string &code)
{
    auto parser = Parser(code);
    auto program = parser.parse();

    visit(*program);

    return;
}

void Interpreter::visit(BinaryOperator &ast_node)
{
    Visitor::visit(*ast_node.left);

    int left = temp_value;

    Visitor::visit(*ast_node.right);

    switch (ast_node.token.lexeme[0])
    {
        case '+':
            temp_value = left + temp_value;
            break;

        case '-':
            temp_value = left - temp_value;
            break;

        case '*':
            temp_value = left * temp_value;
            break;

        case '/':
            temp_value = left / temp_value;
            break;

        case '^':
            temp_value = pow(left, temp_value);
            break;

        default:
            throw SyntaxError("Invalid operator: " + ast_node.token.lexeme);
    }
}

void Interpreter::visit(Constant &ast_node)
{
    temp_value = std::atoi(ast_node.token.lexeme.c_str());
}

void Interpreter::visit(UnaryOperator &un_op)
{
    switch (un_op.token.type)
    {
        case TokenType::OperatorPlus:
            Visitor::visit(*un_op.operand);
            break;

        case TokenType::OperatorMinus:
            Visitor::visit(*un_op.operand);
            temp_value = - temp_value;
            break;

        default:
            throw SyntaxError(un_op.token);
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
    if (variables.find(node.token.lexeme) != variables.end())
        temp_value = variables[node.token.lexeme];
    else
        /// @todo Define interpretation exception.
        throw std::runtime_error("Variable used before defined: " + node.token.lexeme);
}

void Interpreter::visit(AST::Assignment &node)
{
    Visitor::visit(*node.expression);

    variables[node.variable->token.lexeme] = temp_value;
}

void Interpreter::print_state()
{
    for (auto pair : variables)
    {
        std::cout << pair.first << '\t' << pair.second << std::endl;
    }
}
