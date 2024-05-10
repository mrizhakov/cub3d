/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:53:41 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/10 16:16:13 by ddavlety         ###   ########.fr       */
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

	x = 0;
	y = 0;
	while (y != MAZE_DIMENSION - 1)
	{
		while (x != MAZE_DIMENSION - 1)
		{
			game_maze->maze.g[y][x] = 'Z';
			x++;
		}
		x = 0;
		y++;
	}
	game_maze->maze.valid_maze = -1;
}

t_maze init_t_maze(t_maze maze) // ?? do we need this function?
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y != MAZE_DIMENSION - 1)
	{
		while (x != MAZE_DIMENSION - 1)
		{
			maze.g[y][x] = 'Z';
			x++;
		}
		x = 0;
		y++;
	}
	maze.valid_maze = -1;
	return (maze);
}

int	initialise_game(t_game *game_data)
{
	// textures

	// colors
	game_data->color[F].color[0] = -1;
	game_data->color[F].color[1] = -1;
	game_data->color[F].color[2] = -1;
	game_data->color[F].valid_rgb = -1;
	game_data->color[C].color[0] = -1;
	game_data->color[C].color[1] = -1;
	game_data->color[C].color[2] = -1;
	game_data->color[C].valid_rgb = -1;

	// maze parse
	game_data->player_init_dir = 1.0;
	game_data->maze_closed = -1;

	// player
	game_data->player = (t_double_pixel *)ft_calloc(sizeof(t_double_pixel), 1);
	if (!game_data->player)
		return (1);
	game_data->player->color = 0x00FF00FF;
	game_data->player_angle = M_PI / 2;
	game_data->player_turn_speed = TURNING_SPEED * (M_PI / 180);
	game_data->fov_angle = FOV * (M_PI / 180);
	game_data->num_rays = WINDOW_WIDTH / 1;

	// draw

	// maze
	init_maze(game_data);
	return (0);
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
	free(game_data);
}
