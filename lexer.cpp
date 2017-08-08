#include "lexer.hpp"


Token::operator std::string() const
{
    switch (type)
    {
        case TokenType::None      : return "<NONE>";
        case TokenType::EndOfFile : return "<EOF>";
        case TokenType::Assign    : return "<assign>";

        case TokenType::LeftParen    : return "<left_paren>";
        case TokenType::RightParen   : return "right_paren>";

        case TokenType::Var : return "<var>";
        case TokenType::Add : return "<add>";
        case TokenType::Sub : return "<sub>";
        case TokenType::Mul : return "<mul>";
        case TokenType::Div : return "<div>";
        case TokenType::Pow : return "<pow>";

        case TokenType::Literal    : return "<literal: " + lexeme + ">";
        case TokenType::Identifier : return "<identifier: " + lexeme + ">";
    }
}


std::map<std::string, Token> Lexer::keywords = {
        {"var", Token{TokenType::Var, "var"}}
};


Lexer::Lexer(std::string source_code) : code(source_code), offset(0) {}


Token Lexer::next_token()
{
    skip_whitespace();

    if (offset == code.length())
        return {TokenType::EndOfFile, ""};

    // Check one-char tokens
    switch (code[offset++])
    {
        case '+':
            return {TokenType::Add, "+"};

        case '-':
            return {TokenType::Sub, "-"};

        case '*':
            return {TokenType::Mul, "*"};

        case '/':
            return {TokenType::Div, "/"};

        case '^':
            return {TokenType::Pow, "^"};

        case '=':
            return {TokenType::Assign, "="};

        case '(':
            return {TokenType::LeftParen, "("};

        case ')':
            return {TokenType::RightParen, ")"};

        default:
            offset--;
    }

    if (std::isdigit(code[offset]))
    {
        return literal();
    }

    if (std::isalpha(code[offset]))
    {
        return identifier();
    }

    throw std::runtime_error("Unexpected character");
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
    Token token{TokenType::Literal};

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
        return Token{TokenType::Identifier, lexeme};
}
