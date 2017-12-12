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


void Parser::expect(Terminal terminal)
{
    if (current.terminal == terminal)
    {
        accept();
    }
    else
    {
        error(to_string(terminal));
    }
}


void Parser::error(const std::string &expected)
{
    throw SyntaxError("syntax error: " + expected + " expected, got " + to_string(current) + " instead");
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

        case Terminal::If:
            return if_statement();

        case Terminal::While:
            return while_statement();

        case Terminal::For:
            return for_statement();

        case Terminal::Print:
            return print_statement();

        case Terminal::Read:
            return read_statement();

        default:
            error("statement");
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
            error("expresion");
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

std::shared_ptr<ConditionalStatement> Parser::if_statement()
{
    expect(Terminal::If);

    auto condition = expression();

    expect(Terminal::Then);

    auto then_case = statement_block();
    decltype(then_case) else_case;

    if (current.terminal == Terminal::Else)
    {
        accept();
        else_case = statement_block();
    }
    else
    {
        else_case = std::make_shared<StatementBlock>();
    }

    expect(Terminal::End);

    return std::make_shared<ConditionalStatement>(condition, then_case, else_case);
}

std::shared_ptr<ConditionalLoop> Parser::while_statement()
{
    expect(Terminal::While);

    auto condition = expression();

    expect(Terminal::Do);

    auto body = statement_block();

    expect(Terminal::End);

    return std::make_shared<ConditionalLoop>(condition, body);
}

std::shared_ptr<Statement> Parser::for_statement()
{
    expect(Terminal::For);

    auto id = current;
    expect(Terminal::Identifier);

    expect(Terminal::In);

    auto iterable = expression();

    expect(Terminal::Do);

    auto body = statement_block();

    expect(Terminal::End);

    throw std::runtime_error("Oops, not implemented yet...");
}

std::shared_ptr<PrintStatement> Parser::print_statement()
{
    expect(Terminal::Print);
    auto value = expression();

    return std::make_shared<PrintStatement>(value);
}


std::shared_ptr<ReadStatement> Parser::read_statement()
{
    expect(Terminal::Read);
    auto value = expression();

    return std::make_shared<ReadStatement>(value);
}


std::shared_ptr<StatementBlock> Parser::statement_block()
{
    auto block = std::make_shared<StatementBlock>();

    while (current.terminal != Terminal::End && current.terminal != Terminal::EndOfFile)
    {
        try
        {
            block->statements.push_back(statement());
        }
        catch (SyntaxError &error)
        {
            accept();

            m_errors.push_back(error);

            std::clog << error.what() << std::endl;
        }
    }
}


std::shared_ptr<ValueDeclaration> Parser::value_declaration()
{

}
