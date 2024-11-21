section .text
	global ft_strdup
	extern ft_strlen
	extern ft_strcpy
	extern malloc

ft_strdup:
	call ft_strlen
	push rdi
	mov rdi, rax
	call malloc
	pop rbx
	mov rdi, rax
	mov rsi, rbx
	call ft_strcpy
	ret
	 
