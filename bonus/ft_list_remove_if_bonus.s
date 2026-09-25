section .text
global ft_list_remove_if
extern free

ft_list_remove_if:
    test rdi, rdi
    jz done

    test rsi, rsi
    jz done

    test rdx, rdx
    jz done

    push r12
    push r13
    push r14
    push r15

    mov r12, rdi
    mov r13, rsi
    mov r14, rdx
    mov r15, rcx

loop:
    mov rax, [r12]
    test rax, rax
    jz cleanup

    mov rdi, [rax]
    mov rsi, r13
    call r14

    cmp eax, 0x0
    jne next_list

    mov rax, [r12]
    mov rdx, [rax + 8]
    mov [r12], rdx

    push rax
    test r15, r15
    jz free_list

    mov rdi, [rax]
    call r15

free_list:
    pop rdi
    call free
    jmp loop

cleanup:
    pop r15
    pop r14
    pop r13
    pop r12

done:
    ret

next_list:
    mov rax, [r12]
    lea r12, [rax + 8]
    jmp loop
