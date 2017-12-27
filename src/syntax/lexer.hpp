#ifndef TOMATO_LEXER_HPP
#define TOMATO_LEXER_HPP


#include <string>
#include <map>


namespace Tomato::Syntax
{
    enum class Terminal
    {
        Invalid, EndOfFile, Operator, Assignment, Arrow, Identifier, Dot, Coma,

        IntegerLiteral, FloatLiteral, BooleanLiteral, CharacterLiteral, StringLiteral,

        LParen, LSquareBracket, LCurlyBracket,
        RParen, RSquareBracket, RCurlyBracket,

        // Keywords:
        Import, Var, Let, If, Then, Else, End, While, Do, For, In, Func, Return,

        Print, Read,
    };


    std::string to_string(Terminal terminal);


    struct Token
    {
        Terminal terminal;
        std::string lexeme;
    };


    std::string to_string(const Token &token);


    class InvalidToken : public std::exception {};


    class Lexer
    {
    public:
        Lexer() = default;
        explicit Lexer(const std::string &text);

        void set_text(const std::string &text);

        Token get_next();
        bool eof();

    private:
        char current();
        void skip();
        void accept();
        void expect(char character);
        void reject();

        Token token(Terminal terminal);
        void skip_whitespace();

        static const std::map<std::string, Terminal> keywords;

    private:
        Token number();
        Token identifier();
        Token operator_();
        Token string_literal();
        Token char_literal();

    private:
        std::string text;
        size_t offset = 0, len = 0;
    };
}


#endif //TOMATO_LEXER_HPP
