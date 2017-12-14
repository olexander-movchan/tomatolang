#include <gtest/gtest.h>
#include <semantic/symtab.hpp>



TEST(SymbolTableTest, GeneralTest)
{
    SymbolTable symtab;

    symtab.push_scope("__builtin__");

    symtab.define_symbol("int", Type());
    symtab.define_symbol("float", Type());
    symtab.define_symbol("bool", Type());

    symtab.push_scope("__global__");
}
