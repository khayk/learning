# 1. Print two strings with formatting
#    see https://www.programiz.com/python-programming/input-output-import
print("Hello %s %s! You just delved into python." % (a, b))


# 2. Map each item from the input to int
integer_list = map(int, input().split())
    # Creates a tuple of integers
    t = tuple(integer_list)
    # Creates a tuple of integers
    l = list(integer_list)

# 3. Read the first string inside the command and the rest inside args
command, *args = input().split()

# 4. Locates the main function and call it
if __name__ == '__main__':
    print("You are inside main")

# 5. strip returns a copy of the string with both leading and trailing characters removed (based on the string argument passed).
    "  hello ".strip() # result is 'hello'

# 6. Your task is to find out if the string  contains: alphanumeric characters
    any([char.isalnum() for char in S])

# 7. String adjustements
    width = 20
    'HackerRank'.ljust(width,'-')   # HackerRank----------
    'HackerRank'.center(width,'-')  # -----HackerRank-----
    'HackerRank'.rjust(width,'-')   # ----------HackerRank

# 8. The textwrap module provides two convenient functions: wrap() and fill().
    print(textwrap.wrap(string,8))
    print(textwrap.fill(string,8))

# 9. Make the first letter uppercase
    'name'.capitalize()