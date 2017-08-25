#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

#include "syntax/parser.hpp"
#include "interpreter.hpp"


int main(int argc, char **argv)
{
    Parser parser;
    Interpreter interpreter;

    std::string code;

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

        code = code + line + "\n";
        free(line);

        try
        {
            auto ast = parser.parse(code);

            interpreter.interpret(ast);
        }
        catch (const CodeError &error)
        {
            if (error.token.type == Token::Type::EndOfFile)
            {
                PS = PS2;
                continue;
            }

            std::cout << "Oops, there was an error!" << std::endl;
        }
        catch (const InterpretationError &error)
        {
            std::cout << "Oops, there was an error!" << std::endl;
        }

        code.clear();
        PS = PS1;
    }

    return 0;
}
