section .text
	global ft_strcpy

ft_strcpy:
	xor rcx, rcx
	loop1 nop
	cmp byte[rsi], 0x0
	mov al, byte [rsi]
	mov byte [rdi], al
	je done
	inc rcx
	inc rdi
	inc rsi
	jne loop1
	
done:
	sub rdi, rcx
	mov rax, rdi
	ret
