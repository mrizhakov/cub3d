/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:53:41 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/16 22:49:20 by mrizakov         ###   ########.fr       */
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
	// game_data->dist_proj_plane = (WINDOW_WIDTH / 2) / tan(game_data->fov_angle / 2);
	// game_data->texture_width is the new MINIMAP_SQUARE_SIDE_LEN, please adjust to the correct size of texture width
	game_data->texture_width = 512;
	game_data->dist_proj_plane = (WINDOW_WIDTH / 2) / tan(game_data->fov_angle / 2);
	// uncomment this line to get a psychodelic effect
    // dist_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	init_maze(game_data);
	return (0);
}

void free_textures(t_game *game_data)
{
	int	i;

	if (game_data->textures[NO])
		mlx_delete_texture(game_data->textures[NO]);
	if (game_data->textures[SO])
		mlx_delete_texture(game_data->textures[SO]);
	if (game_data->textures[WE])
		mlx_delete_texture(game_data->textures[WE]);
	if (game_data->textures[EA])
		mlx_delete_texture(game_data->textures[EA]);
	i = 0;
	while(i < 4)
		game_data->textures[i++] = NULL;
	if (game_data->icon)
		mlx_delete_texture(game_data->icon);
	game_data->icon = NULL;
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
