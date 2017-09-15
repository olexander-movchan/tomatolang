#include <iostream>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

#include "syntax/parser.hpp"
#include "interpreter.hpp"


using namespace Tomato;
using std::literals::operator""s;


int main(int argc, char **argv)
{
    Parser parser;
    Interpreter interpreter;

    std::string code;
    std::vector<std::string> code_history;

    char const * const PS1 = ">>> ";
    char const * const PS2 = "... ";

    char const * PS = PS1;

    while (true)
    {
        char * line = readline(PS);

        if (line == nullptr) // EOF reached
        {
            std::cout << std::endl;
            break;
        }
        else if (*line) // Not empty
        {
            add_history(line);
        }

        code += line + "\n"s;
        code_history.emplace_back(line);
        free(line);

        try
        {
            auto ast = parser.parse(code);

            interpreter.interpret(ast);
        }
        catch (const CodeError &error)
        {
            if (error.location.line == code_history.size())
            {
                PS = PS2;
                continue;
            }

            std::cout << "\n" << error.what() << " at line "
                      << error.location.line + 1 << ", column "
                      << error.location.column + 1 << ":\n\n";

            std::cout << code_history[error.location.line] << '\n';

            for (int i = 0; i < error.location.column; ++i)
            {
                std::cout << ' ';
            }

            std::cout << "^\n" << std::endl;
        }
        catch (const InterpretationError &error)
        {
            std::cout << "Oops, there was an error!" << std::endl;
        }

        code.clear();
        code_history.clear();
        PS = PS1;
    }

    return 0;
}
