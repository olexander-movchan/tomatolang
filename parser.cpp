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
        case TokenType::OperatorPlus:
        {
            Token plus = current_token;
            eat(TokenType::OperatorPlus);

            return std::make_shared<UnaryOperator>(plus, factor());
        }

        case TokenType::OperatorMinus:
        {
            Token minus = current_token;
            eat(TokenType::OperatorMinus);

            return std::make_shared<UnaryOperator>(minus, factor());
        }

        case TokenType::LeftParen:
        {
            eat(TokenType::LeftParen);
            auto factor = expression();
            eat(TokenType::RightParen);

            return factor;
        }

        case TokenType::Integer:
        {
            auto factor = std::make_shared<Constant>(current_token);
            eat(TokenType::Integer);
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
    if (current_token.type == TokenType::VariableDecl)
        return declaration();
    else
        return assignment();
}

std::shared_ptr<Statement> Parser::assignment()
{
    auto var = std::make_shared<Variable>(current_token);

    eat(TokenType::Identifier);
    eat(TokenType::Assignment);

    auto expr = expression();

    return std::make_shared<Assignment>(var, expr);
}

std::shared_ptr<Statement> Parser::declaration()
{
    eat(TokenType::VariableDecl);

    auto var = std::make_shared<Variable>(current_token);

    eat(TokenType::Identifier);
    eat(TokenType::Assignment);

    auto expr = expression();

    return std::make_shared<Declaration>(var, expr);
}
