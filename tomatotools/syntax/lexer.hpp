#ifndef INTERPRETER_LEXER_HPP
#define INTERPRETER_LEXER_HPP


#include <string>
#include <map>

#include "token.hpp"


class Lexer
{
public:
    /**
     * @param code program source code
     */
    Lexer(const std::string &code);

    /**
     * @brief Parses next lexical token
     * @return next token
     */
    Token next();

    /**
     * @brief Checks whether end of file reached
     * @return true if EOF reached
     */
    bool eof() const;

private:
    std::string code;
    std::size_t offset;

    Token::Position token_pos;
    Token::Position current_pos;

    char current_char();
    void advance();
    void skip_whitespace();

    Token literal();
    Token identifier();

    /// @todo Refactor method
    Token operator_token();

    static std::map<std::string, Token::Type> keywords;
};


#endif //INTERPRETER_LEXER_HPP
