#include <cmath>
#include "types.hpp"
#include "interpreter.hpp"


char const * const IncomatibleTypesMessage = "Operation with incompatible types";


//
// Integer
//


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


void Integer::set(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        value = obj.value;
    }
    catch (std::bad_cast)
    {
        throw RuntimeError(IncomatibleTypesMessage);
    }
}


std::string Integer::str()
{
    return std::to_string(value);
}


Object::Ref Integer::add(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Integer>(value + obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(value + obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}


Object::Ref Integer::sub(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Integer>(value - obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(value - obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}


Object::Ref Integer::mul(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Integer>(value * obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(value * obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}


Object::Ref Integer::div(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Float>(float(value) / obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(value / obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}


Object::Ref Integer::pow(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Integer>(ipow(value, obj.value));
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(std::pow(float(value), obj.value));
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);}


Object::Ref Integer::opposite()
{
    return std::make_shared<Integer>(-value);
}


//
// Float
//

Float::Float(float value) : value(value) {}


void Float::set(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        value = obj.value;
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        value = float(obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}


std::string Float::str()
{
    return std::to_string(value);
}


Object::Ref Float::add(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(value + obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Float>(value + obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}


Object::Ref Float::sub(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(value - obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Float>(value - obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);

}

Object::Ref Float::mul(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(value * obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Float>(value * obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}

Object::Ref Float::div(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(value / obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Float>(value / obj.value);
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}

Object::Ref Float::pow(const Object &object)
{
    try
    {
        auto obj = dynamic_cast<const Float&>(object);

        return std::make_shared<Float>(std::pow(value, obj.value));
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    try
    {
        auto obj = dynamic_cast<const Integer&>(object);

        return std::make_shared<Float>(std::pow(value, float(obj.value)));
    }
    catch (std::bad_cast)
    {
        // Do nothing
    }

    throw RuntimeError(IncomatibleTypesMessage);
}

Object::Ref Float::opposite()
{
    return std::make_shared<Float>(-value);
}
