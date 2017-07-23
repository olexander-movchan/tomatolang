#include "parser.hpp"


SyntaxError::SyntaxError(char const *const message) : runtime_error(message) {}

SyntaxError::SyntaxError(std::string message) : runtime_error(message.c_str()) {}


Parser::Parser(const std::string &code) : lexer(code)
{
    current_token = this->lexer.next_token();
}


std::shared_ptr<Expression> Parser::parse()
{
    std::shared_ptr<Expression> expression;

    expression = std::make_shared<IntegerConstant>(current_token);

    eat(TokenType::Integer);

    while (current_token.type == TokenType::OperatorPlus || current_token.type == TokenType::OperatorMinus)
    {
        Token op = current_token;

        eat(op.type);

        Token num = current_token;
        eat(TokenType::Integer);

        std::shared_ptr<Expression> right = std::make_shared<IntegerConstant>(num);

        expression = std::make_shared<BinaryOperator>(expression, op, right);
    }

    eat(TokenType::EndOfFile);

    return expression;
}


void Parser::eat(TokenType expected_type)
{
    if (current_token.type == expected_type)
    {
        current_token = lexer.next_token();
    }
    else
    {
        throw SyntaxError("Unexpected token: " + current_token.lexeme);
    }
}
