#include <gtest/gtest.h>
#include <syntax/navigator.hpp>


using namespace std::string_literals;
using namespace Tomato;


TEST(CodeNavigatorTest, GeneralTest)
{
    CodeNavigator navigator;
    CodePoint O = {0, 0};
    ASSERT_EQ(navigator.top(), O);
    ASSERT_EQ(navigator.top(), O);

    CodePoint A = {2, 42};
    navigator.push(A);

    ASSERT_EQ(navigator.top(), A);

    navigator.push();

    ASSERT_EQ(navigator.top(), A);

    CodePoint B = {3, 4};
    navigator.move(B);

    ASSERT_EQ(navigator.top(), B);
    ASSERT_EQ(navigator.pop(), B);

    ASSERT_EQ(navigator.top(), A);
    ASSERT_EQ(navigator.pop(), A);

    ASSERT_EQ(navigator.top(), O);

    ASSERT_THROW(navigator.pop(), std::underflow_error);
}
