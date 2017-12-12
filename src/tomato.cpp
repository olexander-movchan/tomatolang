#include <iostream>
#include <vector>

#include <readline/readline.h>
#include <readline/history.h>

#include "lexer.hpp"
#include "parser.hpp"
#include "printer.hpp"


using namespace Tomato::Syntax;


int main(int argc, char **argv)
{
    Parser parser;
    Printer printer(std::cout);

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

        parser.reset(line);
        free(line);

        auto tree = parser.expression();
        printer.print(*tree);
    }

    return 0;
}
