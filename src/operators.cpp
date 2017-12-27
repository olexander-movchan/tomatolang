#include "operators.hpp"


using namespace Tomato;


bool Tomato::IsUnaryOperator(const std::string &lexeme)
{
    try
    {
        GetUnaryOperator(lexeme);
        return true;
    }
    catch (std::out_of_range &)
    {
        return false;
    }
}


bool Tomato::IsBinaryOperator(const std::string &lexeme)
{
    try
    {
        GetBinaryOperator(lexeme);
        return true;
    }
    catch (std::out_of_range &)
    {
        return false;
    }
}


UnaryOperator Tomato::GetUnaryOperator(const std::string &lexeme)
{
    static const std::map<std::string, UnaryOperator> map = {
            {"+",   UnaryOperator::Plus},
            {"-",   UnaryOperator::Minus},
            {"*",   UnaryOperator::Unpack},
            {"not", UnaryOperator::Not}
    };

    return map.at(lexeme);
}


BinaryOperator Tomato::GetBinaryOperator(const std::string &lexeme)
{
    static const std::map<std::string, BinaryOperator> map = {
            {"+", BinaryOperator::Plus},
            {"-", BinaryOperator::Minus},
            {"*", BinaryOperator::Mul},
            {"/", BinaryOperator::Div},
            {"%", BinaryOperator::Mod},
            {"^", BinaryOperator::Exp},

//            {"+=", BinaryOperator::AssignPlus},
//            {"-=", BinaryOperator::AssignMinus},
//            {"*=", BinaryOperator::AssignMul},
//            {"/=", BinaryOperator::AssignDiv},
//            {"%=", BinaryOperator::AssignMod},
//            {"^=", BinaryOperator::AssignExp},

            {"and", BinaryOperator::And},
            {"or",  BinaryOperator::Or},
            {"xor", BinaryOperator::Xor},

            {"<",  BinaryOperator::LT},
            {">",  BinaryOperator::GT},
            {"<=", BinaryOperator::LE},
            {">=", BinaryOperator::GE},
            {"==", BinaryOperator::EQ},
            {"!=", BinaryOperator::NE},
    };

    return map.at(lexeme);
}


int Tomato::GetPrecedence(UnaryOperator operator_)
{
    switch (operator_)
    {
        case UnaryOperator::Unpack:
        case UnaryOperator::Plus:
        case UnaryOperator::Minus:
        case UnaryOperator::Not:
            return 0;
    }
}


int Tomato::GetPrecedence(BinaryOperator operator_)
{
    switch (operator_)
    {
        case BinaryOperator::Exp:
            return 5;

        case BinaryOperator::Mul:
        case BinaryOperator::Div:
            return 4;

        case BinaryOperator::Mod:
            return 3;

        case BinaryOperator::Minus:
        case BinaryOperator::Plus:
            return 2;

        case BinaryOperator::LE:
        case BinaryOperator::LT:
        case BinaryOperator::EQ:
        case BinaryOperator::NE:
        case BinaryOperator::GE:
        case BinaryOperator::GT:
            return 1;

        case BinaryOperator::And:
        case BinaryOperator::Or:
        case BinaryOperator::Xor:
            return 0;
    }
}

bool Tomato::IsLeftAssociative(int precedence)
{
    return precedence != 5;
}


const int Tomato::MaxPrecedence = 5;