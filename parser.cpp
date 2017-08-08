#include "parser.hpp"


using namespace AST;


SyntaxError::SyntaxError(std::string message) : runtime_error(message.c_str()) {}
SyntaxError::SyntaxError(const Token &token)  : runtime_error("Unexpected token: " + (std::string)token) {}


Parser::Parser(const std::string &code) : lexer(code)
{
    current_token = this->lexer.next_token();
}


std::shared_ptr<Program> Parser::parse()
{
    auto program = std::make_shared<Program>();

    while (current_token.type != TokenType::EndOfFile)
    {
        program->statements.push_back(statement());
    }

    return program;
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

    while (current_token.type == TokenType::Add ||
           current_token.type == TokenType::Sub)
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

    while (current_token.type == TokenType::Mul ||
           current_token.type == TokenType::Div)
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

    if (current_token.type == TokenType::Pow)
    {
        auto pow = current_token;
        eat(TokenType::Pow);

        auto exponent = power();

        return std::make_shared<BinaryOperator>(base, pow, exponent);
    }

    return base;
}

std::shared_ptr<Expression> Parser::factor()
{
    switch (current_token.type)
    {
        case TokenType::Add:
        {
            Token plus = current_token;
            eat(TokenType::Add);

            return std::make_shared<UnaryOperator>(plus, factor());
        }

        case TokenType::Sub:
        {
            Token minus = current_token;
            eat(TokenType::Sub);

            return std::make_shared<UnaryOperator>(minus, factor());
        }

        case TokenType::LeftParen:
        {
            eat(TokenType::LeftParen);
            auto factor = expression();
            eat(TokenType::RightParen);

            return factor;
        }

        case TokenType::Literal:
        {
            auto factor = std::make_shared<Literal>(current_token);
            eat(TokenType::Literal);
            return factor;
        }

        case TokenType::Identifier:
        {
            auto factor = std::make_shared<Variable>(current_token);
            eat(TokenType::Identifier);
            return factor;
        }

        default:
            throw SyntaxError(current_token);
    }
}

std::shared_ptr<Statement> Parser::statement()
{
    if (current_token.type == TokenType::Var)
        return declaration();
    else
        return assignment();
}

std::shared_ptr<Statement> Parser::assignment()
{
    auto var = std::make_shared<Variable>(current_token);

    eat(TokenType::Identifier);
    eat(TokenType::Assign);

    auto expr = expression();

    return std::make_shared<Assignment>(var, expr);
}

std::shared_ptr<Statement> Parser::declaration()
{
    eat(TokenType::Var);

    auto var = std::make_shared<Variable>(current_token);

    eat(TokenType::Identifier);
    eat(TokenType::Assign);

    auto expr = expression();

    return std::make_shared<Declaration>(var, expr);
}
