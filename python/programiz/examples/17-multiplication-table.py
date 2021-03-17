# To take input from the user
num = int(input("Display multiplication table of? "))

for i in range(1, 11):
    print('%d X% 3d =% 4d' % (num, i, num * i))