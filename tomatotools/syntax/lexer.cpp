#include "lexer.hpp"


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


Lexer::Lexer(const std::string &code) : code(code), offset(0) {}


char Lexer::current_char()
{
    return code[offset];
}


void Lexer::advance()
{
    if (current_char() == '\n')
    {
        current_pos.line  += 1;
        current_pos.column = 1;
    }
    else
    {
        current_pos.column += 1;
    }

    offset += 1;
}


bool Lexer::eof() const
{
    return offset == code.length();
}


Token Lexer::next()
{
    skip_whitespace();

    if (eof())
    {
        return Token(Token::Type::EndOfFile, "", current_pos);
    }

    // Save token start position
    token_pos = current_pos;


    if (current_char() == '\n')
    {
        advance();
        return Token(Token::Type::EndOfLine, "\n", token_pos);
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
    return Token(Token::Type::Invalid, code.substr(offset-1, 1), token_pos);
}


Token Lexer::operator_token()
{
    char current = current_char();
    advance();

    switch (current)
    {
        case '+':
            return Token(Token::Type::Add, "+", token_pos);

        case '-':
            return Token(Token::Type::Sub, "-", token_pos);

        case '*':
            return Token(Token::Type::Mul, "*", token_pos);

        case '/':
        {
            if (current_char() == '/')
            {
                advance();
                return Token(Token::Type::IntDiv, "//", token_pos);
            }
            else
            {
                return Token(Token::Type::Div, "/", token_pos);
            }
        }

        case '^':
            return Token(Token::Type::Exp, "^", token_pos);

        case '(':
            return Token(Token::Type::LParen, "(", token_pos);

        case ')':
            return Token(Token::Type::RParen, ")", token_pos);

        case '=':
        {
            if (current_char() == '=')
            {
                advance();
                return Token(Token::Type::EQ, "==", token_pos);
            }
            else
            {
                return Token(Token::Type::Assign, "=", token_pos);
            }
        }

        case '<':
        {
            if (current_char() == '=')
            {
                advance();
                return Token(Token::Type::LE, "<=", token_pos);
            }
            else
            {
                return Token(Token::Type::LT, "<", token_pos);
            }
        }

        case '>':
        {
            if (current_char() == '=')
            {
                advance();
                return Token(Token::Type::GE, ">=", token_pos);
            }
            else
            {
                return Token(Token::Type::GT, ">", token_pos);
            }
        }

        case '!':
        {
            if (current_char() == '=')
            {
                advance();
                return Token(Token::Type::NE, "!=", token_pos);
            }
            else
            {
                break;
            }
        }

        default:
            break;
    }

    return Token(Token::Type::Invalid, code.substr(offset-1, 1), token_pos);
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

    std::size_t len = current_pos.column - token_pos.column;
    std::string lexeme = code.substr(offset - len, len);

    return Token(Token::Type::Literal, lexeme, token_pos);
}


Token Lexer::identifier()
{
    while (std::isalpha(current_char()))
        advance();

    std::size_t len = current_pos.column - token_pos.column;
    std::string lexeme = code.substr(offset - len, len);

    if (keywords.find(lexeme) != keywords.end())
    {
        return Token(keywords[lexeme], lexeme, token_pos);
    }
    else
    {
        return Token(Token::Type::Identifier, lexeme, token_pos);
    }
}
