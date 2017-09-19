#include <gtest/gtest.h>
#include <syntax/lexer.hpp>


using namespace std::string_literals;


TEST(Lexer__Test, Simple_Test)
{
    auto code = "var a = 0"s;
    Tomato::Lexer lexer(code);

    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::Var);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::Identifier);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::Assign);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::Literal);

    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::EndOfFile);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::EndOfFile);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::EndOfFile);

    ASSERT_EQ(lexer.next().position.column, code.length());
}
