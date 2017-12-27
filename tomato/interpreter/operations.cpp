#include "operations.hpp"


using namespace Tomato;
using namespace Tomato::Semantic;
using namespace Tomato::Runtime;


void Operations::define(Symbol ltype, BinaryOperator op, Symbol rtype, const BinaryOperation &definition)
{
    binary_operations[std::make_tuple(ltype, op ,rtype)] = definition;
}

void Operations::define(UnaryOperator op, Symbol type, const UnaryOperation &definition)
{
    unary_operations[std::make_tuple(op, type)] = definition;
}

const BinaryOperation &Operations::lookup(Symbol ltype, BinaryOperator op, Symbol rtype)
{
    try
    {
        return binary_operations.at(std::make_tuple(ltype, op, rtype));
    }
    catch (std::out_of_range &)
    {
        throw SemanticError("undefined operation");
    }
}

const UnaryOperation &Operations::lookup(UnaryOperator op, Symbol type)
{
    try
    {
        return unary_operations.at(std::make_tuple(op, type));
    }
    catch (std::out_of_range &)
    {
        throw SemanticError("undefined operation");
    }
}


void Operations::init_builtins(Symbol symbol_int, Symbol symbol_float, Symbol symbol_bool)
{
    // Integer operations
    define(symbol_int, BinaryOperator::Plus, symbol_int, Runtime::Operation<int, int, int, Runtime::Sum>(symbol_int));
    define(symbol_int, BinaryOperator::Minus, symbol_int, Runtime::Operation<int, int, int, Runtime::Sub>(symbol_int));
    define(symbol_int, BinaryOperator::Mul, symbol_int, Runtime::Operation<int, int, int, Runtime::Mul>(symbol_int));
    define(symbol_int, BinaryOperator::Div, symbol_int, Runtime::Operation<int, int, float, Runtime::Div>(symbol_float));
    define(symbol_int, BinaryOperator::Mod, symbol_int, Runtime::Operation<int, int, int, Runtime::Mod>(symbol_int));
    define(symbol_int, BinaryOperator::Exp, symbol_int, Runtime::Operation<int, int, int, Runtime::Exp>(symbol_int));

    define(symbol_int, BinaryOperator::EQ, symbol_int, Runtime::Operation<int, int, bool, Runtime::EQ>(symbol_bool));
    define(symbol_int, BinaryOperator::NE, symbol_int, Runtime::Operation<int, int, bool, Runtime::NE>(symbol_bool));
    define(symbol_int, BinaryOperator::LT, symbol_int, Runtime::Operation<int, int, bool, Runtime::LT>(symbol_bool));
    define(symbol_int, BinaryOperator::LE, symbol_int, Runtime::Operation<int, int, bool, Runtime::LE>(symbol_bool));
    define(symbol_int, BinaryOperator::GE, symbol_int, Runtime::Operation<int, int, bool, Runtime::GE>(symbol_bool));
    define(symbol_int, BinaryOperator::GT, symbol_int, Runtime::Operation<int, int, bool, Runtime::GT>(symbol_bool));


    // Float operations
    define(symbol_float, BinaryOperator::Plus, symbol_float, Runtime::Operation<float, float, float, Runtime::Sum>(symbol_float));
    define(symbol_float, BinaryOperator::Minus, symbol_float, Runtime::Operation<float, float, float, Runtime::Sub>(symbol_float));
    define(symbol_float, BinaryOperator::Mul, symbol_float, Runtime::Operation<float, float, float, Runtime::Mul>(symbol_float));
    define(symbol_float, BinaryOperator::Div, symbol_float, Runtime::Operation<float, float, float, Runtime::Div>(symbol_float));
    define(symbol_float, BinaryOperator::Exp, symbol_float, Runtime::Operation<float, float, float, Runtime::Exp>(symbol_float));

    define(symbol_float, BinaryOperator::EQ, symbol_float, Runtime::Operation<float, float, bool, Runtime::EQ>(symbol_bool));
    define(symbol_float, BinaryOperator::NE, symbol_float, Runtime::Operation<float, float, bool, Runtime::NE>(symbol_bool));
    define(symbol_float, BinaryOperator::LT, symbol_float, Runtime::Operation<float, float, bool, Runtime::LT>(symbol_bool));
    define(symbol_float, BinaryOperator::LE, symbol_float, Runtime::Operation<float, float, bool, Runtime::LE>(symbol_bool));
    define(symbol_float, BinaryOperator::GE, symbol_float, Runtime::Operation<float, float, bool, Runtime::GE>(symbol_bool));
    define(symbol_float, BinaryOperator::GT, symbol_float, Runtime::Operation<float, float, bool, Runtime::GT>(symbol_bool));


    // Integer with float operations
    define(symbol_int, BinaryOperator::Plus, symbol_float, Runtime::Operation<int, float, float, Runtime::Sum>(symbol_float));
    define(symbol_float, BinaryOperator::Plus, symbol_int, Runtime::Operation<float, int, float, Runtime::Sum>(symbol_float));
    define(symbol_int, BinaryOperator::Minus, symbol_float, Runtime::Operation<int, float, float, Runtime::Sub>(symbol_float));
    define(symbol_float, BinaryOperator::Minus, symbol_int, Runtime::Operation<float, int, float, Runtime::Sub>(symbol_float));
    define(symbol_int, BinaryOperator::Mul, symbol_float, Runtime::Operation<int, float, float, Runtime::Mul>(symbol_float));
    define(symbol_float, BinaryOperator::Mul, symbol_int, Runtime::Operation<float, int, float, Runtime::Mul>(symbol_float));
    define(symbol_int, BinaryOperator::Div, symbol_float, Runtime::Operation<int, float, float, Runtime::Div>(symbol_float));
    define(symbol_float, BinaryOperator::Div, symbol_int, Runtime::Operation<float, int, float, Runtime::Div>(symbol_float));
    define(symbol_int, BinaryOperator::Exp, symbol_float, Runtime::Operation<int, float, float, Runtime::Exp>(symbol_float));
    define(symbol_float, BinaryOperator::Exp, symbol_int, Runtime::Operation<float, int, float, Runtime::Exp>(symbol_float));

    define(symbol_int, BinaryOperator::EQ, symbol_float, Runtime::Operation<int, float, bool, Runtime::EQ>(symbol_bool));
    define(symbol_float, BinaryOperator::EQ, symbol_int, Runtime::Operation<float, int, bool, Runtime::EQ>(symbol_bool));
    define(symbol_int, BinaryOperator::NE, symbol_float, Runtime::Operation<int, float, bool, Runtime::NE>(symbol_bool));
    define(symbol_float, BinaryOperator::NE, symbol_int, Runtime::Operation<float, int, bool, Runtime::NE>(symbol_bool));
    define(symbol_int, BinaryOperator::LT, symbol_float, Runtime::Operation<int, float, bool, Runtime::LT>(symbol_bool));
    define(symbol_float, BinaryOperator::LT, symbol_int, Runtime::Operation<float, int, bool, Runtime::LT>(symbol_bool));
    define(symbol_int, BinaryOperator::LE, symbol_float, Runtime::Operation<int, float, bool, Runtime::LE>(symbol_bool));
    define(symbol_float, BinaryOperator::LE, symbol_int, Runtime::Operation<float, int, bool, Runtime::LE>(symbol_bool));
    define(symbol_int, BinaryOperator::GE, symbol_float, Runtime::Operation<int, float, bool, Runtime::GE>(symbol_bool));
    define(symbol_float, BinaryOperator::GE, symbol_int, Runtime::Operation<float, int, bool, Runtime::GE>(symbol_bool));
    define(symbol_int, BinaryOperator::GT, symbol_float, Runtime::Operation<int, float, bool, Runtime::GT>(symbol_bool));
    define(symbol_float, BinaryOperator::GT, symbol_int, Runtime::Operation<float, int, bool, Runtime::GT>(symbol_bool));


    // Bool operations
    define(symbol_bool, BinaryOperator::And, symbol_bool, Runtime::Operation<bool, bool, bool, Runtime::And>(symbol_bool));
    define(symbol_bool, BinaryOperator::Or, symbol_bool, Runtime::Operation<bool, bool, bool, Runtime::Or>(symbol_bool));
    define(symbol_bool, BinaryOperator::Xor, symbol_bool, Runtime::Operation<bool, bool, bool, Runtime::Xor>(symbol_bool));
}



template <>
int Tomato::Runtime::Exp(const int &left, const int &right)
{
    int base = left, exp = right, pow = 1;

    int k = 0;

    while (exp > 0)
    {
        exp >>= 1;
        k++;
    }
    exp = right;

    for (int i = k-1; i >= 0; --i)
    {
        pow *= pow;

        if (exp & (1 << i))
            pow *= base;
    }

    return pow;
};
