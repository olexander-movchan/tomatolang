#include <iostream>
#include "interpreter.hpp"

int main(int argc, char **argv)
{
    std::string line;

    while (std::cin)
    {
        std::cout << "calc> ";
        std::getline(std::cin, line);

        Interpreter interpreter(line);

        std::cout << interpreter.run() << std::endl;
    }
}
