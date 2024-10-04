VIEW AS CODE
Some random C files, will elaboraate on any files that need so here

Stack.h: not much to be said, the implementation prevents the user from doing anything too bad. See commments in file for further explanation

stack_notype.h: this will need some explaining, see below
  1:  A call to create should be followed by creating a StackData pointer and using SETDATA() to set the data in it. Allows use of ISFULL/EMPTY and GETBYTES, useful for handling out of bound crashes
  2: If StackData is omitted, then user must pay real close attention to pushing/popping, pushing past stack will segfault/abort, popping past corrupts address under the stack and might crash if block underneath isn't in address space(very unlikely)
  3: The stack does the following: on a push, we store at sp, THEN set it to the next address. on a pop, we dec sp, THEN retrive value
  4: Function Descriptions: 
    type* CREATE(type, nelems) : creates a stack, where type is the type of data to be stored, nelems is the number of elements we want to allocate. Returns address of stack pointer on success, NULL on error
    void* PUSH(sp, data) : Pushes value onto stack pointed to by sp. Returns address of stack on success, NULL on error. Just check if it returns NULL, discard it otherwise
    type* POP(sp) : Pops value and returns its ADDRESS, NOT DATA. Returns NULL on error, address of top value on success
    StackData* SETDATA(sp, sizeB, nelems) : takes the stack pointer, its size in bytes, and # of elements as args. Creates and ets all the fields in StackData aaccordingly. Returns NULL on error, pointer to StackData on success. Note that the user will have to free this pointer explicitly
    void DELETE(sd) : frees memory of dynamic block for the stack. Note that we free the base and not the actual sp itself, otherwise im pretty sure we get UD, see the Stack.h destroyStack() function as well. 
    bool ISFULL(sp, sd) : Returns whether or not the stack is full. Returns 1 on yes, 0 on no
    bool ISEMPTY(sp, sd) : Returns whether or not the stack is empty. Returns 1 on yes, 0 on no
    intptr_t GETBYTES(sp, sd) : Returns size remaining on stack in bytes, hence the name.

  
