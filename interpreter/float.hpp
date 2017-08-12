#ifndef INTERPRETER_FLOAT_HPP
#define INTERPRETER_FLOAT_HPP


#include "object.hpp"


class Float : public Object
{
public:
    Float(float value = 0.0f);

    void assign(const Object &object) override;
    std::string str() override;

    Ref add(const Object &object) override;
    Ref sub(const Object &object) override;
    Ref mul(const Object &object) override;
    Ref div(const Object &object) override;

    Ref exp(const Object &object) override;
    Ref un_minus() override;

    Ref un_plus() override;

    float value;
};


#endif //INTERPRETER_FLOAT_HPP
