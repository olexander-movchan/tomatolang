#include <iostream>
#include <vector>

#include <readline/readline.h>
#include <readline/history.h>

#include "lexer.hpp"


using namespace Tomato::Syntax;


int main(int argc, char **argv)
{
    Lexer lexer;

    char const * const prompt = ">>> ";

    while (true)
    {
        char * line = readline(prompt);

        if (line == nullptr) // EOF reached
        {
            std::cout << std::endl;
            break;
        }
        else if (*line) // Not empty
        {
            add_history(line);
        }

        lexer.reset(line);
        free(line);

        while (!lexer.eof())
        {
            try
            {
                std::cout << to_string(lexer.get_next()) << std::endl;
            }
            catch (InvalidToken &error)
            {
                std::cout << error.what() << std::endl;
            }
        }
    }

    return 0;
}
