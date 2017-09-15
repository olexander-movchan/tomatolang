#include <gtest/gtest.h>

#include <syntax/lexer.hpp>


TEST(Lexer__Test, Simple_Test)
{
    Tomato::Lexer lexer("var a = 0");

    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::Var);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::Identifier);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::Assign);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::Literal);

    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::EndOfFile);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::EndOfFile);
    ASSERT_EQ(lexer.next().type, Tomato::Token::Type::EndOfFile);

    ASSERT_EQ(lexer.next().position, (Tomato::CodePoint {0, 9}));
}
