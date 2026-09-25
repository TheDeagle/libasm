NASM = nasm
NFLAGS = -f elf64

NAME = libasm
BONUS_NAME = bonus_libasm
LIB = libasm.a

TEST = test_main
TEST_BONUS = test_bonus

SRC_DIR = mandatory
BONUS_SRC_DIR = bonus
OBJ_DIR = obj

SRC = ./$(SRC_DIR)/ft_strlen.s ./$(SRC_DIR)/ft_strcpy.s ./$(SRC_DIR)/ft_strcmp.s ./$(SRC_DIR)/ft_write.s ./$(SRC_DIR)/ft_read.s

BONUS_SRC = ./$(BONUS_SRC_DIR)/ft_list_push_front.s

# ---------------------------------------------------------------------------- #
#                                  Mandatory                                   #
# ---------------------------------------------------------------------------- #

$(NAME):
	@ mkdir -p $(OBJ_DIR)
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strlen.s -o ./$(OBJ_DIR)/ft_strlen.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strcpy.s -o ./$(OBJ_DIR)/ft_strcpy.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strcmp.s -o ./$(OBJ_DIR)/ft_strcmp.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_write.s -o ./$(OBJ_DIR)/ft_write.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_read.s -o ./$(OBJ_DIR)/ft_read.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strdup.s -o ./$(OBJ_DIR)/ft_strdup.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_calloc.s -o ./$(OBJ_DIR)/ft_calloc.o
	@ ar rcs $(LIB) ./$(OBJ_DIR)/ft_strlen.o ./$(OBJ_DIR)/ft_strcpy.o ./$(OBJ_DIR)/ft_strcmp.o ./$(OBJ_DIR)/ft_write.o ./$(OBJ_DIR)/ft_read.o ./$(OBJ_DIR)/ft_strdup.o ./$(OBJ_DIR)/ft_calloc.o

# ---------------------------------------------------------------------------- #
#                                    Bonus                                     #
# ---------------------------------------------------------------------------- #

bonus:
	@ mkdir -p $(OBJ_DIR)
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_atoi_base_bonus.s -o ./$(OBJ_DIR)/ft_atoi_base_bonus.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_push_front_bonus.s -o ./$(OBJ_DIR)/ft_list_push_front_bonus.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_size_bonus.s -o ./$(OBJ_DIR)/ft_list_size_bonus.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strcmp.s -o ./$(OBJ_DIR)/ft_strcmp.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_sort_bonus.s -o ./$(OBJ_DIR)/ft_list_sort_bonus.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_remove_if_bonus.s -o ./$(OBJ_DIR)/ft_list_remove_if_bonus.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_simd_memchr_bonus.s -o ./$(OBJ_DIR)/ft_simd_memchr_bonus.o
	@ ar rcs $(BONUS_NAME).a ./$(OBJ_DIR)/ft_atoi_base_bonus.o ./$(OBJ_DIR)/ft_list_push_front_bonus.o ./$(OBJ_DIR)/ft_list_size_bonus.o ./$(OBJ_DIR)/ft_strcmp.o ./$(OBJ_DIR)/ft_list_sort_bonus.o ./$(OBJ_DIR)/ft_list_remove_if_bonus.o ./$(OBJ_DIR)/ft_simd_memchr_bonus.o

# ---------------------------------------------------------------------------- #
#                                    Tests                                     #
# ---------------------------------------------------------------------------- #

test: $(LIB)
	gcc main.c $(LIB) -o $(TEST)
	./$(TEST)

test_bonus:
	@ mkdir -p $(OBJ_DIR)
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_atoi_base_bonus.s -o ./$(OBJ_DIR)/ft_atoi_base_bonus.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_push_front_bonus.s -o ./$(OBJ_DIR)/ft_list_push_front_bonus.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_size_bonus.s -o ./$(OBJ_DIR)/ft_list_size_bonus.o
	@ $(NASM) $(NFLAGS) ./$(SRC_DIR)/ft_strcmp.s -o ./$(OBJ_DIR)/ft_strcmp.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_sort_bonus.s -o ./$(OBJ_DIR)/ft_list_sort_bonus.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_list_remove_if_bonus.s -o ./$(OBJ_DIR)/ft_list_remove_if_bonus.o
	@ $(NASM) $(NFLAGS) ./$(BONUS_SRC_DIR)/ft_simd_memchr_bonus.s -o ./$(OBJ_DIR)/ft_simd_memchr_bonus.o
	gcc bonus_main.c \
		./$(OBJ_DIR)/ft_atoi_base_bonus.o \
		./$(OBJ_DIR)/ft_list_push_front_bonus.o \
		./$(OBJ_DIR)/ft_list_size_bonus.o \
		./$(OBJ_DIR)/ft_strcmp.o \
		./$(OBJ_DIR)/ft_list_sort_bonus.o \
		./$(OBJ_DIR)/ft_list_remove_if_bonus.o \
		./$(OBJ_DIR)/ft_simd_memchr_bonus.o \
		-o $(TEST_BONUS)
	./$(TEST_BONUS)

# ---------------------------------------------------------------------------- #
#                                   Meta                                       #
# ---------------------------------------------------------------------------- #

all: $(NAME)

clean:
	@ rm -rf $(OBJ_DIR)

fclean: clean
	@ rm -f $(NAME) $(LIB) $(BONUS_NAME) $(BONUS_NAME).a $(TEST) $(TEST_BONUS)

re: fclean all

.PHONY: all bonus test test_bonus clean fclean re