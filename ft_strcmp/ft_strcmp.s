section .text
	global ft_strcmp

ft_strcmp:
	cmp [rdi], [rsi]	
	jl neg
	jg pos
	je eq

eq:
	mov rax, 0
	ret

neg:
	mov al, [rdi]
	mov ab, [rsi]
	sub al, ab
	mov rax, al
	ret

pos:
	mov rax, 1
	ret
