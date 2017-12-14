#include <iostream>
#include "interpreter.hpp"


int main(int argc, char **argv)
{
    Tomato::Interpreter interpreter(std::cin, std::cout);
    interpreter.run();

    return 0;
}
