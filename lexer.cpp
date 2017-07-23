#include "lexer.hpp"


std::ostream &operator<<(std::ostream &stream, const TokenType type)
{
    switch (type)
    {
        case TokenType::Unknown      : stream << "UNKNOWN";        break;
        case TokenType::Integer      : stream << "INTEGER";        break;
        case TokenType::EndOfFile    : stream << "END_OF_FILE";    break;

        case TokenType::OperatorPlus  : stream << "OPERATOR_PLUS";   break;
        case TokenType::OperatorMinus : stream << "OPERATOR_MINUS";  break;
        case TokenType::OperatorMul   : stream << "OPERATOR_MUL";    break;
        case TokenType::OperatorDiv   : stream << "OPERATOR_DIV";    break;
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

    if (std::isdigit(ch))
    {
        offset--;
        return integer();
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

Token Lexer::integer()
{
    Token token{TokenType::Integer};

    std::size_t len = 0;
    while (std::isdigit(code[offset + len]))
        ++len;

    token.lexeme = code.substr(offset, len);

    offset += len;

    return token;
}
