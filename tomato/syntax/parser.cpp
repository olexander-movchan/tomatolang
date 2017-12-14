#include "parser.hpp"

#include <stack>
#include <iostream>


using namespace Tomato::Syntax;


void Parser::set_text(const std::string &text)
{
    lexer.set_text(text);
    accept(); // init current token
}


bool Parser::eof() const
{
    return current.terminal == Terminal::EndOfFile;
}


void Parser::accept()
{
    current = lexer.get_next();
}


void Parser::reject(const std::string &expected)
{
    throw SyntaxError(expected + " expected, got " + to_string(current) + " instead");
}


void Parser::expect(Terminal expected)
{
    if (current.terminal == expected)
        accept();
    else
        reject(to_string(expected));
}


std::shared_ptr<ASTNode> Parser::parse()
{
    return statement();
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
    switch (current.terminal)
    {
        case Terminal::Operator:
            if (IsUnaryOperator(current.lexeme))
            {
                auto op = GetUnaryOperator(current.lexeme);
                accept();

                return std::make_shared<UnaryOperation>(op, term());
            }
            else
            {
                reject("unary operator");
            }

        case Terminal::LParen:
            {
                accept();
                auto expr = expression();
                expect(Terminal::RParen);

                return expr;
            }

        case Terminal::Identifier:
            return identifier();

        case Terminal::Literal:
            return literal();

        default:
            reject("expression");
    }
}

std::shared_ptr<Identifier> Parser::identifier()
{
    auto id = std::make_shared<Identifier>(current.lexeme);
    expect(Terminal::Identifier);
    return id;
}

std::shared_ptr<Literal> Parser::literal()
{
    auto lit = std::make_shared<Literal>(current.lexeme);
    expect(Terminal::Literal);
    return lit;
}

std::shared_ptr<Statement> Parser::statement()
{
    switch (current.terminal)
    {
        case Terminal::Identifier:
        case Terminal::Literal:
        case Terminal::Operator:
        case Terminal::LParen:
            return expression();

        case Terminal::Let:
        case Terminal::Var:
            return value_declaration();

        case Terminal::Print:
            return print_statement();

        default:
            reject("statement");
    }
}

std::shared_ptr<ValueDeclaration> Parser::value_declaration()
{
    std::shared_ptr<Identifier> value;
    std::shared_ptr<Identifier> type;
    std::shared_ptr<Expression> init;
    bool constant;

    switch (current.terminal)
    {
        case Terminal::Let:
            accept();
            constant = true;
            break;

        case Terminal::Var:
            accept();
            constant = false;
            break;

        default:
            reject("value declaration");
    }

    value = identifier();

    if (current.terminal == Terminal::Identifier)
    {
        type = identifier();
    }

    if (constant || current.terminal == Terminal::Operator)
    {
        if (current.lexeme != "=")
            reject("initializer");

        accept();
        init = expression();
    }

    if (!type && !init)
    {
        reject("type or initializer");
    }

    return std::make_shared<ValueDeclaration>(value, type, init, constant);
}


std::shared_ptr<PrintStatement> Parser::print_statement()
{
    expect(Terminal::Print);

    return std::make_shared<PrintStatement>(expression());
}
