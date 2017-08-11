#include <iostream>

#include "interpreter/interpreter.hpp"
#include "parser/error.hpp"


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

        try
        {
            interpreter.interpret(line);
        }
        catch (const SyntaxError &error)
        {
            std::cout << error.what() << std::endl;
        }
        catch (const RuntimeError &error)
        {
            std::cout << error.what() << std::endl;
        }
        catch (TypeError)
        {
            std::cout << "Incompatible types!" << std::endl;
        }
    }

    return 0;
}
