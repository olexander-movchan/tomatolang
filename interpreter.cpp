#include "interpreter.hpp"
#include "parser.hpp"


Interpreter::Interpreter(const std::string &code) : lexer(code)
{
    current_token = this->lexer.next_token();
}


int Interpreter::run()
{
    Token left = current_token;
    eat(TokenType::Integer);

    int result = std::atoi(left.lexeme.c_str());

    while (current_token.type == TokenType::OperatorPlus)
    {
        eat(TokenType::OperatorPlus);

        Token right = current_token;

        eat(TokenType::Integer);

        result += std::atoi(right.lexeme.c_str());
    }

    return result;
}


void Interpreter::eat(TokenType expected_type)
{
    if (current_token.type == expected_type)
    {
        current_token = lexer.next_token();
    }
    else
    {
        throw SyntaxError("Unexpected token");
    }
}
