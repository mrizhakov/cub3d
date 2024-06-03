/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:12:56 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 11:41:09 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int32_t	check_pix(t_float_pixel pix)
{
	if (pix.x < 0 || pix.y < 0
		|| pix.x > WINDOW_WIDTH - 1 || pix.y > WINDOW_HEIGHT -1)
	{
		ft_putendl_fd("Warning\nInvalid pixel", 2);
		return (0);
	}
	else
		return (1);
}

int32_t	ft_float_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	transform(float value)
{
	const float	center = 0.4;
	const float	scale = 10.0;
	float		shifted;
	float		transformed;

	shifted = value - center;
	transformed = 1 / (1 + exp(-(scale * shifted)));
	return (transformed);
}

void	draw_minimap_fov(t_game *game_data, t_raycast ray, t_raycast ray_door)
{
	t_slope	slope;

	if (ray.distance > ray_door.distance
		&& ray_door.door[0] && !ray_door.door[0]->isopen)
		slope = init_slope_data((uint32_t)game_data->player->x
				* MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)game_data->player->y * MINIMAP_SQUARE_SIDE_LEN
				/ game_data->texture_width,
				(uint32_t)ray_door.shortest_wall_hit_x
				* MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)ray_door.shortest_wall_hit_y * MINIMAP_SQUARE_SIDE_LEN
				/ game_data->texture_width);
	else
		slope = init_slope_data((uint32_t)game_data->player->x
				* MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)game_data->player->y * MINIMAP_SQUARE_SIDE_LEN
				/ game_data->texture_width,
				(uint32_t)ray.shortest_wall_hit_x * MINIMAP_SQUARE_SIDE_LEN
				/ game_data->texture_width,
				(uint32_t)ray.shortest_wall_hit_y * MINIMAP_SQUARE_SIDE_LEN
				/ game_data->texture_width);
	draw_line(slope, game_data->player->color, game_data->img);
}
