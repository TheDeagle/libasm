section .text
global ft_strcmp

ft_strcmp:
	xor rcx, rcx

loop:
	mov al, [rdi + rcx]
	mov dl, [rsi + rcx]
	cmp al, dl
	jne done
	cmp dl, 0
	je done
	inc rcx
	jmp loop

done:
	sub al, dl
	movsx rax, al
	ret
