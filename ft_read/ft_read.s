section .text
	global ft_read
	extern __errno_location

ft_read:
	mov rax, 0x00
	syscall
	
	test rax, rax
	js _error 

	ret

_error:
	neg rax
	mov rbx, rax
	call __errno_location
	mov (rax), rbx
	mov rax, -1
	ret
