#ifndef TOMATOLANG_OPERATIONS_HPP
#define TOMATOLANG_OPERATIONS_HPP


#include <functional>
#include <cmath>

#include "object.hpp"
#include "operators.hpp"


namespace Tomato::Runtime
{
    using BinaryOperation = std::function<std::shared_ptr<Object>(const Object &, const Object &)>;
    using UnaryOperation = std::function<std::shared_ptr<Object>(const Object &)>;


    class UndefinedOperation : public std::runtime_error
    {
    public:
        using runtime_error::runtime_error;
    };


    class Operations
    {
    public:
        void init_builtins(Semantic::Symbol symbol_int, Semantic::Symbol symbol_float, Semantic::Symbol symbol_bool);

        void define(Semantic::Symbol ltype, BinaryOperator op, Semantic::Symbol rtype, const BinaryOperation &definition);
        void define(UnaryOperator op, Semantic::Symbol type, const UnaryOperation &definition);

        const BinaryOperation & lookup(Semantic::Symbol ltype, BinaryOperator op, Semantic::Symbol rtype);
        const UnaryOperation & lookup(UnaryOperator op, Semantic::Symbol type);

    private:
        std::map<std::tuple<Semantic::Symbol, BinaryOperator, Semantic::Symbol>, BinaryOperation> binary_operations;
        std::map<std::tuple<UnaryOperator, Semantic::Symbol>, UnaryOperation> unary_operations;
    };


#define ARITHMETIC_OPERATION(NAME, OPERATOR) \
    template <typename L, typename R, typename G> \
    G NAME(const L &left, const R &right) { return G(left) OPERATOR G(right); }

    ARITHMETIC_OPERATION(Sum, +)
    ARITHMETIC_OPERATION(Sub, -)
    ARITHMETIC_OPERATION(Mul, *)
    ARITHMETIC_OPERATION(Div, /)
    ARITHMETIC_OPERATION(Mod, %)


    template <typename L, typename R, typename G>
    G Exp(const L &left, const R &right) { return std::pow(G(left), G(right)); }

    template <>
    int Exp(const int &left, const int &right);


#undef ARITHMETIC_OPERATION


#define COMARISON_OPERATION(NAME, OPERATOR) \
    template <typename L, typename R, typename G=bool> \
    bool NAME(const L &left, const R &right) { \
        static_assert(std::is_same<bool, G>::value, "Comparison must return bool"); \
        return left OPERATOR right; \
    }

    COMARISON_OPERATION(EQ, ==)
    COMARISON_OPERATION(NE, !=)
    COMARISON_OPERATION(LT, <)
    COMARISON_OPERATION(LE, <=)
    COMARISON_OPERATION(GE, >=)
    COMARISON_OPERATION(GT, >)

#undef COMARISON_OPERATION


#define BOOLEAN_OPERATION(NAME, OPERATOR) \
    template <typename L, typename R, typename G=bool> \
    bool NAME(const L &left, const R &right) { \
        static_assert(std::is_same<bool, L>::value, "Boolean operation accept only boolean operand"); \
        static_assert(std::is_same<bool, R>::value, "Boolean operation accept only boolean operand"); \
        static_assert(std::is_same<bool, G>::value, "Boolean operation produces boolean value"); \
        return left OPERATOR right; \
    }

    BOOLEAN_OPERATION(And, &&)
    BOOLEAN_OPERATION(Or, ||)
    BOOLEAN_OPERATION(Xor, !=)

#undef BOOLEAN_OPERATION

    template <typename L, typename R, typename G, G (*Op) (const L&, const R&)>
    class Operation
    {
    public:
        explicit Operation(Semantic::Symbol type_symbol) : type_symbol(type_symbol) {}

        std::shared_ptr<Object> operator() (const Object &left, const Object &right)
        {
            try
            {
                return std::make_shared<Scalar<G>>(
                        type_symbol,
                        Op(dynamic_cast<const Scalar<L> &>(left).value,
                           dynamic_cast<const Scalar<R> &>(right).value),
                        false
                );
            }
            catch (std::bad_cast &)
            {
                throw std::logic_error("internal interpreter error");
            }
        }
    private:
        Semantic::Symbol type_symbol;
    };
}


#endif //TOMATOLANG_OPERATIONS_HPP
