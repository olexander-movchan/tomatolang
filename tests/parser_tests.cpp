#include <gtest/gtest.h>
#include <syntax/parser.hpp>


using namespace Tomato;


TEST(Parser__Test, SimpleTest)
{
    Parser parser = Parser();

    auto p1 = parser.parse("2 + 2 * 2");
    auto p2 = parser.parse("2 * 2 + 2");
    auto expr_a = p1->statements.front().get();
    auto expr_b = p2->statements.front().get();

    ASSERT_NO_THROW(dynamic_cast<AST::BinaryOperatorNode &>(*expr_a));
    ASSERT_NO_THROW(dynamic_cast<AST::BinaryOperatorNode &>(*expr_b));

    ASSERT_EQ(Token::Type::Add, dynamic_cast<AST::BinaryOperatorNode *>(expr_a)->operation);
    ASSERT_EQ(Token::Type::Add, dynamic_cast<AST::BinaryOperatorNode *>(expr_b)->operation);
}
