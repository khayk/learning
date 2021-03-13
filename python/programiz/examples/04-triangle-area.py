import math

a = 3
b = 4
c = 5

p = (a + b + c) / 2
area = math.sqrt(p * (p - a) * (p - b) * (p - c))

print ('The area of the triangle is %0.2f' %area);
