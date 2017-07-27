#### About
Just an interpreter for my own language...

#### Language Specifcation
    program    = statement +
    statement  = assignment
    assignment = variable assign expression
    
    expression = sum
    sum        = product ( (plus | minus) product )*
    product    = power ( (mul | div) power )*
    power      = factor [ pow power ]
    factor     = (plus | minus) factor
                | variable
                | integer
                | "(" expression ")"
    variable   = identifier
                
    plus   = "+"
    minus  = "-"
    mul    = "*"
    div    = "/"
    pow    = "^"
    assign = "="

#### Example
Here is an example of interactive session:

    ti> a = 2^10
    ti> b = 5 - (-2 * (3 + -7)) ^2
    ti> c = a - 2*b
    ti> exit
    a	1024
    b	-59
    c	1142
