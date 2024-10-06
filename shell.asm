bits 64


;all our strings
section .data
    prompt db "$ ", 0
    promptL equ $ - prompt

    errmsg db "Error!!!",10,0
    errmsgL equ $ - errmsg

    message db "Bash Terminal, use CTRL+C to exit", 10, 0
    messageL equ $ - message

    ;preset args for a system() like execution, we handle the argv* by declaring an array of the correct args
    bin db "/bin/sh", 0
    arg1 db "sh", 0
    arg2 db "-c", 0
    arg3 db "ls", 0
    arg4 db "", 0

    args dq arg1, arg2, buffer, arg4, 0

section .bss
    buffer: resb 256
section .text

global _start
_start:

    ;print message
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    mov rdx, messageL
    syscall

    cmp rax, 0
    js error

    loop1:
        ;print prompt
        mov rax, 1
        mov rdi, 1
        mov rsi, prompt
        mov rdx, promptL
        syscall

        ;error handling
        cmp rax, promptL
        jnz error

        ;now we need to fork a child and have it execute a command from STDIN
        ;first we'll store the command in our buffer
        mov rax, 0
        mov rdi, 0
        mov rsi, buffer
        mov rdx, 256
        syscall

        cmp rax, 0
        js error

        ;buffer now holds command, lets fork uglass
        mov rax, 57
        syscall
     
        cmp rax, 0
        js error
        jz child

        ;in parent, we wait for child
        mov rdi, rax
        mov rax, 61

        ;we dont care about options, just wait on child
        mov rsi, 0
        mov rdx, 0
        mov r10, 0
        syscall

        ;clear buffer and jmp back
        mov rax, buffer
        mov rcx, 256

        ;will clear the buffer, roughly equal to memset(buffer, '\0', sizeof(buffer)); in C version, see shell.c 
        clearBuffer:
            mov BYTE [rax], 0x00
            inc rax
            loop clearBuffer

        ;do it all again
        jmp loop1

        ;exit just in case
        mov rax, 60
        mov rdi, 0
        syscall

child:
    ;we'll execute command in buffer, first load correct args for exec
    mov rax, 59
    lea rdi, bin
    lea rsi, args
    xor rdx, rdx
    syscall
    
    ;call to exit just in case
    mov rax, 60
    mov rdi, 0
    syscall

;error handler for any syscall errors
error:
    ;print error msg and exit
    mov rax, 1
    mov rdi, 1
    mov rsi, errmsg
    mov rdx, errmsgL
    syscall

    mov rax, 60
    mov rdi, 0
    syscall
