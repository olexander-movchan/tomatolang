#include "lexer.hpp"


using namespace Tomato;


CodePoint Lexer::Pointer;


std::map<std::string, Token::Type> Lexer::keywords = {
        { "var"    ,  Token::Type::Var },
        { "let"    ,  Token::Type::Let },

        { "if"     ,  Token::Type::If },
        { "then"   ,  Token::Type::Then },
        { "else"   ,  Token::Type::Else },
        { "end"    ,  Token::Type::End },
        { "for"    ,  Token::Type::For },
        { "in "    ,  Token::Type::In },
        { "while"  ,  Token::Type::While },
        { "do"     ,  Token::Type::Do },

        { "and"    ,  Token::Type::And },
        { "not"    ,  Token::Type::Not },
        { "or"     ,  Token::Type::Or },

        { "true"   ,  Token::Type::Literal },
        { "false"  ,  Token::Type::Literal },

        { "print"  ,  Token::Type::Print },
};


void Lexer::append(const std::string &code)
{
    reset(source_buffer + code);
}


void Lexer::reset(const std::string &code)
{
    source_buffer = code;
    navigator.move(CodePoint {0, 0});
    current_offset = start_offset = 0;
}



char Lexer::current_char()
{
    return source_buffer[current_offset];
}


void Lexer::advance()
{
    if (current_char() == '\n')
    {
        navigator.top().line  += 1;
        navigator.top().column = 0;
    }
    else
    {
        navigator.top().column += 1;
    }

    current_offset += 1;
}


bool Lexer::eof() const
{
    return current_offset >= source_buffer.length();
}


Token Lexer::token(Token::Type type)
{
    CodePoint end = navigator.pop();

    auto token = Token(type, source_buffer.substr(start_offset, current_offset - start_offset), navigator.top());

    navigator.move(end);
    return token;
}


Token Lexer::next_token()
{
    skip_whitespace();

    // Save token start location
    start_offset = current_offset;
    navigator.push();

    if (eof())
    {
        return token(Token::Type::EndOfFile);
    }

    static const std::string op_chars = "+-*/%^<!=>()";
    if (op_chars.find(current_char()) != op_chars.npos)
    {
        return operator_token();
    }

    // Numerical literal
    if (std::isdigit(current_char()))
    {
        return literal();
    }

    // Identifier
    if (std::isalpha(current_char()))
    {
        return identifier();
    }

    // Neither of valid token appeared
    advance();
    return token(Token::Type::Invalid);
}


Token Lexer::operator_token()
{
    char current = current_char();
    advance();

    switch (current)
    {
        case '+':
            return token(Token::Type::Add);

        case '-':
            return token(Token::Type::Sub);

        case '*':
            return token(Token::Type::Mul);

        case '/':
        {
            if (current_char() == '/')
            {
                advance();
                return token(Token::Type::IntDiv);
            }
            else
            {
                return token(Token::Type::Div);
            }
        }

        case '^':
            return token(Token::Type::Exp);

        case '(':
            return token(Token::Type::LParen);

        case ')':
            return token(Token::Type::RParen);

        case '=':
        {
            if (current_char() == '=')
            {
                advance();
                return token(Token::Type::EQ);
            }
            else
            {
                return token(Token::Type::Assign);
            }
        }

        case '<':
        {
            if (current_char() == '=')
            {
                advance();
                return token(Token::Type::LE);
            }
            else
            {
                return token(Token::Type::LT);
            }
        }

        case '>':
        {
            if (current_char() == '=')
            {
                advance();
                return token(Token::Type::GE);
            }
            else
            {
                return token(Token::Type::GT);
            }
        }

        case '!':
        {
            if (current_char() == '=')
            {
                advance();
                return token(Token::Type::NE);
            }
            else
            {
                break;
            }
        }

        default:
            break;
    }

    return token(Token::Type::Invalid);
}


void Lexer::skip_whitespace()
{
    while (!eof())
    {
        switch (current_char())
        {
            case ' ':
            case '\t':
            case '\n':
                advance();
                break;

            default:
                return;
        }
    }
}


Token Lexer::literal()
{
    while (std::isdigit(current_char()))
        advance();

    if (current_char() == '.')
    {
        advance();

        while (std::isdigit(current_char()))
            advance();
    }

    return token(Token::Type::Literal);
}


Token Lexer::identifier()
{
    while (std::isalpha(current_char()))
        advance();

    auto id = token(Token::Type::Identifier);

    if (keywords.find(id.lexeme) != keywords.end())
        return Token(keywords[id.lexeme], id.lexeme, id.location);
    else
        return id;
}
