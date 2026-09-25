section .text
global ft_atoi_base

; prototype int ft_atoi_base(char *str, char *base)
; RDI = str
; RSI = base

get_base_len:
    test rdi, rdi
    jz fail
    xor eax, eax          ; i = 0

loop:
    mov bl, [rdi + rax]
    test bl, bl
    jz check_len
    cmp bl, '-'
    je fail
    cmp bl, '+'
    je fail
    cmp bl, 32
    jle fail
    cmp bl, 127
    jge fail
    lea rcx, [rax + 1]

dup_loop:
    mov dl, [rdi + rcx]
    test dl, dl
    jz no_dup
    cmp dl, bl
    je fail
    inc rcx
    jmp dup_loop

no_dup:
    inc rax
    jmp loop

check_len:
    cmp rax, 2
    jl fail
    ret

fail:
    xor eax, eax
    ret

is_digit:
    test rdi, rdi
    jz .not_found
    test rsi, rsi
    jz .not_found
    xor r8d, r8d

.loop:
    mov al, [rsi + r8]     ; use al, not bl
    test al, al
    jz .not_found
    cmp al, [rdi]
    je .found
    inc r8d
    jmp .loop

.found:
    mov eax, r8d
    ret

.not_found:
    mov eax, -1
    ret


ft_atoi_base:
	push rbx
	push r12

    xor ebx, ebx
    xor r10b, r10b

    push rdi
    mov rdi, rsi
    call get_base_len
    pop rdi

    test eax, eax
    jz return_zero        ; invalid base

    mov r12d, eax

    test rdi, rdi
    jz return_zero        ; NULL str

    xor rcx, rcx
    call skip_sapces
    mov rcx, rax

parse_signs:
    cmp byte [rdi + rcx], '-'
    je handle_minus
    cmp byte [rdi + rcx], '+'
    je handle_plus
    jmp conversion_loop

handle_minus:
    xor r10b, 1
    inc rcx
    jmp parse_signs

handle_plus:
    inc rcx
    jmp parse_signs

conversion_loop:
	push rdi
	lea rdi, [rdi + rcx]
	call is_digit
	pop rdi

	cmp eax, -1
	je end

	imul ebx, r12d
	add ebx, eax

	inc rcx
	jmp conversion_loop


end:
	cmp r10b, 1
	jne return
	neg ebx

return:
	movsxd rax, ebx
	pop r12
	pop rbx
	ret 

skip_sapces:
    mov al, [rdi + rcx]
    cmp al, ' '
    je space_loop_reloop
    cmp al, 9
    jb mov_rcx_rax
    cmp al, 13
    jbe space_loop_reloop

mov_rcx_rax:
    mov rax, rcx
    ret

space_loop_reloop:
    inc rcx
    jmp skip_sapces

return_zero:
    xor eax, eax
	pop r12
	pop rbx
    ret