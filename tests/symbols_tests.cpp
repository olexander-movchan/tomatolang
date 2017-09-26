#include <gtest/gtest.h>
#include <semantic/symbols.hpp>
#include <errors.hpp>


using namespace std::string_literals;
using namespace Tomato;


TEST(SymbolTableTest, GeneralTest)
{
    CodeNavigator navigator;
    SymbolTable symbols(navigator);

    ASSERT_NO_THROW(symbols.define(Symbol("foo")));
    ASSERT_NO_THROW(symbols.define(Symbol("bar")));
    ASSERT_NO_THROW(symbols.define(Symbol("foobar")));

    ASSERT_THROW(symbols.define(Symbol("foo")), NameError);

    ASSERT_NO_THROW(symbols.lookup("foo"));
    ASSERT_NO_THROW(symbols.lookup("bar"));

    ASSERT_THROW(symbols.lookup("baz"), NameError);
}
