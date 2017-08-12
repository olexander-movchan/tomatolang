## About

Just an interpreter for my own language...

Program should consist of statements. Statements are:

- variable declaration
- assignment
- expression

If single expression is given, its value will be printed.


## Example

Here is interactive session example:

	>>> var pi = 3.1415926
	>>> var eps = 10^-5
	>>> var diff = pi - 355/113
	>>> -eps < diff and diff < eps
	true


## Variables

Variable cannot be used until it declared.
Once declared, variable can not be declared again.

Variable can be declared using next syntax construction:

    var <variable_name> = <expression>

A new value can be assigned to variable:

    <variable_name> = <expression>


## Type system

Language is static and strongly typed.
There are three types supported: integer, floating-point and boolean.

Here are some rules for numeric operations:
- Algebraic operation on integer and float returns float;
- Division returns float;
- Exponentiation returns float;
- Integer value can be assigned to a float variable.


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
