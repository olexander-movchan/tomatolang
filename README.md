#### About
Just an interpreter for my own language...

#### Language Specifcation
    program    = statement +
    statement  = assignment | var_decl
    var_decl   = var variable assign expression
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
    var    = "var"

#### Example
Here is an example of interactive session:

    ti> var a = 2
    ti> var b = 3
    ti> var c = b - a
    ti> c = a + b - c
    ti> exit
    a	2
    b	3
    c	4
