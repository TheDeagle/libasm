section .text
global ft_list_sort
extern ft_strcmp

ft_list_sort:
    test rdi, rdi
    jz done

    mov r10, [rdi]
    test r10, r10
    jz done

    test rsi, rsi
    jz done

restart:
    mov r10, [rdi]
    xor r9, r9

loop:
    mov r11, [r10 + 8]
    test r11, r11
    jz check_swapped

    push rdi
    push rsi
    push r10
    push r9
    push r11

    mov rdi, [r10]
    mov rsi, [r11]

    call [rsp + 24]

    pop r11
    pop r9
    pop r10
    pop rsi
    pop rdi

    cmp eax, 0x0
    jle next_node

    mov rdx, [r10]
    mov rcx, [r11]

    mov [r10], rcx
    mov [r11], rdx
    mov r9, 0x1

    jmp next_node

done:
    ret

next_node:
    mov r10, [r10 + 8]
    jmp loop

check_swapped:
    test r9, r9
    jnz restart
    ret