NAME = cub3D

LIBFT = ./libft/libft.a
MLX42 = ./MLX42/build/libmlx42.a
SRCS	:= $(shell find ./src -iname "*.c")
MLX42_dir = ./MLX42

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror
CC = cc 
MLX42FLAGS = -ldl -lglfw -pthread -lm  

all:	buildlib	$(NAME) 

$(NAME): $(LIBFT) libmlx $(MLX42) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX42) $(MLX42FLAGS)
	@echo "\033[33m=== cub3D ===\033[36m=== COMPILED  ===\033[0m"

buildlib:
	@if ! [ -d "$(MLX42_dir)" ]; then \
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_dir); \
	fi

$(LIBFT):
	@$(MAKE) -C ./libft
	@echo "\033[33m=== libft ===\033[36m=== COMPILED  ===\033[0m"

libmlx:
	@cd $(MLX42_dir) && cmake -B build && cmake --build build -j4
	@echo "\033[33m=== mlx ===\033[36m=== COMPILED  ===\033[0m"

clean: 
	@$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
	@echo "\033[33m=== ALL ===\033[36m=== CLEANED ===\033[0m"

fclean:
	@$(MAKE) fclean -C ./libft
	@cd ./MLX42 && rm -rf build
	@rm -rf ./MLX42
	$(RM) $(OBJS) $(NAME)
	@echo "\033[33m=== ALL ===\033[36m=== FULLY CLEANED ===\033[0m"

re:	fclean all

.PHONY: all clean fclean re