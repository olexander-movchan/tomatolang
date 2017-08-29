#include "object.hpp"


using namespace Tomato;

/*
 * Any Object subclass doesn't have to override all of this methods,
 * but invoking not overloaded one should cause the type error.
 */

Object::Ref Object::add(const Object &object) { throw TypeError(); }
Object::Ref Object::sub(const Object &object) { throw TypeError(); }
Object::Ref Object::mul(const Object &object) { throw TypeError(); }
Object::Ref Object::div(const Object &object) { throw TypeError(); }
Object::Ref Object::exp(const Object &object) { throw TypeError(); }

Object::Ref Object::un_minus() { throw TypeError(); }
Object::Ref Object::un_plus() { throw TypeError(); }

Object::Ref Object::lt(const Object &object) { throw TypeError(); }
Object::Ref Object::gt(const Object &object) { throw TypeError(); }
Object::Ref Object::le(const Object &object) { throw TypeError(); }
Object::Ref Object::ge(const Object &object) { throw TypeError(); }
Object::Ref Object::eq(const Object &object) { throw TypeError(); }
Object::Ref Object::ne(const Object &object) { throw TypeError(); }

Object::Ref Object::op_not() { throw TypeError(); }

Object::Ref Object::op_and(const Object &object) { throw TypeError(); }
Object::Ref Object::op_or (const Object &object) { throw TypeError(); }
