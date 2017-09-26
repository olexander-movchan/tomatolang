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

    lexer.append("2 + 2");

    ASSERT_EQ(lexer.next_token().type, Token::Type::Literal);
    ASSERT_EQ(lexer.next_token().type, Token::Type::Add);
    ASSERT_EQ(lexer.next_token().type, Token::Type::Literal);

    lexer.append("var a = 2");

    ASSERT_EQ(lexer.next_token().type, Token::Type::Literal);
    ASSERT_EQ(lexer.next_token().type, Token::Type::Add);
    ASSERT_EQ(lexer.next_token().type, Token::Type::Literal);
    ASSERT_EQ(lexer.next_token().type, Token::Type::Var);

    lexer.reset("print a");

    ASSERT_EQ(lexer.next_token().type, Token::Type::Print);
}


TEST(LexerTest, Navigation)
{
    Lexer lexer;

    lexer.append("var a = 0\nvar b = 1\n");

    ASSERT_EQ(lexer.next_token().location, (CodePoint {0, 0}));
    ASSERT_EQ(lexer.next_token().location, (CodePoint {0, 4}));
    ASSERT_EQ(lexer.next_token().location, (CodePoint {0, 6}));
    ASSERT_EQ(lexer.next_token().location, (CodePoint {0, 8}));
    ASSERT_EQ(lexer.next_token().location, (CodePoint {1, 0}));
    ASSERT_EQ(lexer.next_token().location, (CodePoint {1, 4}));
    ASSERT_EQ(lexer.next_token().location, (CodePoint {1, 6}));
    ASSERT_EQ(lexer.next_token().location, (CodePoint {1, 8}));

    lexer.reset("print foo");
    ASSERT_EQ(lexer.next_token().location, (CodePoint {0, 0}));
}
