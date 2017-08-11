#include "parser.hpp"
#include "error.hpp"


using namespace AST;


Parser::Parser(const std::string &code) : lexer(code)
{
    current_token = this->lexer.next_token();
}


std::shared_ptr<Program> Parser::parse()
{
    auto program = std::make_shared<Program>();

    while (current_token.type != Token::Type::EndOfFile)
    {
        program->statements.push_back(statement());
    }

    return program;
}


void Parser::eat(Token::Type expected_type)
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

    while (current_token.type == Token::Type::Add ||
           current_token.type == Token::Type::Sub)
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

    while (current_token.type == Token::Type::Mul ||
           current_token.type == Token::Type::Div)
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

    if (current_token.type == Token::Type::Pow)
    {
        auto pow = current_token;
        eat(Token::Type::Pow);

        auto exponent = power();

        return std::make_shared<BinaryOperator>(base, pow, exponent);
    }

    return base;
}


std::shared_ptr<Expression> Parser::factor()
{
    switch (current_token.type)
    {
        case Token::Type::Add:
        {
            Token plus = current_token;
            eat(Token::Type::Add);

            return std::make_shared<UnaryOperator>(plus, factor());
        }

        case Token::Type::Sub:
        {
            Token minus = current_token;
            eat(Token::Type::Sub);

            return std::make_shared<UnaryOperator>(minus, factor());
        }

        case Token::Type::LParen:
        {
            eat(Token::Type::LParen);
            auto factor = expression();
            eat(Token::Type::RParen);

            return factor;
        }

        case Token::Type::Literal:
        {
            auto factor = std::make_shared<Literal>(current_token);
            eat(Token::Type::Literal);
            return factor;
        }

        case Token::Type::Identifier:
        {
            auto factor = std::make_shared<Variable>(current_token);
            eat(Token::Type::Identifier);
            return factor;
        }

        default:
            throw SyntaxError(current_token);
    }
}


std::shared_ptr<Statement> Parser::statement()
{
    if (current_token.type == Token::Type::Var)
        return declaration();
    else
        return assignment();
}


std::shared_ptr<Statement> Parser::assignment()
{
    auto var = std::make_shared<Variable>(current_token);

    eat(Token::Type::Identifier);
    eat(Token::Type::Assign);

    auto expr = expression();

    return std::make_shared<Assignment>(var, expr);
}


std::shared_ptr<Statement> Parser::declaration()
{
    eat(Token::Type::Var);

    auto var = std::make_shared<Variable>(current_token);

    eat(Token::Type::Identifier);
    eat(Token::Type::Assign);

    auto expr = expression();

    return std::make_shared<Declaration>(var, expr);
}
