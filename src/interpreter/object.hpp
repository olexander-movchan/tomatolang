#ifndef TOMATO_RUNTIME_OBJECT_HPP
#define TOMATO_RUNTIME_OBJECT_HPP


#include <any>

#include "semantic/symtab.hpp"


namespace Tomato::Runtime
{
    class Object
    {
    public:
        explicit Object(Semantic::Symbol type, bool is_mutable);
        virtual ~Object() = default; // make Object polymorphic type

        virtual void assign(const Object &) = 0;
        virtual std::shared_ptr<Object> clone() = 0;

        Semantic::Symbol type;
        bool is_mutable;
    };

    template <typename T>
    class Scalar : public Object
    {
    public:
        Scalar(Semantic::Symbol type, const T &value, bool is_mutable);

        void assign(const Object &object) override;

        std::shared_ptr<Object> clone() override;

        T value;
    };

    extern template class Scalar<int>;
    extern template class Scalar<float>;
    extern template class Scalar<bool>;
}


#endif //TOMATOLANG_OBJECT_HPP
