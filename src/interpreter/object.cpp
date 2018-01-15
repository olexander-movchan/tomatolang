#include "object.hpp"


using namespace Tomato::Semantic;
using namespace Tomato::Runtime;


Object::Object(Semantic::Symbol type, bool is_mutable) : type(type), is_mutable(is_mutable) {}


template<typename T>
Scalar<T>::Scalar(Semantic::Symbol type, const T &value, bool is_mutable) : Object(type, is_mutable), value(value) {}

template<typename T>
void Scalar<T>::assign(const Object &object)
{
    if (!is_mutable)
        throw SemanticError("assigning to constant object");

    try
    {
        value = dynamic_cast<const Scalar<T> &>(object).value;
    }
    catch (std::bad_cast &)
    {
        throw SemanticError("assigning different types");
    }
}

template<typename T>
std::shared_ptr<Object> Tomato::Runtime::Scalar<T>::clone()
{
    return std::make_shared<Scalar<T>>(type, value, is_mutable);
}


template class Scalar<int>;
template class Scalar<float>;
template class Scalar<bool>;
template class Scalar<char>;
