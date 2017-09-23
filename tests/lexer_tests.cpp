#include <gtest/gtest.h>
#include <syntax/lexer.hpp>


using namespace std::string_literals;
using namespace Tomato;


TEST(LexerTest, GeneralTest)
{
    auto code = "2 + 2 * 2"s;
    Lexer lexer;

    lexer.append(code);

    ASSERT_EQ(lexer.next_token().type, Tomato::Token::Type::Literal);
    ASSERT_EQ(lexer.next_token().type, Tomato::Token::Type::Add);
    ASSERT_EQ(lexer.next_token().type, Tomato::Token::Type::Literal);
    ASSERT_EQ(lexer.next_token().type, Tomato::Token::Type::Mul);
    ASSERT_EQ(lexer.next_token().type, Tomato::Token::Type::Literal);

    ASSERT_EQ(lexer.next_token().type, Tomato::Token::Type::EndOfFile);
    ASSERT_EQ(lexer.next_token().type, Tomato::Token::Type::EndOfFile);
    ASSERT_EQ(lexer.next_token().type, Tomato::Token::Type::EndOfFile);

    ASSERT_EQ(lexer.next_token().location.column, code.length());
}


TEST(LexerTest, AppendAndReset)
{
    Lexer lexer;

    lexer.reset("2 + 2");

    ASSERT_EQ(lexer.next_token().type, Token::Type::Literal);
    ASSERT_EQ(lexer.next_token().type, Token::Type::Add);
    ASSERT_EQ(lexer.next_token().type, Token::Type::Literal);

    lexer.reset("var a = 2");

}
