#include <iostream>
#include "lexer.hpp"

int main() {
    std::string line;

    while (std::getline(std::cin, line))
    {
        Lexer lexer(line);

        while (!lexer.eof())
        {
            std::cout << lexer.next_token() << ' ';
        }
        std::cout << std::endl;
    }
}
