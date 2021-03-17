n = int(input('Enter a number: '))

if n < 1:
    print("Sorry, factorial does not exist for negative numbers")
elif n == 0:
    print("0! = 1")
else:
    factorial = 1

    for i in range(2, n + 1):
        factorial = factorial * i

    print ('%d! = %d' % (n, factorial))