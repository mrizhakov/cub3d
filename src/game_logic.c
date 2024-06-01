/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:43:55 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/01 14:58:35 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	prevent_wall_collisions(t_game *game_data, float player_y_check,
	float player_x_check, int map_padding)
{
	(void)game_data;
	if (player_x_check >= 0 && player_y_check >= 0
		&& player_x_check <= game_data->texture_width * (MAZE_DIMENSION - 1)
		&& player_y_check <= game_data->texture_width * (MAZE_DIMENSION - 1))
	{
		if (!find_wall(game_data->maze, game_data->player->y,
				player_x_check, map_padding, game_data->texture_width)
			&& !find_door(game_data, game_data->player->y,
				player_x_check, map_padding, game_data->texture_width))
			game_data->player->x = player_x_check;
		if (!find_wall(game_data->maze, player_y_check,
				game_data->player->x, map_padding, game_data->texture_width)
			&& !find_door(game_data, player_y_check,
				game_data->player->x, map_padding, game_data->texture_width))
			game_data->player->y = player_y_check;
	}
	return (1);
}

float	check_angle_overflow(t_game *game_data, float player_angle)
{
	if (player_angle < 0)
		player_angle += 2 * M_PI;
	if (player_angle > (2 * M_PI))
		player_angle -= 2 * M_PI;
	game_data->player_turn_dir = 0;
	return (player_angle);
}

void	player_move(t_game *game_data, float *x, float *y)
{
	float	move_step;

	*x -= sin(game_data->player_angle)
		* PLAYER_STEP * game_data->player_strafe_dir;
	*y += cos(game_data->player_angle)
		* PLAYER_STEP * game_data->player_strafe_dir;
	move_step = game_data->player_walk_dir * PLAYER_STEP;
	*x += cos(game_data->player_angle) * move_step;
	*y += sin(game_data->player_angle) * move_step;
	game_data->player_walk_dir = 0;
	game_data->player_strafe_dir = 0;
}

void	update_pos(t_game *game_data)
{
	float	player_y_check;
	float	player_x_check;

	player_x_check = 0;
	player_y_check = 0;
	game_data->redraw_minimap = 0;
	game_data->player_angle += game_data->player_turn_dir * TURNING_SPEED;
	game_data->player_angle = check_angle_overflow(game_data,
			game_data->player_angle);
	player_move(game_data, &player_x_check, &player_y_check);
	if (player_x_check || player_y_check)
		prevent_wall_collisions(game_data,
			game_data->player->y + player_y_check,
			game_data->player->x + player_x_check,
			game_data->texture_width / 4);
	sprites_calculations(game_data);
}
