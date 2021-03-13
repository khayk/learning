import math

a = 1
b = 4
c = 2

if a == 0:
    print('a should not be 0')
    exit

d = b ** 2 - 4 * a * c

if d < 0:
    print('Equation has no solution')
elif d > 0:
    sqrt_d = math.sqrt(d)
    x1 = (-b - sqrt_d) / 2
    x2 = (-b + sqrt_d) / 2
    print('Equation has 2 roots: x1 = %0.2f, x2 = %0.2f' % (x1, x2))
else:
    print('Equation has a one root: %0.2f' % (-b / (2*a)))
