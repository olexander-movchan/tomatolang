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

    std::string code;

    while (true)
    {
        char * line = readline(prompt);

        if (line == nullptr) // EOF reached
        {
            std::cout << std::endl;
            break;
        }
        else if (line[0] == '\0') // Line is empty
        {
            continue;
        }

        // save readline history
        add_history(line);
        code += line;
        free(line);

        parser.set_text(code);

        try
        {
            auto tree = parser.statement_block();
            printer.print(*tree);
            code.clear();
        }
        catch (SyntaxError &error)
        {
            if (parser.eof())
            {
                continue;
            }
            else
            {
                std::clog << error.what() << std::endl;
                code.clear();
            }
        }
    }

    return 0;
}
