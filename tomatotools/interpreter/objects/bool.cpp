#include "bool.hpp"


using namespace Tomato;


Bool::Bool(bool value) : value(value) {}


void Bool::assign(const Object &object)
{
    if (!object.is_instance<Bool>())
        throw TypeError();

    value = object.as<Bool>().value;
}


std::string Bool::str()
{
    return value ? "true" : "false";
}


Object::Ref Bool::op_not()
{
    return std::make_shared<Bool>(!value);
}


Object::Ref Bool::op_and(const Object &object)
{
    if (!object.is_instance<Bool>())
        throw TypeError();

    return std::make_shared<Bool>(value && object.as<Bool>().value);
}


Object::Ref Bool::op_or(const Object &object)
{
    if (!object.is_instance<Bool>())
        throw TypeError();

    return std::make_shared<Bool>(value || object.as<Bool>().value);
}

Object::Ref Bool::True()
{
    return std::make_shared<Bool>(true);
}

Object::Ref Bool::False()
{
    return std::make_shared<Bool>(false);
}
