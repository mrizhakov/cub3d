CC := cc #-fsanitize=address
FLAGS := -g -Wall -Wextra -Werror
NAME := cub3D
RM := rm -f
LIBMLX = ./MLX42
SRC_DIR := src/
EXE_SOURCE :=	cleanup.c draw.c error_handling.c error_messages.c game_logic.c main.c memory_management.c minimap.c \
				mlx_demo.c parsing.c raycast.c testing.c textures.c parsing2.c
EXE_SRCS = $(addprefix $(SRC_DIR), $(EXE_SOURCE))
OBJ_DIR := obj/
INC := -I. -IMLX42/include -IMLX42/include/glad -IMLX42/include/KHR -IMLX42/include/lodepng -IMLX42/include/MLX42
LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a
LIBFT_SRC := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putunsnbr_fd.c ft_putnbr_hex_fd.c ft_printf.c ft_get_next_line.c ft_atoi_binar.c ft_strjoinfree.c \
		ft_chararr_len.c ft_chararr_append.c ft_chararr_dup.c ft_intarrdup.c ft_free_ptr.c
LIBFT_SOURCE := $(addprefix $(LIB_DIR), $(LIBFT_SRC))
LIBFT_OBJ = $(LIBFT_SOURCE:.c=.o)
LIB := -Llibft -lft -ldl -L/usr/local/lib/glfw -lglfw -pthread -lm -LMLX42/build -lmlx42
OBJ = $(EXE_SRCS:.c=.o)
OBJ := $(addprefix $(OBJ_DIR), $(OBJ))
TEST := maps/

all: $(NAME) $(TEST)

$(NAME): $(LIBMLX) $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)

$(LIBMLX):
	@if ! [ -d "$(LIBMLX)" ]; then \
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null 2>&1 && make -C $(LIBMLX)/build -j4 > /dev/null 2>&1;\
	fi

$(LIBFT) : $(LIBFT_OBJ)
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) fclean

fclean: clean
	$(RM) $(NAME)
# $(RM) -r $(TEST)
# $(RM) -r $(LIBMLX)

re: fclean all

$(TEST):
	@if ! [ -d "$(TEST)" ]; then \
	git clone git@github.com:ddavlet/test_maps_cub3D.git $(TEST); \
	fi

.PHONY: all clean re fclean
