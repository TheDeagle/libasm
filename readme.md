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
- `ft_calloc`

### Bonus
- `ft_atoi_base`
- `ft_list_push_front`
- `ft_list_size`
- `ft_list_sort`
- `ft_list_remove_if`

Everything is written in **NASM, 64-bit, Intel syntax**.

---

## Build & run

```bash
make
```

Build the bonus:

```bash
make bonus
```

The Makefile also runs the test program automatically after compilation.

---

## Structure

```text
mandatory/    → mandatory assembly
bonus/        → bonus assembly
obj/          → generated object files
main.c        → mandatory tests
bonus_main.c  → bonus tests
```

---

> No magic. Just registers, memory, syscalls, and a lot of `mov`.
> 
> **42 — Libasm**