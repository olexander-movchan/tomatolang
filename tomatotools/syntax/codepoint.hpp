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
        std::size_t line = 0;
        std::size_t column = 0;
    };
}


#endif //TOMATO_CODEPOINT_NODE
