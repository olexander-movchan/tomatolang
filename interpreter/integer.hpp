#ifndef INTERPRETER_INTEGER_HPP
#define INTERPRETER_INTEGER_HPP


#include "object.hpp"


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

    Ref pow(const Object &object) override;

    Ref un_minus() override;
    Ref un_plus() override;

    int value;
};


#endif //INTERPRETER_INTEGER_HPP
