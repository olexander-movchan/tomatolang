var a float
var b float
var c float

read a
read b
read c

var D = b^2 - 4*a*c

if D > 0 then
    print (0 -b + D^0.5) / (2 * a)
    print (0 -b - D^0.5) / (2 * a)
end

if D == 0 then
    print (0 - b) / (2 * a)
end

if D < 0 then
    print false
end
