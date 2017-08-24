#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

#include "parser/parser.hpp"
#include "interpreter/interpreter.hpp"


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

        code += line;
        free(line);

        try
        {
            auto ast = parser.parse(code);

            interpreter.interpret(ast);

            code.clear();
            PS = PS1;
        }
        catch (const CodeError &error)
        {
            if (error.token.type == Token::Type::EndOfFile)
            {
                PS = PS2;
                continue;
            }

            std::cout << error.what() << std::endl;
        }
    }

    return 0;
}
