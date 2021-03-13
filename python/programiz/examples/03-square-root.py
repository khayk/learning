import math

num = 1+2j

# To take input from the user
#num = eval(input('Enter a number: '))

num_sqrt = math.sqrt(num)

print('The square root of {0} is {1:0.3f}+{2:0.3f}j'.format(num ,num_sqrt.real,num_sqrt.imag))
