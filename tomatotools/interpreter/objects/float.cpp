#include "float.hpp"
#include "integer.hpp"
#include "bool.hpp"

#include <cmath>


Float::Float(float value) : value(value) {}


void Float::assign(const Object &object)
{
    if (object.is_instance<Float>())
        value = object.as<Float>().value;

    else if (object.is_instance<Integer>())
        value = object.as<Integer>().value;

    else
        throw TypeError();
}


std::string Float::str()
{
    return std::to_string(value);
}


Object::Ref Float::add(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Float>(value + object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Float>(value + object.as<Integer>().value);

    else
        throw TypeError();
}


Object::Ref Float::sub(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Float>(value - object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Float>(value - object.as<Integer>().value);

    else
        throw TypeError();

}

Object::Ref Float::mul(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Float>(value * object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Float>(value * object.as<Integer>().value);

    else
        throw TypeError();
}

Object::Ref Float::div(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Float>(value / object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Float>(value / object.as<Integer>().value);

    else
        throw TypeError();
}

Object::Ref Float::exp(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Float>(std::pow(value, object.as<Float>().value));

    else if (object.is_instance<Integer>())
        return std::make_shared<Float>(std::pow(value, float(object.as<Integer>().value)));

    else
        throw TypeError();
}

Object::Ref Float::un_plus()
{
    return std::make_shared<Float>(+value);
}

Object::Ref Float::un_minus(){
    return std::make_shared<Float>(-value);
}


Object::Ref Float::lt(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Bool>(value < object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Bool>(value < object.as<Integer>().value);

    else
        throw TypeError();
}


Object::Ref Float::gt(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Bool>(value > object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Bool>(value > object.as<Integer>().value);

    else
        throw TypeError();
}


Object::Ref Float::le(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Bool>(value <= object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Bool>(value <= object.as<Integer>().value);

    else
        throw TypeError();
}


Object::Ref Float::ge(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Bool>(value >= object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Bool>(value >= object.as<Integer>().value);

    else
        throw TypeError();
}


Object::Ref Float::eq(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Bool>(value == object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Bool>(value == object.as<Integer>().value);

    else
        throw TypeError();
}


Object::Ref Float::ne(const Object &object)
{
    if (object.is_instance<Float>())
        return std::make_shared<Bool>(value != object.as<Float>().value);

    else if (object.is_instance<Integer>())
        return std::make_shared<Bool>(value != object.as<Integer>().value);

    else
        throw TypeError();
}
