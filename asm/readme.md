### How to build assembler

* To assemble the program, type
`nasm -f elf hello.asm`
* To link the object file and create an executable file named hello, type
`ld -m elf_i386 -s -o hello hello.o`
* Execute the program by typing
`./hello`
