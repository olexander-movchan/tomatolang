#ifndef TOMATO_INTERPRETER_HPP
#define TOMATO_INTERPRETER_HPP


#include <ios>

#include "syntax/visitor.hpp"
#include "syntax/syntax_tree.hpp"


namespace Tomato
{
    class Interpreter // : private Syntax::Visitor
    {
    public:
        Interpreter(std::istream &istream, std::ostream &ostream);

        void run();

    private:
        std::istream &istream;
        std::ostream &ostream;
    };
}


#endif //TOMATO_INTERPRETER_HPP
