#ifndef TOMATO_OVERLOADING_HPP
#define TOMATO_OVERLOADING_HPP


#include "symbols.hpp"
#include "operators.hpp"


namespace Tomato::Semantic
{

    class Overloading
    {
    public:
        void define_operation(Type left, BinaryOperator op, Type right);
    };
}


#endif //TOMATO_OVERLOADING_HPP
