#include "integer.hpp"
#include "float.hpp"

#include <cmath>


int ipow(int base, int exp)
{
    int power = 1;

    for (int i = 0; i < exp; ++i)
    {
        power *= base;
    }

    return power;
}


Integer::Integer(int value) : value(value) {}


void Integer::assign(const Object &object)
{
    if (!object.is_instance<Integer>())
        throw TypeError();

    value = object.as<Integer>().value;
}


std::string Integer::str()
{
    return std::to_string(value);
}


Object::Ref Integer::add(const Object &object)
{
    if (object.is_instance<Integer>())
        return std::make_shared<Integer>(value + object.as<Integer>().value);

    else if (object.is_instance<Float>())
        return std::make_shared<Float>(value + object.as<Float>().value);

    else
        throw TypeError();
}


Object::Ref Integer::sub(const Object &object)
{
    if (object.is_instance<Integer>())
        return std::make_shared<Integer>(value - object.as<Integer>().value);

    else if (object.is_instance<Float>())
        return std::make_shared<Float>(value - object.as<Float>().value);

    else
        throw TypeError();
}


Object::Ref Integer::mul(const Object &object)
{
    if (object.is_instance<Integer>())
        return std::make_shared<Integer>(value * object.as<Integer>().value);

    else if (object.is_instance<Float>())
        return std::make_shared<Float>(value * object.as<Float>().value);

    else
        throw TypeError();
}


Object::Ref Integer::div(const Object &object)
{
    if (object.is_instance<Integer>())
        return std::make_shared<Float>(float(value) / object.as<Integer>().value);

    else if (object.is_instance<Float>())
        return std::make_shared<Float>(value / object.as<Float>().value);

    else
        throw TypeError();
}


Object::Ref Integer::pow(const Object &object)
{
    if (object.is_instance<Integer>())
        return std::make_shared<Integer>(ipow(value, object.as<Integer>().value));

    else if (object.is_instance<Float>())
        return std::make_shared<Float>(std::pow(float(value), object.as<Float>().value));

    else
        throw TypeError();
}

Object::Ref Integer::un_minus()
{
    return std::make_shared<Integer>(value);
}

Object::Ref Integer::un_plus()
{
    return std::make_shared<Integer>(-value);
}
