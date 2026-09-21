section .text
global ft_read
extern __errno_location

ft_read:
    mov rax, 0x0
    syscall

    test rax, rax
    jns done

    neg rax
    mov edi, eax

    call __errno_location
    mov [rax], edi

    mov rax, -1

done:
    ret