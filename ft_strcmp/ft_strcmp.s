section .text
	global ft_strcmp

ft_strcmp:
	cmp rdi, rsi
	jg pos
	jl neg
	je eq

eq:
	mov rax, 0
	ret

neg:
	mov rax, -1
	ret

pos:
	mov rax, 1
	ret
