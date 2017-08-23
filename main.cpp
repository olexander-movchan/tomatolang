#include <iostream>

#include "parser/parser.hpp"
#include "interpreter/interpreter.hpp"


int main(int argc, char **argv)
{
    Parser parser;
    Interpreter interpreter;

    std::string code, line;

    char const * const PS1 = ">>> ";
    char const * const PS2 = "... ";

    char const * PS = PS1;

    while (std::cin)
    {
        std::cout << PS;
        std::getline(std::cin, line);
        code += line;

        try
        {
            auto ast = parser.parse(code);

            interpreter.interpret(ast);

            code.clear();
            PS = PS1;
        }
        catch (const CodeError &error)
        {
            if (error.token.type == Token::Type::EndOfFile && std::cin)
            {
                PS = PS2;
                continue;
            }

            std::cout << error.what() << std::endl;
        }
    }

    return 0;
}
