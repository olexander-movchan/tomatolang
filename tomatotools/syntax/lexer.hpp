#ifndef TOMATO_LEXER_HPP
#define TOMATO_LEXER_HPP


#include <string>
#include <map>
#include <syntax/codepoint.hpp>

#include "token.hpp"


namespace Tomato
{
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
        std::size_t start_offset;
        std::size_t current_offset = 0;

        CodePoint start_point;
        CodePoint current_point;

        char current_char();
        void advance();
        void skip_whitespace();

        Token token(Token::Type type);
        Token literal();
        Token identifier();

        /// @todo Refactor method
        Token operator_token();

        static std::map<std::string, Token::Type> keywords;
    };
}


#endif //TOMATO_LEXER_HPP
