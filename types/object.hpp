#ifndef INTERPRETER_OBJECT_HPP
#define INTERPRETER_OBJECT_HPP


#include <memory>


class TypeError : std::exception {};


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

    /**
     * @brief Default virtual destructor
     */
    virtual ~Object() = default;

    /**
     * @brief Determines whether object is of type T
     * @tparam T supposed object type
     * @return true if object is of type T
     */
    template <typename T>
    bool is_instance() const
    {
        return dynamic_cast<const T*>(this) != nullptr;
    }

    /**
     * @brief Gets type T reference to itself
     * @tparam T supposed object type
     * @return reference to itself as type T
     * @throw std::bad_cast
     */
    template <typename T>
    const T & as() const
    {
        return *dynamic_cast<const T*>(this);
    }

    /**
     * @brief assign
     * @param object
     */
    virtual void assign(const Object &object) = 0;

    /**
     * @brief String representaion
     * @return object's string representation
     */
    virtual std::string str() = 0;

    /**
     * @brief Addition
     * @param object right addend
     * @return sum
     */
    virtual Ref add(const Object &object);

    /**
     * @brief Subtraction
     * @param object subtrahend
     * @return difference
     */
    virtual Ref sub(const Object &object);

    /**
     * @brief Multiplication
     * @param object right multiplier
     * @return product
     */
    virtual Ref mul(const Object &object);

    /**
     * @brief Division
     * @param object divisor
     * @return ratio
     */
    virtual Ref div(const Object &object);

    /**
     * @brief Exponentiation
     * @param object exponent
     * @return power
     */
    virtual Ref pow(const Object &object);


    virtual Ref un_minus();
    virtual Ref un_plus();


    // Relational operators:

    virtual Ref lt(const Object &object);
    virtual Ref gt(const Object &object);
    virtual Ref le(const Object &object);
    virtual Ref ge(const Object &object);
    virtual Ref eq(const Object &object);
    virtual Ref ne(const Object &object);


    // Boolean operators:

    virtual Ref op_not();
    virtual Ref op_and(const Object &object);
    virtual Ref op_or (const Object &object);
};


#endif //INTERPRETER_OBJECT_HPP
