#ifndef INTERPRETER_BOOL_HPP
#define INTERPRETER_BOOL_HPP


#include "object.hpp"


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

};


#endif //INTERPRETER_BOOL_HPP
