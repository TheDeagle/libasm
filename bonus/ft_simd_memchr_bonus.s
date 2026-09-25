section .text
global ft_simd_memchr

;   RDI=str
;   RSI=c
;   RDX=n

ft_simd_memchr:
    test rdx, rdx
    jz null

    movzx eax, sil
    imul eax, eax, 0x01010101   ; fill all the 4 bytes with c
    movd xmm1, eax
    pshufd xmm1, xmm1, 0        ; fill the 128 bits of xmm1 using the first 32 bits

loop16:
    cmp rdx, 16
    jb tail

    movdqu xmm0, [rdi]
    pcmpeqb xmm0, xmm1          ; compate xmm0 and xmm1 byte by byte for each 16 bytes (if equal xmm0 = 0xFF, if not xmm0 == 0x00)
    pmovmskb ecx, xmm0 
    test ecx, ecx
    jnz hit

    add rdi, 16
    sub rdx, 16
    jmp loop16

tail:
    test rdx, rdx
    jz null

    cmp byte [rdi], sil
    je one

    inc rdi
    dec rdx
    jmp tail

null:
    xor rax, rax
    ret

one:
    mov rax, rdi
    ret

hit:
    bsf ecx, ecx    ; set ecx to the position of the first 1 bit in ecx (least significant bit)
    lea rax, [rdi + rcx]
    ret