section .text
	global ft_write

ft_write:
	mov rax, 0x01
	syscall
	
	mov rbx, rax
	test rax, rax
	js _error
	
	ret

_error:
	neg rax
	ret
	

