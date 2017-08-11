## About

Just an interpreter for my own language...


## Example

Here is simple interactive session example:

    >>> var a = 3 * 10^2 + 11*5
    >>> var b = 11^2 - 2^3
    >>> var pi = a / b
    >>> print
    var | value
    -----------
    a   | 355
    b   | 113
    pi  | 3.141593


## General program definition

Program consists of statements.

Statement is variable declaration, assignment or print statement.


## Variables

Variable cannot be used until it declared. Once declared, variable can not be declared again.

Variable can be declared using next syntax construction:

    var <variable_name> = <expression>

A new value can be assigned to variable:

    <variable_name> = <expression>


## Print statement

Just `print` with no whitespaces around will print all the declared variables and their values.


## Expressions

Expression is similar to algebraic expression.
Binary operators, unary operators and parentheses can be used.

Binary operators are:
- addition (+)
- subtraction (-)
- multiplication (*)
- division (/)
- exponentiation (^)

Unary operator are unary plus (+) and minus (-).


## Type system

Language is static and strongly typed.
However there are only two types supported: integer and floating-point.

Here are some rules:
- Operation with integer and float returns float
- Division returns float
- Integer can be assigned to a float variable


## Formal language specification

Here is LL(1) compatible language grammar:

    program    = statements

    statements = statement statements
               | statement

    statement  = var_decl
               | assignment
               | expression

    var_decl   = var identifier assign expression
    assignment = expression assign expression

    expression = term add expression
               | term sub expression
               | term

    term       = power mul term
               | power div term
               | power

    power      = factor pow power
               | factor

    factor     = lparen expression rparen
               | identifier
               | literal


    # LEXICAL

    var = 'var'

    add = '+'
    sub = '-'
    mul = '*'
    div = '/'
    pow = '^'

    assign = '='
    lparen = '('
    rparen = ')'

    identifier = "[A-Za-z][A-Za-z0-9]*"

    literal = "\d+(?:\.\d+)?"
