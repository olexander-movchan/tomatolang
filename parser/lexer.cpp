#include "lexer.hpp"
#include "error.hpp"


std::map<std::string, Token> Lexer::keywords = {
        {"var", Token{Token::Type::Var, "var"}},
        {"and", Token{Token::Type::And, "and"}},
        {"not", Token{Token::Type::Not, "not"}},
        {"or",  Token{Token::Type::Or,  "or" }},
};


Lexer::Lexer(std::string source_code) : code(source_code), offset(0) {}


Token Lexer::next_token()
{
    skip_whitespace();

    if (offset == code.length())
        return {Token::Type::EndOfFile, ""};

    // Check operator tokens:
    switch (code[offset++])
    {
        case '+':
            return {Token::Type::Add, "+"};

        case '-':
            return {Token::Type::Sub, "-"};

        case '*':
            return {Token::Type::Mul, "*"};

        case '/':
            return {Token::Type::Div, "/"};

        case '^':
            return {Token::Type::Pow, "^"};

        case '(':
            return {Token::Type::LParen, "("};

        case ')':
            return {Token::Type::RParen, ")"};

        case '=':
        {
            if (code[offset] == '=')
            {
                offset += 1;
                return {Token::Type::EQ, "=="};
            }
            else
            {
                return {Token::Type::Assign, "="};
            }
        }

        case '<':
        {
            if (code[offset] == '=')
            {
                offset += 1;
                return {Token::Type::LE, "<="};
            }
            else
            {
                return {Token::Type::LT, "<"};
            }
        }

        case '>':
        {
            if (code[offset] == '=')
            {
                offset += 1;
                return {Token::Type::GE, ">="};
            }
            else
            {
                return {Token::Type::GT, ">"};
            }
        }

        case '!':
        {
            if (code[offset+1] == '=')
            {
                offset += 1;
                return {Token::Type::NE, "!="};
            }
            else
            {
                offset -= 1;
                throw SyntaxError("Invalid token: " + code.substr(offset, 4) + "...");
            }
        }

        default:
            offset--;
    }

    // Numerical literal
    if (std::isdigit(code[offset]))
    {
        return literal();
    }

    // Identifier
    if (std::isalpha(code[offset]))
    {
        return identifier();
    }

    // Neither of valid token appeared
    throw std::runtime_error("Invalid token: " + code.substr(offset, 5) + "...");
}


bool Lexer::eof() const
{
    return offset == code.length();
}


void Lexer::skip_whitespace()
{
    while (!eof())
    {
        switch (code[offset])
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                ++offset;
                break;

            default:
                return;
        }
    }
}


Token Lexer::literal()
{
    Token token{Token::Type::Literal};

    std::size_t len = 0;
    while (std::isdigit(code[offset + len]))
        ++len;

    token.lexeme = code.substr(offset, len);
    offset += len;

    if (code[offset] == '.')
    {
        len = 1;
        while (std::isdigit(code[offset + len]))
            ++len;

        token.lexeme += code.substr(offset, len);
        offset += len;
    }

    return token;
}


Token Lexer::identifier()
{
    std::size_t len = 0;
    while (std::isalpha(code[offset + len]))
        ++len;

    std::string lexeme = code.substr(offset, len);
    offset += len;

    if (keywords.find(lexeme) != keywords.end())
        return  keywords[lexeme];
    else
        return Token{Token::Type::Identifier, lexeme};
}
