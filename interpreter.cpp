#include "interpreter.hpp"


int pow(int base, int exp)
{
    int power = 1;

    for (int i = 0; i < exp; ++i)
    {
        power *= base;
    }

    return power;
}


Interpreter::Interpreter(const std::string &code) : parser(code) {}


int Interpreter::run()
{
    auto expr = parser.parse();

    ASTVisitor::visit(*expr);

    return last_value;
}

void Interpreter::visit(BinaryOperator &ast_node)
{
    ASTVisitor::visit(*ast_node.left);

    int left = last_value;

    ASTVisitor::visit(*ast_node.right);

    switch (ast_node.token.lexeme[0])
    {
        case '+':
            last_value = left + last_value;
            break;

        case '-':
            last_value = left - last_value;
            break;

        case '*':
            last_value = left * last_value;
            break;

        case '/':
            last_value = left / last_value;
            break;

        case '^':
            last_value = pow(left, last_value);
            break;

        default:
            throw SyntaxError("Invalid operator: " + ast_node.token.lexeme);
    }
}

void Interpreter::visit(IntegerConstant &ast_node)
{
    last_value = std::atoi(ast_node.token.lexeme.c_str());
}