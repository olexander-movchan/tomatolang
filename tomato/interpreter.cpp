#include "interpreter.hpp"

#include <iostream>

#include <readline/readline.h>
#include <readline/history.h>

#include "syntax/parser.hpp"
#include "syntax/printer.hpp"


using namespace Tomato;


Interpreter::Interpreter(std::istream &istream, std::ostream &ostream) : istream(istream), ostream(ostream) {}


void Interpreter::run()
{
    Syntax::Parser parser;
    Syntax::Printer printer(ostream);

    char const * const prompt = ">>> ";

    while (true)
    {
        char * line = readline(prompt);

        if (line == nullptr) // EOF reached
        {
            ostream << std::endl;
            break;
        }
        else if (line[0] == '\0') // Line is empty
        {
            continue;
        }

        // save readline history
        add_history(line);
        parser.set_text(line);
        free(line);


        try
        {
            auto tree = parser.parse();
            printer.print(*tree);
            std::cout << std::endl;
        }
        catch (Syntax::SyntaxError &error)
        {
            std::cout << error.what() << std::endl;
        }
    }
}
