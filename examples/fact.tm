func factorial(n int) -> int
    if n > 1 then
        return n * factorial(n - 1)
    else
        return 1
    end
end


var n int
read n

print factorial(n)
