#include <iostream>
#include <fstream>
#include "interpreter/interpreter.hpp"


int main(int argc, char **argv)
{
    if (argc == 1)
    {
        Tomato::Interpreter interpreter(std::cin, std::cout);
        interpreter.run();
    }
    else if (argc == 2)
    {
        std::ifstream file(argv[1]);

        if (!file.is_open())
        {
            std::clog << "Can't open file '" << argv[1] << '\'' << std::endl;
            return 0;
        }

        Tomato::Interpreter interpreter(std::cin, std::cout);
        interpreter.interpret(file);
    }
    else
    {
        std::cout << "Usage:\n\n"
                  << "    tomato [file]\n\n"
                  << "If file is provided it will be interpreted, otherwise interpreter will start interactive session";
    }

    return 0;
}
