#include <stack>
#include "parser.hpp"


using namespace Tomato::Syntax;


void Parser::reset(const std::string &text)
{
    lexer.reset(text);
    accept(); // init current token
}


void Parser::accept()
{
    current = lexer.get_next();
}


void Parser::expect(Terminal terminal)
{
    if (current.terminal == terminal)
    {
        accept();
    }
    else
    {
        throw std::runtime_error("Unexpected token: " + to_string(current.terminal) + ", " + to_string(terminal) + " expected.");
    }
}


std::shared_ptr<Statement> Parser::statement()
{
    switch (current.terminal)
    {
        case Terminal::Identifier:
        case Terminal::Literal:
        case Terminal::Operator:
            return expression();

        case Terminal::If:
        case Terminal::While:
        case Terminal::For:
        case Terminal::Print:
        case Terminal::Read:
        default:
            throw std::runtime_error("feature not implemented");
    }
}


std::shared_ptr<Expression> Parser::expression()
{
    return expression(0);
}

std::shared_ptr<Expression> Parser::expression(int precedence)
{
    if (precedence > MaxPrecedence)
        return term();

    auto expr = expression(precedence + 1);

    if (IsLeftAssociative(precedence))
    {
        while (IsBinaryOperator(current.lexeme))
        {
            auto op = GetBinaryOperator(current.lexeme);

            if (GetPrecedence(op) != precedence)
                break;

            accept();

            expr = std::make_shared<BinaryOperation>(expr, op, expression(precedence + 1));
        }
    }
    else if (IsBinaryOperator(current.lexeme))
    {
        auto op = GetBinaryOperator(current.lexeme);

        if (GetPrecedence(op) == precedence)
        {
            accept();
            expr = std::make_shared<BinaryOperation>(expr, op, expression(precedence));
        }
    }

    return expr;
}


std::shared_ptr<Expression> Parser::term()
{
    std::shared_ptr<Expression> expr;

    switch (current.terminal)
    {
        case Terminal::LParen:
            accept();
            expr = expression();
            expect(Terminal::RParen);
            break;

        case Terminal::Operator:
            if (IsUnaryOperator(current.lexeme))
            {
                auto op = GetUnaryOperator(current.lexeme);
                accept();

                expr = std::make_shared<UnaryOperation>(op, term());
                break;
            }
            else
            {
                throw std::runtime_error("oops");
            }

        case Terminal::Identifier:
            expr = std::make_shared<Identifier>(current.lexeme);
            accept();
            break;

        case Terminal::Literal:
            expr = std::make_shared<Literal>(current.lexeme);
            accept();
            break;

        default:
            throw std::runtime_error("oops");
    }

    while (true)
    {
        switch (current.terminal)
        {
            case Terminal::Dot:
            {
                accept();
                auto member = std::make_shared<Identifier>(current.lexeme);
                expect(Terminal::Identifier);
                expr = std::make_shared<MemberAccess>(expr, member);
                break;
            }

            case Terminal::LSquareBracket:
            {
                accept();
                auto index = expression();
                expect(Terminal::RSquareBracket);
                expr = std::make_shared<Indexation>(expr, index);
                break;
            }

            case Terminal::LParen:
            {
                accept();
                // TODO: Parse argument list
                expect(Terminal::RParen);
                expr = std::make_shared<Call>(expr);
                break;
            }

            default:
                return expr;
        }
    }
}
