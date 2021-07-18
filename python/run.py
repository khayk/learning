an = int(input())
a = set(map(int, input().split()))
n = int(input())

for i in range(n):
    op_name, bn = input().split()
    bn = int(bn)
    b = set(map(int, input().split()))

    # print(op_name, bn)
    # print(b)
    if op_name == 'update':
        a.update(b)
    elif op_name == 'intersection_update':
        a.intersection_update(b)
    elif op_name == 'difference_update':
        a.difference_update(b)
    elif op_name == 'symmetric_difference_update':
        a.symmetric_difference_update(b)

print(a)
print(sum(a))