#include "object.hpp"


using namespace Tomato::Semantic;
using namespace Tomato::Runtime;


Object::Object(Semantic::Symbol type) : type(type) {}


template<typename T>
Scalar<T>::Scalar(Semantic::Symbol type, const T &value) : Object(type), value(value) {}


template class Scalar<int>;
template class Scalar<float>;
template class Scalar<bool>;
