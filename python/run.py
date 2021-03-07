def print_formatted(n):
    # your code goes here
    w = len('{0:b}'.format(n))

    for i in range (1, n + 1):
        d = str(i)
        o = '{0:o}'.format(i)
        h = '{0:x}'.format(i).upper()
        b = '{0:b}'.format(i)

        print(d.rjust(w), o.rjust(w), h.rjust(w), b.rjust(w))