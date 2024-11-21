section .text
	global ft_strcpy

ft_strcpy:
	xor rcx, rcx
	loop1 nop
	cmp byte [rsi], 0x0
	mov al, [rsi]
	mov [rdi], al
	je done
	inc rsi
	inc rdi
	inc rcx
	jne loop1

done:
	sub rdi, rcx
	mov rax, rdi
	ret
