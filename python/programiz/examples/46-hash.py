# Python rogram to find the SHA-1 message digest of a file

# importing the hashlib module
import hashlib

def hash_file(filename, h):
   """This function returns the hash
   of the file passed into it, with a requested hash algo"""

   # open file for reading in binary mode
   with open(filename, 'rb') as file:

       # loop till the end of the file
       chunk = 0
       while chunk != b'':
           # read only 1024 bytes at a time
           chunk = file.read(1024)
           h.update(chunk)

   # return the hex representation of digest
   return h.hexdigest()

message = hash_file("./programiz/examples/46-hash.py", hashlib.sha256())
print(message)
