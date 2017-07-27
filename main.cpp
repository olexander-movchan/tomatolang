#include <iostream>

#include "interpreter.hpp"


int main(int argc, char **argv)
{
    Interpreter interpreter;
    std::string line;

    while (std::cin)
    {
        std::cout << "ti> ";
        std::getline(std::cin, line);

        if (line.length() == 0 || line == "exit")
            break;

        interpreter.run(line);
    }

    interpreter.print_state();

    return 0;
}
