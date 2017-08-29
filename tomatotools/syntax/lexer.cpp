#include "lexer.hpp"


using namespace Tomato;


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


Lexer::Lexer(const std::string &code) : code(code) {}


char Lexer::current_char()
{
    return code[current_offset];
}


void Lexer::advance()
{
    if (current_char() == '\n')
    {
        current_point.line  += 1;
        current_point.column = 1;
    }
    else
    {
        current_point.column += 1;
    }

    current_offset += 1;
}


bool Lexer::eof() const
{
    return current_offset >= code.length();
}


Token Lexer::token(Token::Type type)
{
    auto token = Token(type, code.substr(start_offset, current_offset - start_offset), start_point);

    return token;
}


Token Lexer::next()
{
    skip_whitespace();

    // Save token start position
    start_offset = current_offset;
    start_point  = current_point;

    if (eof())
    {
        return token(Token::Type::EndOfFile);
    }

    if (current_char() == '\n')
    {
        advance();
        return Token(Token::Type::EndOfLine, "\n");
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
        return token(keywords[id.lexeme]);
    else
        return id;
}
