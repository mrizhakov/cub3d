/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:36:31 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 19:03:15 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cast_type(char c, t_casttype type)
{
	if (c == '1' && type == W_WALL)
		return (W_WALL);
	else if (c == 'D' && type == W_DOOR)
		return (W_DOOR);
	else if (c == 'M' && type == W_SPRITE)
		return (W_SPRITE);
	else
		return (W_NONE);
}

int	cast_type_hor(t_game *game_data, t_raycast *ray, t_casttype type)
{
	int	ray_type;
	int	y;
	int	x;

	y = 0;
	x = 0;
	ray_type = 0;
	if (ray->is_ray_facing_up)
		y = ((int)ray->next_hor_touch_y - 1) / game_data->texture_width;
	else
		y = (int)ray->next_hor_touch_y / game_data->texture_width;
	x = (int)ray->next_hor_touch_x / game_data->texture_width;
	ray_type = cast_type(game_data->maze.g[y][x], type);
	if (ray_type == W_DOOR)
		ray->door[HOR] = which_door(game_data, y, x);
	return (ray_type);
}

int	cast_type_vert(t_game *game_data, t_raycast *ray, t_casttype type)
{
	int	ray_type;
	int	y;
	int	x;

	y = 0;
	x = 0;
	ray_type = 0;
	if (ray->is_ray_facing_left)
		x = ((int)ray->next_vert_touch_x - 1) / game_data->texture_width;
	else
		x = (int)ray->next_vert_touch_x / game_data->texture_width;
	y = (int)ray->next_vert_touch_y / game_data->texture_width;
	ray_type = cast_type(game_data->maze.g[y][x], type);
	if (ray_type == W_DOOR)
		ray->door[VERT] = which_door(game_data, y, x);
	return (ray_type);
}
