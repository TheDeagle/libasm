NASM = nasm
NFLAGS = -f elf64

NAME = libasm
BONUS_NAME = bonus_libasm

SRC_DIR = mandatory
BONUS_SRC_DIR = bonus
OBJ_DIR = obj

SRC = ./$(SRC_DIR)/ft_strlen.s ./$(SRC_DIR)/ft_strcpy.s ./$(SRC_DIR)/ft_strcmp.s ./$(SRC_DIR)/ft_write.s ./$(SRC_DIR)/ft_read.s
OBJ = $(SRC:.s=.o)

BONUS_SRC = ./$(BONUS_SRC_DIR)/ft_list_push_front.s
BONUS_OBJ = $(SRC:.s=.o)

$(NAME): fclean
	@ mkdir $(OBJ_DIR)
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strlen.s -o ./$(OBJ_DIR)/ft_strlen.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strcpy.s -o ./$(OBJ_DIR)/ft_strcpy.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strcmp.s -o ./$(OBJ_DIR)/ft_strcmp.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_write.s -o ./$(OBJ_DIR)/ft_write.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_read.s -o ./$(OBJ_DIR)/ft_read.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strdup.s -o ./$(OBJ_DIR)/ft_strdup.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_calloc.s -o ./$(OBJ_DIR)/ft_calloc.o
	@ gcc main.c ./$(OBJ_DIR)/*.o -o  $(NAME)
	@ ./$(NAME)

bonus: fclean
	@ mkdir $(OBJ_DIR)
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_push_front.s -o ./$(OBJ_DIR)/ft_list_push_front.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_size.s -o ./$(OBJ_DIR)/ft_list_size.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strcmp.s -o ./$(OBJ_DIR)/ft_strcmp.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_sort.s -o ./$(OBJ_DIR)/ft_list_sort.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_remove_if.s -o ./$(OBJ_DIR)/ft_list_remove_if.o
	gcc bonus_main.c ./$(OBJ_DIR)/*.o -o  $(BONUS_NAME)
	@ ./$(BONUS_NAME)

all: $(NAME) bonus

clean:
	@ rm -rf $(OBJ_DIR)

fclean: clean
	@ rm -rf $(NAME) $(BONUS_NAME)