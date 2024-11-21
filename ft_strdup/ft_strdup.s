section .text
	global ft_strdup
	extern ft_strlen
	extern ft_strcpy
	extern malloc

ft_strdup:
	push rdi
	call ft_strlen
	mov rdi, rax
	add rdi, 1
	call malloc
	pop rbx
	mov rdi, rax
	mov rsi, rbx
	call ft_strcpy
	ret
	 
