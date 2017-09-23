#ifndef TOMATO_INTEGER_HPP
#define TOMATO_INTEGER_HPP


#include "object.hpp"


namespace Tomato
{
    class Integer : public Object
    {
    public:
        Integer(int value = 0);

        void assign(const Object &object) override;
        std::string str() override;

        Ref add(const Object &object) override;
        Ref sub(const Object &object) override;
        Ref mul(const Object &object) override;
        Ref div(const Object &object) override;
        Ref exp(const Object &object) override;

        Ref un_minus() override;
        Ref un_plus() override;

        Ref lt(const Object &object) override;
        Ref gt(const Object &object) override;
        Ref le(const Object &object) override;
        Ref ge(const Object &object) override;
        Ref eq(const Object &object) override;
        Ref ne(const Object &object) override;

        int value;
    };
}


#endif //TOMATO_INTEGER_HPP
