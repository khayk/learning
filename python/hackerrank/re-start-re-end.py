import re

S = input();
k = input();
# o = 0

# while True:
#     m = re.search(k, s)

#     if m == None:
#         if o == 0:
#             print('(-1, -1)')
#         break

#     print((m.start() + o, m.end() + o - 1)
#     s = s[m.start() + 1:]
#     o = o + m.start() + 1
#     # print(s)

# for m in re.finditer(k,S):
for m in re.finditer(r'(?=(' + k + '))',S):
    print ((m.start(1),m.end(1)-1))