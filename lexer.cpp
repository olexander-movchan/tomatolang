#include "lexer.hpp"


std::ostream &operator<<(std::ostream &stream, const TokenType type)
{
    switch (type)
    {
        case TokenType::Unknown      : stream << "UNKNOWN";        break;
        case TokenType::Integer      : stream << "INTEGER";        break;
        case TokenType::OperatorPlus : stream << "OPERATOR_PLUS";  break;
        case TokenType::EndOfFile    : stream << "END_OF_FILE";    break;
    }

    return stream;
}


std::ostream &operator<<(std::ostream &stream, const Token &token)
{
    return stream << '<' << token.type << ": " << token.lexeme << '>';
}


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
    if (std::isdigit(ch))
    {
        return {TokenType::Integer, std::string(1, ch)};
    }

    return {TokenType::Unknown, std::string(1, ch)};
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
