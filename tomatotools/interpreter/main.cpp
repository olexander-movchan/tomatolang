#include <iostream>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

#include "syntax/parser.hpp"
#include "interpreter.hpp"


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

        code = code + line + "\n";
        code_history.push_back(line);
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

            std::cout << "\n" << error.what() << " at line "
                      << error.token.position.line << ", column "
                      << error.token.position.column << ":\n\n";

            std::cout << code_history[error.token.position.line - 1] << '\n';

            for (int i = 1; i < error.token.position.column; ++i)
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
