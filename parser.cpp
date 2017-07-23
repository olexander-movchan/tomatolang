#include "parser.hpp"


SyntaxError::SyntaxError(char const *const message) : runtime_error(message) {}

SyntaxError::SyntaxError(std::string message) : runtime_error(message.c_str()) {}


Parser::Parser(const std::string &code) : lexer(code)
{
    current_token = this->lexer.next_token();
}


std::shared_ptr<Expression> Parser::parse()
{
    auto expr = expression();
    eat(TokenType::EndOfFile);
    return expr;
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

std::shared_ptr<Expression> Parser::expression()
{
    return sum();
}

std::shared_ptr<Expression> Parser::sum()
{
    auto sum = product();

    while (current_token.type == TokenType::OperatorPlus ||
           current_token.type == TokenType::OperatorMinus)
    {
        auto op = current_token;
        eat(current_token.type);

        auto right = product();

        sum = std::make_shared<BinaryOperator>(sum, op, right);
    }

    return sum;
}

std::shared_ptr<Expression> Parser::product()
{
    auto prod = power();

    while (current_token.type == TokenType::OperatorMul ||
           current_token.type == TokenType::OperatorDiv)
    {
        auto op = current_token;
        eat(current_token.type);

        auto right = power();

        prod = std::make_shared<BinaryOperator>(prod, op, right);
    }

    return prod;
}

std::shared_ptr<Expression> Parser::power()
{
    auto base = factor();

    if (current_token.type == TokenType::OperatorPow)
    {
        auto pow = current_token;
        eat(TokenType::OperatorPow);

        auto exponent = power();

        return std::make_shared<BinaryOperator>(base, pow, exponent);
    }

    return base;
}

std::shared_ptr<Expression> Parser::factor()
{
    switch (current_token.type)
    {
        case TokenType::LeftParen:
        {
            eat(TokenType::LeftParen);
            auto factor = expression();
            eat(TokenType::RightParen);

            return factor;
        }

        case TokenType::Integer:
        {
            auto factor = std::make_shared<IntegerConstant>(current_token);
            eat(TokenType::Integer);
            return factor;
        }

        default:
            throw SyntaxError("Unexpected token: " + current_token.lexeme);
    }
}
