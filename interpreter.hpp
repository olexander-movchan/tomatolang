#ifndef INTERPRETER_INTERPRETER_HPP
#define INTERPRETER_INTERPRETER_HPP


#include "lexer.hpp"

class Interpreter
{
public:
    Interpreter(const std::string &code);

    int run();

private:
    Lexer lexer;
    Token current_token;

    void eat(TokenType expected_type);
};


#endif //INTERPRETER_INTERPRETER_HPP
