import math

def is_prime(n):
    '''Check if the given number is prime or not'''
    if n <= 0:
        raise ValueError('Invalid argument')

    i = 2
    for i in range(2, math.floor(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

range_bounds = tuple(map(int, input('Enter 2 numbers defining range: ').split(' ')))
lower = range_bounds[0]
upper = range_bounds[1]

print('numbers %d, %d' % (lower, upper))

for i in range(lower, upper):
    if is_prime(i):
        print('%d' % (i), end = ' ')
