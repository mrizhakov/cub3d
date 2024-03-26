# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrizhakov <mrizhakov@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 18:02:05 by mrizakov          #+#    #+#              #
#    Updated: 2024/03/26 17:57:47 by mrizhakov        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#LIBMLX = MLX42/build/libmlx42.a
#MLXFLAGS = -L/path/to/glfw/library -lglfw -lm
CFLAGS = -Wall -Werror -Wextra -g3

#LIBFT_PATH		=	./libft
#LIBFT			=	$(LIBFT_PATH)/libft.a

SRC= main.c error_handling.c parsing.c

all:
#	cc $(SRC) $(LIBFT) $(LIBMLX) $(MLXFLAGS) -o cub3d
	cc $(SRC) $(CFLAGS) -o cub3d
	
name:
#	make -C $(LIBFT_PATH) all
	make all
	
clean:
#	make -C $(LIBFT_PATH) fclean
	make fclean

fclean:
	@rm cub3d

re: fclean all


