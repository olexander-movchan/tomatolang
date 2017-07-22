#include <iostream>
#include "lexer.hpp"
#include "interpreter.hpp"

int main() {
    std::string line;

    while (std::cin)
    {
        std::cout << "calc> ";
        std::getline(std::cin, line);

        Interpreter interpreter(line);

        std::cout << interpreter.run() << std::endl;
    }
}
