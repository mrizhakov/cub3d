/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:31:11 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 21:49:26 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_orientation(t_raycast *ray, float ray_angle)
{
	ray->is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

void	ray_calculations(t_raycast *ray, t_game *game_data,
			float ray_angle, t_casttype type)
{
	ft_bzero(ray, sizeof(*ray));
	ray_orientation(ray, ray_angle);
	ray_horiz_calc(game_data, ray, ray_angle);
	ray_horiz_loop(game_data, ray, type);
	ray_vert_calc(game_data, ray, ray_angle);
	ray_vert_loop(game_data, ray, type);
	ray_shortest_distance(ray, game_data);
}

void	cast_ray(t_game *game_data, float ray_angle, int column_id)
{
	t_raycast	ray;
	t_raycast	ray_door;

	ray_calculations(&ray, game_data, ray_angle, W_WALL);
	ray_calculations(&ray_door, game_data, ray_angle, W_DOOR);
	draw_3d_projection(game_data, column_id, ray, ray_angle);
	game_data->z_buffer[column_id] = ray.distance;
	if (ray_door.door[0])
		draw_3d_door(game_data, column_id, ray_door, ray_angle);
	draw_minimap_fov(game_data, ray, ray_door);
}

void	draw_fov(t_game *game_data)
{
	float	ray_angle;
	int		column_id;
	int		dose;

	column_id = 0;
	if (game_data->psycho == 2)
		dose = 100;
	else
		dose = 2;
	while (column_id < game_data->num_rays)
	{
		game_data->redraw_minimap = 0;
		ray_angle = game_data->player_angle
			+ atan((column_id - game_data->num_rays / dose)
				/ game_data->dist_proj_plane);
		if (game_data->psycho == 3)
			ray_angle = game_data->player_angle
				+ tan((column_id - game_data->num_rays / dose)
					/ game_data->dist_proj_plane);
		ray_angle = check_angle_overflow(game_data, ray_angle);
		if (column_id < game_data->num_rays)
			cast_ray(game_data, ray_angle, column_id);
		column_id++;
	}
	game_data->redraw_minimap = 1;
}
