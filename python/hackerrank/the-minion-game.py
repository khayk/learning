def minion_game(s):
    vowels = 0
    consonants = 0
    n = len(s)

    for i in range(n - 1, -1, -1):
        if s[i] in "AEIOU":
            vowels += n - i
        else:
            consonants += n - i

    if vowels > consonants:
        print('Kevin', vowels)
    else:
        print('Stuart', consonants)

if __name__ == '__main__':
    s = input()
    minion_game(s)