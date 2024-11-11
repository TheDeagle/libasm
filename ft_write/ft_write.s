section .data
	msg db "Hello world!", 10 

section .text
	global _start

_start:
	call main
	
	mov rax, 0x200001
	mov rdi, 0
	syscall

main:
	mov rsi, msg
	mov rdx, 13 
	call ft_write

	ret

ft_write:
	mov rax, 0x200004
	mov rdi, 1
	syscall	

	ret
