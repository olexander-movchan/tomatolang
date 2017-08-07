#ifndef INTERPRETER_TYPES_HPP
#define INTERPRETER_TYPES_HPP


#include <memory>


/**
 * @brief Abstract base class for all runtime objects.
 *
 * @note Subclasses should use dynamic cast to implement methods.
 * @note Similar to Python's 'object' superclass
 */
class Object
{
public:
    /**
     * @brief Shortcut
     */
    using Ref = std::shared_ptr<Object>;

    virtual void set(const Object &object) = 0;
    virtual std::string str() = 0;

    /**
     * @brief Addition
     * @param object right addend
     * @return sum
     */
    virtual Ref add(const Object &object) = 0;

    /**
     * @brief Subtraction
     * @param object subtrahend
     * @return difference
     */
    virtual Ref sub(const Object &object) = 0;

    /**
     * @brief Multiplication
     * @param object right multiplier
     * @return product
     */
    virtual Ref mul(const Object &object) = 0;

    /**
     * @brief Division
     * @param object divisor
     * @return ratio
     */
    virtual Ref div(const Object &object) = 0;

    /**
     * @brief Exponentiation
     * @param object exponent
     * @return power
     */
    virtual Ref pow(const Object &object) = 0;

    /**
     * @brief Negation
     * @return opposite
     */
    virtual Ref opposite() = 0;
};


class Integer : public Object
{
public:
    Integer(int value = 0);

    void set(const Object &object) override;
    std::string str() override;

    Ref add(const Object &object) override;
    Ref sub(const Object &object) override;
    Ref mul(const Object &object) override;
    Ref div(const Object &object) override;

    Ref pow(const Object &object) override;
    Ref opposite() override;

    int value;
};


class Float : public Object
{
public:
    Float(float value = 0.0f);

    void set(const Object &object) override;
    std::string str() override;

    Ref add(const Object &object) override;
    Ref sub(const Object &object) override;
    Ref mul(const Object &object) override;
    Ref div(const Object &object) override;

    Ref pow(const Object &object) override;
    Ref opposite() override;

    float value;
};


#endif //INTERPRETER_TYPES_HPP
