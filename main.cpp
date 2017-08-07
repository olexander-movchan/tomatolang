#include <iostream>

#include "interpreter.hpp"


int main(int argc, char **argv)
{
    std::string line, code;

    while (std::cin)
    {
        std::cout << ">>> ";
        std::getline(std::cin, line);

        if (line.length() == 0 || line == "exit")
            break;

        code += line;
    }

    auto syntax_tree = Parser(code).parse();
    Interpreter interpreter(syntax_tree);

    interpreter.run();
    interpreter.print_state();

    return 0;
}
