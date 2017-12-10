#ifndef TOMATO_BOOL_HPP
#define TOMATO_BOOL_HPP


#include "object.hpp"


namespace Tomato
{
    /**
     * @brief Represents boolean values.
     */
    class Bool : public Object
    {
    public:
        Bool(bool value = false);

        bool value;

        void assign(const Object &object) override;

        std::string str() override;

        Ref op_and(const Object &object) override;
        Ref op_or (const Object &object) override;

        Ref op_not() override;

        static Ref True();
        static Ref False();
    };
}


#endif //TOMATO_BOOL_HPP
