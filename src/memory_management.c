/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:53:41 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/15 20:17:04 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void free_to_null_string(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void free_char_arr(char **str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

void init_maze(t_game *game_maze)
{
	int x;
	int y;

	y = 0;
	while (y < MAZE_DIMENSION)
	{
		x = 0;
		while (x < MAZE_DIMENSION)
		{
			game_maze->maze.g[y][x] = 'X';
			x++;
		}
		y++;
	}
}

int	initialise_game(t_game *game_data)
{
	game_data->player = (t_double_pixel *)ft_calloc(sizeof(t_double_pixel), 1);
	if (!game_data->player)
		return (1);
	game_data->player->color = 0x00FF00FF;
	game_data->player_angle = M_PI / 2;
	game_data->player_turn_speed = TURNING_SPEED * (M_PI / 180);
	game_data->fov_angle = FOV * (M_PI / 180);
	game_data->num_rays = WINDOW_WIDTH / 1;
	init_maze(game_data);
	return (0);
}

void free_textures(t_game *game_data)
{
	if (game_data->textures)
	{
		if (game_data->textures->north)
			mlx_delete_texture(game_data->textures->north);
		if (game_data->textures->east)
			mlx_delete_texture(game_data->textures->east);
		if (game_data->textures->west)
			mlx_delete_texture(game_data->textures->west);
		if (game_data->textures->south)
			mlx_delete_texture(game_data->textures->south);
		if (game_data->textures)
			free(game_data->textures);
		game_data->textures = NULL;
	}
}


void free_on_exit(t_game *game_data)
{
	if (!game_data)
		return ;
	free_to_null_string(&game_data->texture_filename[NO]);
	free_to_null_string(&game_data->texture_filename[SO]);
	free_to_null_string(&game_data->texture_filename[WE]);
	free_to_null_string(&game_data->texture_filename[EA]);
	if (game_data->player)
		free(game_data->player);
	free_textures(game_data);
	free(game_data);
}
