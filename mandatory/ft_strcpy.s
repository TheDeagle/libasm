section .text
global ft_strcpy

ft_strcpy: 
    xor rcx, rcx

loop:
    mov dl, [rsi + rcx]
    mov [rdi + rcx], dl
    cmp byte [rsi + rcx], 0
    je done
    inc rcx
    jmp loop

done:
    mov rax, rdi
    ret