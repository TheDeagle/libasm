section .text
	global ft_strlen

ft_strlen:
	xor rcx, rcx
	
	loop1 nop
	cmp byte [rdi], 0x0

	je done
	inc rcx
	inc rdi
	jne loop1

done:
	mov rax, rcx
	ret

