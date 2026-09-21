section .text
global ft_list_size

ft_list_size:
    xor rcx, rcx

loop:
    test rdi, rdi
    jz done
    mov rdi, [rdi + 8]
    inc rcx
    jmp loop

done:
    mov rax, rcx
    ret