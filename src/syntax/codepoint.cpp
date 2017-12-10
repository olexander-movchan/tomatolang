#include "codepoint.hpp"


namespace Tomato
{
    bool operator==(const CodePoint &a, const CodePoint &b)
    {
        return a.line == b.line && a.column == b.column;
    }
}
