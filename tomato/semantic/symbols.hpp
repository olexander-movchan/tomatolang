#ifndef TOMATO_SYMBOLS_HPP
#define TOMATO_SYMBOLS_HPP


#include <cstddef>


namespace Tomato::Semantic
{
    class Symbol
    {
    public:
        Symbol();
        virtual ~Symbol() = default;

    private:
        size_t id;
        static size_t NextID;
    };

    class Type : public Symbol {};

    class Value : public Symbol
    {
    public:
        explicit Value(Type type, bool is_constant = false);

        Type type();
        bool is_constant();

    private:
        Type m_type;
        bool m_constant;
    };
}


#endif //TOMATO_SYMBOLS_HPP
