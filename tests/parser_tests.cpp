#include <gtest/gtest.h>
#include <parser.hpp>


TEST(ParserTest, Expressions)
{
    using namespace Tomato::Syntax;

    Parser parser;

    parser.set_text("var pi = let");

    auto tree = parser.statement_block();
}
