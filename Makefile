CC := cc
FLAGS := -Wall -Wextra -Werror -g
NAME := cub3D
RM := rm -f
LIBMLX = ./MLX42
SRC_DIR := src/
EXE_SOURCE :=	draw.c error_handling.c error_messages.c game_logic.c main.c memory_management.c minimap.c \
				mlx_demo.c parsing.c raycast.c textures.c texture_color.c pixel_color.c sprites.c doors.c \
				hooks.c psycodelic.c ray_utils.c doors_actions.c draw_utils.c draw_funct.c find_utils.c
EXE_SRCS = $(addprefix $(SRC_DIR), $(EXE_SOURCE))
OBJ_DIR := obj/
INC := -I. -IMLX42/include -IMLX42/include/glad -IMLX42/include/KHR -IMLX42/include/lodepng -IMLX42/include/MLX42
LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a
LIB := -Llibft -lft -ldl -lglfw -pthread -lm -LMLX42/build -lmlx42
OBJ = $(EXE_SRCS:.c=.o)
OBJ := $(addprefix $(OBJ_DIR), $(OBJ))
TEST := maps/

all: $(NAME) $(TEST)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ_DIR) $(OBJ) cub3d.h
	$(CC) $(FLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)

$(LIBMLX):
	@if ! [ -d "$(LIBMLX)" ]; then \
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null 2>&1 && make -C $(LIBMLX)/build -j4 > /dev/null 2>&1;\
	fi

$(LIBFT) :
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
#	$(RM) -r $(TEST)
#	$(RM) test.sh
#	$(RM) -r $(LIBMLX)

re: fclean all

$(TEST):
	@if ! [ -d "$(TEST)" ]; then \
	git clone git@github.com:ddavlet/test_maps_cub3D.git $(TEST); \
	mv $(TEST)test.sh ./test.sh; \
	fi

.PHONY: all clean re fclean
