section .text
	global ft_write
	extern __errno_location

ft_write:
	mov rax, 0x01
	syscall
	
	test rax, rax
	js _error
	
	ret

_error:
	neg rax
	mov rbx, rax
	call __errno_location
	mov [rax], rbx
	mov rax, -1	

	ret
	

