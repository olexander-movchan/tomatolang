#ifndef TOMATO_CODEPOINT_NODE
#define TOMATO_CODEPOINT_NODE


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
        std::size_t line;
        std::size_t column;
    };
}


#endif //TOMATO_CODEPOINT_NODE
