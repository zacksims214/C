#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//definitition for address variables that SHOULDNT be modified, set only
typedef uint64_t word;

//simple struct to hold the stack pointer, base addr and max addr
typedef struct {
  int* sp;
  word baseAddress;
  word maxAddress;
} Stack;

//some useful simple functions, assumes int element type of course 
word getSize(Stack* stack) { return ((word) stack->sp - stack->baseAddress) / sizeof(int); }
word getTotalSize(Stack* stack) { return (stack->maxAddress - stack->baseAddress) / sizeof(int); }
word getSizeRemaining(Stack* stack) { return (stack->maxAddress - (word) stack->sp) / sizeof(int); }
word isEmpty(Stack* stack) { return ( (word) stack->sp == stack->baseAddress ); }                                    
word isFull(Stack* stack) { return ( stack->maxAddress == (word) stack->sp ); }

//creates a stack and sets all values
//default int data type, returns pointer to stack on success, NULL on error
Stack* createStack(size_t nelements) {
    if(nelements <= 0) 
        return NULL;
    //request memory for struct
    Stack* stack =  (Stack*) malloc(sizeof(Stack));
    if(stack == NULL)
        return NULL;

    //request memory for actual stack
    stack->sp = (int*) malloc(nelements * sizeof(int));
    if(stack->sp == NULL)
        return NULL;

    //set upper/lower bounds
    stack->baseAddress = (word) stack->sp;
    stack->maxAddress = stack->baseAddress + (nelements * sizeof(int));
    return stack;
}

//returns 0 on failure, 1 on success
int push(Stack* stack, int data) {
    if(stack == NULL || isFull(stack))
        return 0;
    *(stack->sp)++ = data;
    return 1;
}

//pops element, returns pointer to data, NULL on error
int* pop(Stack* stack) {
    if(stack == NULL || isEmpty(stack))
        return NULL;
    return --(stack->sp);
}

//NULL on error, address of value returned on success
int* peek(Stack* stack) { 
    if(stack == NULL || isEmpty(stack)) 
        return NULL;   
    else return ((stack->sp) - sizeof(int)); 
}

//ensures both the stack pointer and the struct stack pointer are destroyed
//just doing free(stack) leaks
void destroyStack(Stack* stack) {
    //no need to check for NULL, free wont complain
    free((int *) stack->baseAddress);
    free(stack);
}

//will INCREASE stack, passing a negative arg is forbidden
//passing nelems as 0 will double current stack size
Stack* resize(Stack* stack, size_t nelems) {
    int offset; 
    //arg checking
    if(stack == NULL || nelems < 0)
        return NULL;

    //get offset of sp and create new stack
    offset = getSize(stack);
    Stack* temp;
    //this allows for a simple scheme to just double the stack size
    if(nelems == 0) 
        temp = createStack(getTotalSize(stack) << 1);
    else 
        temp = createStack(nelems);

    //check memory
    if(temp == NULL)
        return NULL;

    //copy memory
    temp->sp = memcpy((void*) temp->sp, (void*) stack->baseAddress, offset * sizeof(int));
    //temp sp holds new sized stack with all old data, just need to set pointer to correct offset
    temp->sp = temp->sp + (offset * sizeof(int));

    //free old stack and return pointer to new stack
    destroyStack(stack);
    return temp;
}
