#include "lexer.hpp"


Token::operator std::string() const
{
    switch (type)
    {
        case TokenType::None      : return "<NONE>";
        case TokenType::EndOfFile : return "<EOF>";

        case TokenType::VariableDeclaration : return "<var>";
        case TokenType::LeftParen    : return "<left_paren>";
        case TokenType::RightParen   : return "right_paren>";

        case TokenType::OperatorPlus  : return "<plus>";
        case TokenType::OperatorMinus : return "<minus>";
        case TokenType::OperatorMul   : return "<mul>";
        case TokenType::OperatorDiv   : return "<div>";
        case TokenType::OperatorPow   : return "<pow>";
        case TokenType::Assignment    : return "<assign>";

        case TokenType::Literal    : return "<integer: " + lexeme + ">";
        case TokenType::Identifier : return "<identifier: " + lexeme + ">";
    }
}


std::map<std::string, Token> Lexer::keywords = {
        {"var", Token{TokenType::VariableDeclaration, "var"}}
};


Lexer::Lexer(std::string source_code) : code(source_code), offset(0) {}


Token Lexer::next_token()
{
    skip_whitespace();

    if (offset == code.length())
        return {TokenType::EndOfFile, ""};

    char ch = code[offset++];

    if (ch == '+')
    {
        return {TokenType::OperatorPlus, "+"};
    }

    if (ch == '-')
    {
        return {TokenType::OperatorMinus, "-"};
    }

    if (ch == '*')
    {
        return {TokenType::OperatorMul, "*"};
    }

    if (ch == '/')
    {
        return {TokenType::OperatorDiv, "/"};
    }

    if (ch == '^')
    {
        return {TokenType::OperatorPow, "^"};
    }

    if (ch == '=')
    {
        return {TokenType::Assignment, "="};
    }

    if (ch == '(')
    {
        return {TokenType::LeftParen, "("};
    }

    if (ch == ')')
    {
        return {TokenType::RightParen, ")"};
    }

    if (std::isdigit(ch))
    {
        offset--;
        return literal();
    }

    if (std::isalpha(ch))
    {
        offset--;
        return identifier();
    }

    return {TokenType::None, std::string(1, ch)};
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
