section .text
global ft_calloc
extern malloc
extern __errno_location

ft_calloc:
    xor rcx, rcx

    mov rax, rdi
    mul rsi
    jc overflow

    
    mov rdi, rax
    push rax
    call malloc
    pop rdi

    test rax, rax
    je done

    xor rcx, rcx

loop:
    cmp rcx, rdi
    je done

    mov byte [rax + rcx], 0x0
    inc rcx

    jmp loop

done:
    ret


overflow:
    call __errno_location
    mov dword [rax], 12
    
    xor rax, rax
    ret
