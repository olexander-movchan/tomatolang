func fib(n int)
    var a = 0
    var b = 1
    var i = 0

    while i < n do
        print a

        b = b + a
        a = b - a

        i = i + 1
    end
end

var k = 42

while k != 0 do
    read k
    fib(k)
end
