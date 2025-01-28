;RUNS ON LINUX ONLY, NO WINDOWS
;procedure that takes an unsigned integer and convert it to a string and prints it. Similar to the MIPS print int syscall, but here we're using linux write syscall here
;linux only writes to screen from a buffer, so we must convert to ascii, hence the slightly complicated implementation
;rax holds the number to be printed, no return value

bits 64

section .data
	newline db " ", 10, 0
	newlineL equ $ - newline

section .bss
	digit resq 1

section .text
global _start

_start:

	mov rax, 999
	call itoa
	
	mov rax, 60
	mov rdi, 0
	syscall

itoa:
	;set up frame
	push rbp
	mov rbp, rsp

	;init regs, rbx is 10 for modulo, rcx rdx cleared
	mov rbx, 10
	mov rcx, 0
	mov rdx, 0

getDigits:
	
	;get least sig digit, add 48 to it and push to stack
	div rbx
	add rdx, '0'
	push rdx

	;inc dig count and clear rdx, not doing so gives FPE
	inc rcx
	xor rdx, rdx
	cmp rax, 0
	jnz getDigits

	;you gotta do this 
	mov r10, rcx

print:
	;get char
	pop rdx
	
	;store char in our memory location
	lea rax, digit
	mov byte [rax], dl

	;print digit label
	mov rax, 1
	mov rdi, 1
    	mov rsi, digit
    	mov rdx, 1
    	syscall

	;dec counter and check
	dec r10
	jnz print

printLine:
    	mov eax, 1
    	mov edi, 1
    	mov esi, newline
    	mov edx, newlineL
    	syscall

	pop rbp
	ret
