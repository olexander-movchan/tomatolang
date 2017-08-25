#include "token.hpp"


Token::Token(const Token::Type &type, const std::string &lexeme, Token::Position position)
        : type(type), lexeme(lexeme), position(position) {}


bool Token::is_binary_op() const
{
    switch (type)
    {
        case Token::Type::Or:
        case Token::Type::And:
        case Token::Type::LT:
        case Token::Type::GT:
        case Token::Type::LE:
        case Token::Type::GE:
        case Token::Type::EQ:
        case Token::Type::NE:
        case Token::Type::Add:
        case Token::Type::Sub:
        case Token::Type::Mul:
        case Token::Type::Div:
        case Token::Type::IntDiv:
        case Token::Type::Mod:
        case Token::Type::Exp:
            return true;

        default:
            return false;
    }
}


bool Token::is_unary_op() const
{
    switch (type)
    {
        case Token::Type::Not:
        case Token::Type::Add:
        case Token::Type::Sub:
            return true;

        default:
            return false;
    }
}
