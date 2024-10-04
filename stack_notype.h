#include <stdlib.h>
#include <stdint.h>

//helpful for tracking stack info, completely optional but you lose access to ISFULL, ISEMPTY and GETBYTES 
typedef struct {       
    intptr_t base;
    intptr_t top;
    size_t esize;
}   StackData;

//big boy functions of the stack
#define CREATE(type, nelems) ({ typeof (type)* sp = malloc(sizeof(type) * nelems); sp; })
#define PUSH(sp, data) ({ void* flag = sp; if(sp) *(sp)++ = data; flag; })
#define POP(sp) ({ void* vp = sp; if(sp) vp = --(sp); vp; })
#define SETDATA(sp, sizeB, nelems) ({ StackData* sd = malloc(sizeof(StackData)); if(sd != NULL) { sd->base = (intptr_t) sp; sd->top =  ((intptr_t) sp + (nelems * sizeB)); sd->esize = sizeB; } sd; })
#define DELETE(sp) (free(sp))
#define ISFULL(sp, sd) ( (intptr_t) sp == sd->top )
#define ISEMPTY(sp, sd) ( (intptr_t) sp == sd->base)
#define GETBYTES(sp, sd) ({ intptr_t x = sd->top - ((intptr_t) sp); x; })
