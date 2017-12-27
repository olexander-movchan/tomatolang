#include "object.hpp"


using namespace Tomato::Semantic;
using namespace Tomato::Runtime;


Object::Object(Semantic::Symbol type) : type(type) {}


template<typename T>
Scalar<T>::Scalar(Semantic::Symbol type, const T &value) : Object(type), value(value) {}

template<typename T>
void Scalar<T>::assign(const Object &object)
{
    try
    {
        value = dynamic_cast<const Scalar<T> &>(object).value;
    }
    catch (std::bad_cast &)
    {
        throw SemanticError("assigning different types");
    }
}


template class Scalar<int>;
template class Scalar<float>;
template class Scalar<bool>;
