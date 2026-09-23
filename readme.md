# Libasm

Assembly yourself.

A small journey into x86-64 assembly — learning how C functions look when you get rid of the comfort of C.

## What I implemented

### Mandatory
- `ft_strlen`
- `ft_strcpy`
- `ft_strcmp`
- `ft_write`
- `ft_read`
- `ft_strdup`

### Bonus
- `ft_atoi_base`
- `ft_list_push_front`
- `ft_list_size`
- `ft_list_sort`
- `ft_list_remove_if`
- `ft_simd_memchr`

Everything is written in **NASM, 64-bit, Intel syntax** following the **System V AMD64 ABI**.

---

## Technical Details & Optimization

- **Calling Conventions:** Arguments passed via standard register order (`RDI`, `RSI`, `RDX`, `RCX`, `R8`, `R9`).
- **SIMD / SSE Support:** `ft_simd_memchr` utilizes 128-bit XMM registers (`movdqu`, `pcmpeqb`, `pmovmskb`, `bsf`) to scan 16 bytes per cycle.
- **Syscall & Errno Handling:** `ft_write` and `ft_read` handle system calls directly via `syscall`, setting `__errno_location` on errors.
- **Stack Alignment:** Strict 16-byte stack frame alignment maintained prior to calling external functions like `malloc` and `free`.

---

## Build & Run

Build mandatory library:

```bash
make
```

Build bonus functions and run tests:

```bash
make bonus
```

Clean object files and build outputs:

```bash
make clean
make fclean
make re
```

---

## Project Structure

```text
.
├── mandatory/        → Mandatory NASM assembly sources
├── bonus/            → Bonus NASM assembly sources
├── obj/              → Compiled object files (.o)
├── main.c            → Mandatory test suite
├── bonus_main.c      → Bonus test suite
├── Makefile          → Compilation rules
└── README.md
```

---

> No magic. Just registers, memory, syscalls, and a lot of `mov`.
> 
> **42 — Libasm**