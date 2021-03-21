
import itertools

A = list(map(int, filter(lambda s: (s != ''), input().split())))
B = list(map(int, filter(lambda s: (s != ''), input().split())))

for pair in list(itertools.product(A, B)):
    print(pair, end = ' ')