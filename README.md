## About

Just an interpreter for my own language...


## Example

Here is interactive session example:

    >>> var a = 3 * 10^2 + 11*5
    >>> var b = 10 * (2^3 + 2) + 13
    >>> var pi = a / b
    >>> pi
    3.141593


## Type system

Language is static and strongly typed.
There are three types supported: integer, floating-point and boolean (WIP).

Here are some rules for numeric operations:
- Algebraic operation on integer and float returns float
- Division returns float
- Integer value can be assigned to a float variable


## Variables

Variable cannot be used until it declared.
Once declared, variable can not be declared again.

Variable can be declared using next syntax construction:

    var <variable_name> = <expression>

A new value can be assigned to variable:

    <variable_name> = <expression>


## Expressions

Binary operators, unary operators and parentheses can be used.

Binary operators are:
- algebraic (`+`, `-`, `*`, `/`, `^`)
- comparative (`==`, `!=`, `>`, `>=`, `<`, `<=`)
- boolean (`and`, `or`)

Unary operators are `+`, `-` and `not`.

All operators are left-associative, except exponentiation (`^`) which is right-associative.

Here is operator precedence:

1. `^`
2. `*` and `/`
3. unary `+`, `-` and `not`
4. `+` and `-`
5. `==`, `!=`, `>`, `>=`, `<`, `<=`
6. `and`
7. `or`
