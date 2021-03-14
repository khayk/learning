import math

def is_prime(n):
    '''Check if the given number is prime or not'''
    if (n <= 0):
        raise ValueError('Invalid argument')

    i = 2
    for i in range(2, math.floor(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

# n = int(input("Enter number for prime test: "))
n = 12

try:
    print('{0} is {1}a prime number'.format(n, '' if is_prime(n) else 'NOT '))
except ValueError as ve:
    print(ve)