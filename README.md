Some random C/nasm files, will elaboraate on any files that need so here

Stack.h: not much to be said, the implementation prevents the user from doing anything too bad. See commments in file for further explanation

stack_notype.h: this will need some explaining, see below

  1: You MUST use gcc, I'm using GNU extensions ({}) and typeof, WILL NOT run without
  
  2:  A call to create should be followed by creating a StackData pointer and using SETDATA() to set the data in it. Allows use of ISFULL/EMPTY and GETBYTES, useful for handling out of bound crashes
  
  3: If StackData is omitted, then user must pay real close attention to pushing/popping, pushing past stack will segfault/abort, popping past corrupts address under the stack and might crash if block underneath isn't in address space(very unlikely)
  
  4: The stack does the following: on a push, we store at sp, THEN set it to the next address. on a pop, we dec sp, THEN retreive value
  
  5: Function Descriptions: 
  
    type* CREATE(type, nelems) : creates a stack, where type is the type of data to be stored, nelems is the number of elements we want to allocate. Returns address of stack pointer on success, NULL on error
    
    void* PUSH(sp, data) : Pushes value onto stack pointed to by sp. Returns address of stack on success, NULL on error. Just check if it returns NULL, discard it otherwise
    
    type* POP(sp) : Pops value and returns its ADDRESS, NOT DATA. Returns NULL on error, address of top value on success
    
    StackData* SETDATA(sp, sizeB, nelems) : takes the stack pointer, its size in bytes, and # of elements as args. Creates and ets all the fields in StackData aaccordingly. Returns NULL on error, pointer to StackData on success. Note that the user will have to free this pointer explicitly
    
    void DELETE(sd) : frees memory of dynamic block for the stack. Note that we free the base and not the actual sp itself, otherwise im pretty sure we get UD, see the Stack.h destroyStack() function as well. 
    
    bool ISFULL(sp, sd) : Returns whether or not the stack is full. Returns 1 on yes, 0 on no
    
    bool ISEMPTY(sp, sd) : Returns whether or not the stack is empty. Returns 1 on yes, 0 on no
    
    intptr_t GETBYTES(sp, sd) : Returns size remaining on stack in bytes, hence the name.
    

shell.c:

this acts as a simple shell in a linux environment, needs to be run on a linux machine or VM, WSL as well. Exit shell with CTRL+C

shell.asm

this is the same exact program as shell.c, but in x86_64 NASM. Again, I'm using linux syscalls so run on Linux. If shell.c runs, this should too.

commands to run shell.asm:

  nasm -f elf64 shell.asm

  ld shell.o -o shell

  ./shell

More to come, I had an OS project that was too easy in C, so I'll probably try and write it in assembly, will be posted soon if I do so
