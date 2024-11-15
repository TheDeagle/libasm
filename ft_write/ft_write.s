section .data
	msg db "Hello world!", 0

section .text
	global _start


_start:
	call _main

	mov rax, 0x2000001
	mov rdi, 0
	syscall

ft_write:
	mov rax, 0x2000004
	mov rdi, 1
	mov rsi, [rbp + 8]
	mov rdx, 12
	syscall
	ret

_main:
	push msg
	push rbp
	mov rbp, rsp
	call ft_write

	ret
