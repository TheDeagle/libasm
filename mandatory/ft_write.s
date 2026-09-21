section .text
global ft_write
extern __errno_location

ft_write:
    mov rax, 0x1
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