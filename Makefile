SRC = ./ft_read/ft_read.s ./ft_write/ft_write.s ./ft_strlen/ft_strlen.s ./ft_strcpy/ft_strcpy.s ./ft_strcmp/ft_strcmp.s \
      ./ft_strdup/ft_strdup.s    
OBJ = $(SRC:.s=.o)

NAME=libasm.a

NASM = nasm
CC = gcc
CFLAGS = -o a.out -no-pie
NASMFLAGS = -f elf64


$(NAME):
	for file in $(SRC); do \
		$(NASM) $(NASMFLAGS) -o $${file%.s}.o $$file; \
	done
	ar rc $(NAME)  $(OBJ)

fclean:
	rm -rf libasm.a $(OBJ)
