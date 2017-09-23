#include <stdexcept>
#include "navigator.hpp"


using namespace Tomato;


CodeNavigator::CodeNavigator(const CodePoint &point)
{
    points.push(point);
}


CodePoint & CodeNavigator::top()
{
    return points.top();
}


void CodeNavigator::push()
{
    points.push(points.top());
}


void CodeNavigator::push(const CodePoint &point)
{
    points.push(point);
}


void CodeNavigator::move(const CodePoint &point)
{
    points.top() = point;
}


CodePoint CodeNavigator::pop()
{
    auto tmp = points.top();
    points.pop();

    if (points.empty())
        throw std::underflow_error("Navigation stack become empty");

    return tmp;
}
