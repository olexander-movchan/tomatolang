#include "symbols.hpp"


using namespace Tomato::Semantic;


Symbol::Symbol() : id(NextID++) {}
size_t Symbol::NextID = 0;


Value::Value(Type type, bool is_constant) : m_type(type), m_constant(is_constant) {}


bool Value::is_constant()
{
    return m_constant;
}


Type Value::type()
{
    return m_type;
}
