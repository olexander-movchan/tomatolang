#ifndef TOMATO_NAVIGATOR_HPP
#define TOMATO_NAVIGATOR_HPP


#include <stack>
#include "codepoint.hpp"


namespace Tomato
{
    /**
     * Stack-based code navigator.
     */
    class CodeNavigator
    {
    public:
        explicit CodeNavigator(const CodePoint & point = CodePoint{});
        void push();

        void push(const CodePoint &point);
        void move(const CodePoint &point);

        CodePoint pop();
        CodePoint & top();

    private:
        std::stack<CodePoint> points;
    };
}

#endif //TOMATO_NAVIGATOR_HPP
