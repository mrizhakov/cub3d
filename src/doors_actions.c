/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:56:16 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 19:21:14 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static float	calculate_angle(float p_angle,
								t_doors *door, t_float_pixel *player)
{
	float	angle_door;

	angle_door = p_angle - atan2(door->y - player->y, door->x - player->x);
	if (angle_door > M_PI)
		angle_door -= 2 * M_PI;
	if (angle_door < -M_PI)
		angle_door += 2 * M_PI;
	angle_door = fabs(angle_door);
	return (angle_door);
}

void	detect_vis_door(t_game *game_data)
{
	t_doors			*doors;
	t_float_pixel	*player;
	float			angle_sprite;
	int				i;

	doors = game_data->doors;
	player = game_data->player;
	i = 0;
	while (doors[i].texture)
	{
		angle_sprite = calculate_angle(game_data->player_angle,
				&doors[i], player);
		if (angle_sprite < (game_data->fov_angle / 2))
		{
			doors[i].distance = distance_between_points(player->x,
					player->y, doors[i].x, doors[i].y);
			doors[i].angle = atan2(doors[i].y - player->y,
					doors[i].x - player->x) - game_data->player_angle + M_PI;
			doors[i].visible = true;
		}
		else
			doors[i].visible = false;
		i++;
	}
}

t_doors	*closiest_door(t_game *game_data)
{
	int		i;
	int		closiest;
	float	distance;

	distance = FLT_MAX;
	i = 0;
	closiest = 0;
	while (game_data->doors[i].texture)
	{
		if (game_data->doors[i].distance < distance
			&& game_data->doors[i].visible)
		{
			distance = game_data->doors[i].distance;
			closiest = i;
		}
		i++;
	}
	return (&game_data->doors[closiest]);
}

void	open_door(t_game *game_data)
{
	t_doors	*door;

	detect_vis_door(game_data);
	door = closiest_door(game_data);
	if (!door)
		return ;
	if (door->distance < (float)ACTION_DIST
		&& !door->isopen && mlx_get_time() - door->animation_time > 2)
	{
		door->isopen = true;
		door->animation_time = mlx_get_time();
	}
	else if (door->distance < (float)ACTION_DIST
		&& mlx_get_time() - door->animation_time > 2)
	{
		door->isopen = false;
		door->animation_time = mlx_get_time();
	}
}
