#ifndef TOMATO_CODEPOINT_HPP
#define TOMATO_CODEPOINT_HPP


#include <cstddef>


namespace Tomato
{
    /**
     * @brief CodePoint represents some character location in the code.
     *
     * @note Line and column are zero-indexed.
     */
    struct CodePoint
    {
        std::size_t line = 0;
        std::size_t column = 0;
    };


    bool operator== (const Tomato::CodePoint &a, const Tomato::CodePoint &b);
}


#endif //TOMATO_CODEPOINT_HPP
