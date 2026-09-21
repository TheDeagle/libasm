section .text
global ft_list_push_front
extern malloc
extern __errno_location

ft_list_push_front:
    test rdi, rdi
    jz done

    test rsi, rsi
    jz done

    push rdi
    push rsi
    
    mov rdi, 16
    call malloc

    pop rsi
    pop rdi

    test rax, rax
    jz malloc_fail

    mov [rax], rsi
    mov rcx, [rdi]
    mov [rax + 8], rcx
    mov [rdi], rax

done:
    ret

malloc_fail:
    call __errno_location
    mov byte [rax], 0x12
    xor rax, rax
    ret

