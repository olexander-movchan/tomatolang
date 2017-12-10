#include <iostream>
#include "lexer.hpp"


using namespace Tomato::Syntax;


std::string Tomato::Syntax::to_string(Terminal terminal)
{
    switch (terminal)
    {
        case Terminal::Invalid:     return "INVALID";
        case Terminal::EndOfFile:   return "EOF";

        case Terminal::Import:      return "import";
        case Terminal::Operator:    return "operator";
        case Terminal::Identifier:  return "identifier";
        case Terminal::LParen:      return "lparen";
        case Terminal::RParen:      return "rparen";
        case Terminal::Literal:     return "literal";
        case Terminal::Var:         return "var";
        case Terminal::Let:         return "let";
        case Terminal::If:          return "if";
        case Terminal::Then:        return "then";
        case Terminal::Else:        return "else";
        case Terminal::End:         return "end";
        case Terminal::While:       return "while";
        case Terminal::Do:          return "do";
        case Terminal::For:         return "for";
        case Terminal::In:          return "in";
        case Terminal::Func:        return "func";
    }
}


std::string Tomato::Syntax::to_string(const Token &token)
{
    switch (token.terminal)
    {
        case Terminal::Invalid:
        case Terminal::Identifier:
        case Terminal::Literal:
        case Terminal::Operator:
            return "<" + to_string(token.terminal) + ": " + token.lexeme + ">";

        default:
            return "<" + to_string(token.terminal) + ">";
    }
}


InvalidToken::InvalidToken(const std::string &message) : runtime_error(message) {}


const std::map<std::string, Terminal> Lexer::keywords = {
        {"import",  Terminal::Import},
        {"let",     Terminal::Let},
        {"var",     Terminal::Var},
        {"if",      Terminal::If},
        {"then",    Terminal::Then},
        {"else",    Terminal::Else},
        {"end",     Terminal::End},
        {"while",   Terminal::While},
        {"do",      Terminal::Do},
        {"for",     Terminal::For},
        {"in",      Terminal::In},
        {"func",    Terminal::Func},

        {"true",    Terminal::Literal},
        {"false",   Terminal::Literal},

        {"and",     Terminal::Operator},
        {"or",      Terminal::Operator},
        {"not",     Terminal::Operator},
};


Lexer::Lexer(const std::string &text)
{
    reset(text);
}


void Lexer::reset(const std::string &text)
{
    this->text = text;
    offset = len = 0;
}


bool Lexer::eof()
{
    skip_whitespace();
    return !current();
}


void Lexer::skip_whitespace()
{
    while (std::isspace(current()))
    {
        skip();
    }
}


char Lexer::current()
{
    if (offset + len >= text.length())
        return '\0';
    else
        return text[offset + len];
}


void Lexer::skip()
{
    offset += 1;
}


void Lexer::accept()
{
    len += 1;
}


void Lexer::expect(char character)
{
    if (current() == character)
        accept();
    else
        error();
}


void Lexer::error()
{
    throw InvalidToken("Invalid token: " + to_string(token(Terminal::Invalid)));
}


Token Lexer::token(Terminal terminal)
{
    auto lexeme = text.substr(offset, len);

    offset += len;
    len = 0;

    skip_whitespace();

    if (keywords.find(lexeme) != keywords.end())
    {
        return Token {keywords.at(lexeme), lexeme};
    }

    return Token {terminal, lexeme};
}


Token Lexer::get_next()
{
    skip_whitespace();

    if (std::isdigit(current()))
    {
        return number();
    }

    if (std::isalpha(current()))
    {
        return identifier();
    }

    switch (current())
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '&':
        case '|':
        case '^':
        case '<':
        case '>':
        case '=':
        case '!':
            return operator_();

        case '(':
            accept();
            return token(Terminal::LParen);

        case ')':
            accept();
            return token(Terminal::RParen);

        case '"':
            return string_literal();

        case '\'':
            return char_literal();

        default:
            break;
    }

    accept();
    error();
}


Token Lexer::number()
{
    if (!std::isdigit(current()))
    {
        accept();
        error();
    }

    while (std::isdigit(current()))
        accept();

    if (current() == '.')
    {
        accept();

        if (!std::isdigit(current()))
        {
            error();
        }

        while (isdigit(current()))
            accept();
    }

    return token(Terminal::Literal);
}


Token Lexer::identifier()
{
    if (!std::isalnum(current()))
    {
        accept();
        error();
    }

    while (std::isalnum(current()))
        accept();

    return token(Terminal::Identifier);
}


Token Lexer::operator_()
{
    switch (current())
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '&':
        case '|':
        case '^':
        case '<':
        case '>':
        case '=':
            accept();

            if (current() == '=')
            {
                accept();
            }

            return token(Terminal::Operator);

        case '!':
            accept();

            if (current() == '=')
            {
                accept();
                return token(Terminal::Operator);
            }
            else
            {
                return token(Terminal::Invalid);
            }

        default:
            accept();
            error();
    }
}

Token Lexer::string_literal()
{
    expect('"');

    while (current() && current() != '"')
    {
        if (current() == '\\')
        {
            accept();
            accept();
        }
        else
        {
            accept();
        }
    }

    expect('"');

    return token(Terminal::Literal);
}


Token Lexer::char_literal()
{
    expect('\'');

    if (current() == '\\')
    {
        accept();
    }
    accept();

    expect('\'');

    return token(Terminal::Literal);
}
