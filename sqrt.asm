bits 64
section .text

global sqrt

sqrt:
   
    mov r8, rax
    mov r9, r8
    shr rax, 1
    mov r10, rax
    
loop:
    
    xor rdx, rdx
    mov rax, r8
    div r9
    add rax, r9

    shr rax, 1
    mov r9, rax
    dec r10
    jnz loop
    
done:
    mov rax, r9
    ret
