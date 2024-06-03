/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:37:44 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 19:15:28 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_ray_data(t_game *game_data,
			int column_id, t_raycast *ray, float ray_angle)
{
	float	perp_distance;
	float	wall_strip_height;

	perp_distance = ray->distance * cos((ray_angle - game_data->player_angle));
	wall_strip_height = (game_data->texture_width / perp_distance)
		* game_data->dist_proj_plane;
	ray->top = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
	ray->bott = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
	ray->height = ray->bott - ray->top;
	ray->img = game_data->img;
	ray->err = ray->height / ray->texture->height;
	ray->column = column_id;
}

static void	draw_3d_surface(t_game *game_data, int column_id, t_raycast ray)
{
	draw_line(init_slope_data((uint32_t)column_id, (uint32_t)ray.bott,
			(uint32_t)column_id, (uint32_t)WINDOW_HEIGHT - 1),
		game_data->color[F].rgb_color, game_data->img);
}

static void	wall_texture_calc(t_raycast *ray, t_game *game_data)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_left)
			ray->texture = game_data->textures[WE];
		else if (ray->is_ray_facing_right)
			ray->texture = game_data->textures[EA];
		ray->offset = (int)ray->ver_wall_hit_y % game_data->texture_width;
	}
	else
	{
		if (ray->is_ray_facing_up)
			ray->texture = game_data->textures[NO];
		else if (ray->is_ray_facing_down)
			ray->texture = game_data->textures[SO];
		ray->offset = (int)ray->hor_wall_hit_x % game_data->texture_width;
	}
}

void	draw_3d_projection(t_game *game_data, int column_id,
			t_raycast ray, float ray_angle)
{
	ray.texture = game_data->textures[TEX_DOOR_OP];
	wall_texture_calc(&ray, game_data);
	fill_ray_data(game_data, column_id, &ray, ray_angle);
	if (game_data->psycho)
	{
		ray.offset = rand() % 1000;
		ray.texture = game_data->textures[TEX_PSY_1];
		game_data->color[C].rgb_color = ft_float_pixel(227, 61, 148, 255);
		game_data->color[F].rgb_color = ft_float_pixel(130, 94, 9, 255);
	}
	draw_textures(ray);
	draw_3d_surface(game_data, column_id, ray);
}

void	draw_3d_door(t_game *game_data, int column_id,
			t_raycast ray, float ray_angle)
{
	ray.texture = game_data->textures[ray.door[0]->texture];
	if (ray.texture == game_data->textures[TEX_DOOR_OP])
		return ;
	if (ray.was_hit_vertical)
		ray.offset = (int)ray.ver_wall_hit_y % game_data->texture_width;
	else
		ray.offset = (int)ray.hor_wall_hit_x % game_data->texture_width;
	fill_ray_data(game_data, column_id, &ray, ray_angle);
	if (game_data->psycho)
	{
		ray.offset = rand() % 1000;
		ray.texture = game_data->textures[TEX_PSY_2];
	}
	if (ray.distance < game_data->z_buffer[column_id])
	{
		draw_textures(ray);
		if (!ray.door[0]->isopen)
			game_data->z_buffer[column_id] = ray.distance;
	}
}
