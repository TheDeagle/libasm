section .text
	global ft_write

ft_write:
	mov rax, 0x01
	syscall
	
	ret

