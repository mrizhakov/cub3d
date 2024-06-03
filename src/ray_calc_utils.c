/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:36:31 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 14:58:44 by ddavlety         ###   ########.fr       */
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

int	cast_type_calc(t_game *game_data, t_raycast *ray,
	t_casttype type, t_orientation orient)
{
	int	ray_type;
	int	y;
	int	x;

	y = 0;
	x = 0;
	ray_type = 0;
	if (orient == VERT)
	{
		y = (int)ray->next_vert_touch_y / game_data->texture_width;
		x = (int)ray->next_vert_touch_x / game_data->texture_width;
		ray_type = cast_type(game_data->maze.g[y][x], type);
		if (ray_type == W_DOOR)
			ray->door[VERT] = which_door(game_data, y, x);
	}
	else if (orient == HOR)
	{
		y = (int)ray->next_hor_touch_y / game_data->texture_width;
		x = (int)ray->next_hor_touch_x / game_data->texture_width;
		ray_type = cast_type(game_data->maze.g[y][x], type);
		if (ray_type == W_DOOR)
			ray->door[HOR] = which_door(game_data, y, x);
	}
	return (ray_type);
}
