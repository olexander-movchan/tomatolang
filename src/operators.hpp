#ifndef TOMATO_OPERATORS_HPP
#define TOMATO_OPERATORS_HPP


#include <map>


namespace Tomato::Syntax
{
    enum class BinaryOperator
    {
        Plus, Minus, Mul, Div, Mod, Exp, Assign,
        AssignPlus, AssignMinus, AssignMul, AssignDiv, AssignMod, AssignExp,

        LT, LE, EQ, NE, GE, GT,

        And, Or, Xor,
    };


    enum class UnaryOperator
    {
        Plus, Minus, Not, Unpack,
    };


    bool IsUnaryOperator(const std::string &lexeme);
    bool IsBinaryOperator(const std::string &lexeme);

    UnaryOperator GetUnaryOperator(const std::string &lexeme);
    BinaryOperator GetBinaryOperator(const std::string &lexeme);

    int GetPrecedence(UnaryOperator operator_);
    int GetPrecedence(BinaryOperator operator_);

    bool IsLeftAssociative(int precedence);

    extern const int MaxPrecedence;
}


#endif //TOMATO_OPERATORS_HPP
