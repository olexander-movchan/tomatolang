#include <iostream>

#include "interpreter/interpreter.hpp"


int main(int argc, char **argv)
{
    Interpreter interpreter;
    std::string line;

    static const char * const PROMPT = ">>> ";

    while (std::cin)
    {
        std::cout << PROMPT;
        std::getline(std::cin, line);

        try
        {
            interpreter.interpret(line);
        }
        catch (const TypeError &error)
        {
            std::cout << "Type Error!" << std::endl;
        }
        catch (const CodeError &error)
        {
            std::cout << error.what() << std::endl;
            std::cout << line << std::endl;
            for (int i = 0; i < error.token.position; ++i)
            {
                std::cout << ' ';
            }
            std::cout << "^\n" << std::endl;
        }
        catch (const RuntimeError &error)
        {
            std::cout << error.what() << std::endl;
        }
    }

    return 0;
}
