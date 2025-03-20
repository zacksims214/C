some misc asm/C files I write in my free time
Some light documentation for relevant files: 

itoa.asm:
  A procedure that takes an integer as an argument in RAX, and prints it to the screen. Uses the linux WRITE syscall, having to turn the integer into ascii before printing, hence the "integer to ascii" name, reverse of C's atoi

shell.c:
  A simple bash shell that the user can execute commands with. Again, we use linux system calls to execute the commands, via forking a child then calling exec to replace the child's process image with the command to be executed. 

shell.asm:
  This is simply a recreation of shell.c in x86 NASM. Functions the exact same, just in assembly for fun

sqrt.asm: 
  A procedure that calcuates the square root of an integer argument in RAX, returns result in RAX

stack.h
  A simple integer stack data structure in C. Supports common features such as push, pop, and peek, and destroy, as well as a function to resize the stack, either by a user defined amount, or simply doubling the current size. See comments in code for more detail

stack_notype.h
  A stack data structure that allows the user to declare the data type using the gcc typeof operator. Hence, you must compile with gcc. Obsufcated on purpose, will implement a much nicer version without the macro nonsense soon. See if you can figure out how it works if you want to have some fun
