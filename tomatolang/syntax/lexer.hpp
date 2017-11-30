#ifndef TOMATO_LEXER_HPP
#define TOMATO_LEXER_HPP


#include <string>
#include <map>

#include "token.hpp"
#include "navigator.hpp"


namespace Tomato
{
    class Lexer
    {
    public:
        void append(const std::string &code);
        void reset(const std::string &code);

        /**
         * @brief Parse next lexical token
         * @return next token
         */
        Token next_token();

        /**
         * @brief Checks whether end of file reached
         * @return true if EOF reached
         */
        bool eof() const;

        static CodePoint Pointer;

    private:
        std::string source_buffer;
        std::size_t start_offset;
        std::size_t current_offset = 0;

        CodeNavigator navigator;

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
