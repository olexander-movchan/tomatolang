#include <gtest/gtest.h>
#include <syntax/parser.hpp>


TEST(ParserTest, Expressions)
{
    using namespace Tomato::Syntax;

    Parser parser;

    parser.set_text("var pi = let");
}
