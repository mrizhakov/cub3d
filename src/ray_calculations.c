/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:35:49 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 14:52:02 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_horiz_calc(t_game *game_data, t_raycast *ray, float ray_angle)
{
	ray->yintercept = floor(game_data->player->y
			/ game_data->texture_width) * game_data->texture_width;
	if (ray->is_ray_facing_down)
		ray->yintercept += ray->is_ray_facing_down * game_data->texture_width;
	ray->xintercept = game_data->player->x + (ray->yintercept
			- game_data->player->y) / tan(ray_angle);
	ray->ystep = game_data->texture_width;
	if (ray->is_ray_facing_up)
		ray->ystep *= ray->is_ray_facing_up * -1;
	ray->xstep = game_data->texture_width / tan(ray_angle);
	if (ray->is_ray_facing_right)
		ray->xstep = game_data->texture_width / tan(ray_angle);
	if (ray->is_ray_facing_left && ray->xstep > 0)
		ray->xstep *= -1;
	if (ray->is_ray_facing_right && ray->xstep < 0)
		ray->xstep *= -1;
	ray->next_hor_touch_x = ray->xintercept;
	ray->next_hor_touch_y = ray->yintercept;
	if (ray->is_ray_facing_up)
		ray->next_hor_touch_y--;
}

void	ray_horiz_loop(t_game *game_data, t_raycast *ray, t_casttype type)
{
	int	ray_type;

	while (ray->next_hor_touch_x >= 0 && ray->next_hor_touch_y >= 0
		&& ray->next_hor_touch_y / game_data->texture_width < MAZE_DIMENSION
		&& ray->next_hor_touch_x / game_data->texture_width < MAZE_DIMENSION)
	{
		ray_type = cast_type_calc(game_data, ray, type, HOR);
		if (ray_type)
		{
			if (!(ray_type == W_DOOR && ray->door[HOR]->isopen))
			{
				ray->found_hor_hit = 1;
				ray->hor_wall_hit_x = ray->next_hor_touch_x;
				ray->hor_wall_hit_y = ray->next_hor_touch_y;
			}
			break ;
		}
		ray->next_hor_touch_x += ray->xstep;
		ray->next_hor_touch_y += ray->ystep;
	}
}

void	ray_vert_calc(t_game *game_data, t_raycast *ray, float ray_angle)
{
	ray->xintercept = floor(game_data->player->x
			/ game_data->texture_width) * game_data->texture_width;
	if (game_data->psycho)
		ray->xintercept = (game_data->player->x
				/ MINIMAP_SQUARE_SIDE_LEN) * MINIMAP_SQUARE_SIDE_LEN;
	if (ray->is_ray_facing_right)
		ray->xintercept += ray->is_ray_facing_right
			* game_data->texture_width;
	ray->yintercept = game_data->player->y + (ray->xintercept
			- game_data->player->x) * tan(ray_angle);
	ray->xstep = game_data->texture_width;
	if (ray->is_ray_facing_left)
		ray->xstep *= ray->is_ray_facing_left * -1;
	ray->ystep = game_data->texture_width * tan(ray_angle);
	if (ray->is_ray_facing_up && ray->ystep > 0)
		ray->ystep *= -1;
	if (ray->is_ray_facing_down && ray->ystep < 0)
		ray->ystep *= -1;
	ray->next_vert_touch_x = ray->xintercept;
	ray->next_vert_touch_y = ray->yintercept;
	if (ray->is_ray_facing_left)
		ray->next_vert_touch_x--;
}

void	ray_vert_loop(t_game *game_data, t_raycast *ray, t_casttype type)
{
	int	ray_type;

	while (ray->next_vert_touch_x >= 0 && ray->next_vert_touch_y >= 0
		&& ray->next_vert_touch_y / game_data->texture_width <= MAZE_DIMENSION
		&& ray->next_vert_touch_x / game_data->texture_width <= MAZE_DIMENSION)
	{
		ray_type = cast_type_calc(game_data, ray, type, VERT);
		if (ray_type)
		{
			if (!(ray_type == W_DOOR && ray->door[VERT]->isopen))
			{
				ray->found_vert_hit = 1;
				ray->ver_wall_hit_x = ray->next_vert_touch_x;
				ray->ver_wall_hit_y = ray->next_vert_touch_y;
			}
			break ;
		}
		ray->next_vert_touch_x += ray->xstep;
		ray->next_vert_touch_y += ray->ystep;
	}
}

void	ray_shortest_distance(t_raycast *ray, t_game *game_data)
{
	if (ray->found_hor_hit)
		ray->distance_hor = distance_between_points(game_data->player->x,
				game_data->player->y, ray->hor_wall_hit_x, ray->hor_wall_hit_y);
	else
		ray->distance_hor = FLT_MAX;
	if (ray->found_vert_hit)
		ray->distance_vert = distance_between_points(game_data->player->x,
				game_data->player->y, ray->ver_wall_hit_x, ray->ver_wall_hit_y);
	else
		ray->distance_vert = FLT_MAX;
	if (ray->distance_hor < ray->distance_vert)
	{
		ray->shortest_wall_hit_x = ray->hor_wall_hit_x;
		ray->shortest_wall_hit_y = ray->hor_wall_hit_y;
		ray->distance = ray->distance_hor;
	}
	else
	{
		ray->shortest_wall_hit_x = ray->ver_wall_hit_x;
		ray->shortest_wall_hit_y = ray->ver_wall_hit_y;
		ray->distance = ray->distance_vert;
		ray->door[0] = ray->door[VERT];
	}
	if (ray->distance_vert < ray->distance_hor)
		ray->was_hit_vertical = 1;
}
