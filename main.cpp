#include <iostream>

#include "interpreter.hpp"


int main(int argc, char **argv)
{
    Interpreter interpreter;
    std::string line;

    static const char * const PROMPT = ">>> ";

    while (std::cin)
    {
        std::cout << PROMPT;
        std::getline(std::cin, line);

        if (line == "print")
        {
            interpreter.print_state();
            continue;
        }

        interpreter.interpret(line);
    }

    return 0;
}
