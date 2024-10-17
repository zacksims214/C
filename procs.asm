;;will simply create a child, print message and exit. 
;;we do 1, 2, 4, and 8 iterations, based on OS project 

bits 64

section .data

    line db "", 10, 0
    lineL equ $ - line

    strt db "Beginning", 10, 0
    strtL equ $ - strt

    childMsg db "Hello from child!", 10, 0
    childMsgL equ $ - childMsg

    errorM db "Error, Exiting", 10, 0
    errorL equ $ - errorM

    oneC db "Starting one child ",10, 10, 0
    oneCL equ $ - oneC

    twoC db "Starting two children ",10, 10, 0
    twoCL equ $ - twoC

    fourC db "Starting four children ",10, 10, 0
    fourCL equ $ - fourC

    eightC db "Starting eight children ",10, 10, 0
    eightCL equ $ - eightC

    done db "Done",10, 0
    doneL equ $ - done

section .text

    global _start

_start:

    ;print message
    mov rax, 1
    mov rdi, 1 
    mov rsi, strt
    mov rdx, strtL
    syscall

    mov rax, 1
    mov rsi, line
    mov rdx, lineL
    syscall


    ;here we're just printing all the messages and making calls to go

    mov rax, 1
    mov rdi, 1 
    mov rsi, oneC
    mov rdx, oneCL
    syscall
    mov r8, 1
    call go

    call printLine

    mov rax, 1
    mov rdi, 1 
    mov rsi, twoC
    mov rdx, twoCL
    syscall
    mov r8, 2
    call go

    call printLine

    mov rax, 1
    mov rdi, 1 
    mov rsi, fourC
    mov rdx, fourCL
    syscall
    mov r8, 4
    call go

    call printLine

    mov rax, 1
    mov rdi, 1 
    mov rsi, eightC
    mov rdx, eightCL
    syscall
    mov r8, 8
    call go

    call printLine

    mov rax, 1
    mov rdi, 1 
    mov rsi, done
    mov rdx, doneL
    syscall

    jmp exit
    

;expects child num in r8, will fork r8 children 
go:
    ;fork child
    mov rax, 57
    syscall

    cmp rax, 0
    jz child

    ;in parent, wait for kid to simmer down
    mov rax, 61
    mov rdi, 0
    xor rsi, rsi
    xor rdx, rdx
    xor r10, r10
    syscall

    dec r8
    jnz go

    ret
    
child:

    ;in child, print msg and exit
    mov rax, 1
    mov rdi, 1
    mov rsi, childMsg
    mov rdx, childMsgL
    syscall

    jmp exit

error:
    mov rax, 1
    mov rdi, 1
    mov rsi, errorM
    mov rdx, errorL
    syscall
    jmp exit

printLine:
    mov rax, 1
    mov rdi, 1
    mov rsi, line
    mov rdx, lineL
    syscall

    ret

exit:
    mov rax, 60
    mov rdi, 0
    syscall