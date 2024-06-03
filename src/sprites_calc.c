/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:46:59 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 12:34:20 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_height(t_game *game_data, t_sprite *vis_sprite)
{
	float	sprite_height;
	float	top_pixel;
	float	bott_pixel;

	sprite_height = (game_data->texture_width
			/ vis_sprite->distance) * game_data->dist_proj_plane;
	top_pixel = (WINDOW_HEIGHT / 2) - (sprite_height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	bott_pixel = (WINDOW_HEIGHT / 2) + (sprite_height / 2);
	if (bott_pixel >= WINDOW_HEIGHT)
		bott_pixel = WINDOW_HEIGHT - 1;
	vis_sprite->top_pixel = top_pixel;
	vis_sprite->bott_pixel = bott_pixel;
	vis_sprite->dimentions = sprite_height;
	vis_sprite->err_line = sprite_height
		/ game_data->textures[vis_sprite->texture]->height;
}

void	set_width(t_game *game_data, t_sprite *vis_sprite)
{
	float	pos_x;
	float	left_x;
	float	right_x;

	pos_x = tan(vis_sprite->angle) * game_data->dist_proj_plane;
	left_x = (WINDOW_WIDTH / 2) + pos_x - vis_sprite->dimentions / 2;
	right_x = left_x + vis_sprite->dimentions;
	vis_sprite->left_pixel = left_x;
	vis_sprite->right_pixel = right_x;
	vis_sprite->err_column = vis_sprite->dimentions / game_data->texture_width;
}

void	sort_sprites(t_sprite sprites[SPRITES_CO])
{
	uint32_t	i;
	uint32_t	j;
	t_sprite	tmp;

	j = 0;
	while (j <= SPRITES_CO && sprites[j].texture)
	{
		i = 0;
		while (i < SPRITES_CO && sprites[i + 1].texture)
		{
			if (sprites[i].distance == 0
				|| sprites[i].distance < sprites[i + 1].distance)
			{
				tmp = sprites[i];
				sprites[i] = sprites[i + 1];
				sprites[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

void	detect_vis_sprites(t_game *game_data)
{
	t_sprite		*sprites;
	float			angle_sprite;
	int				i;

	sprites = game_data->sprites;
	i = -1;
	while (sprites[++i].texture)
	{
		if (sprites[i].taken)
			continue ;
		sprites[i].visible = false;
		angle_sprite = calcul_angle_sprite(game_data->player_angle,
				&sprites[i], game_data->player);
		sprites[i].distance = distance_between_points(game_data->player->x,
				game_data->player->y, sprites[i].x, sprites[i].y);
		if (sprites[i].distance < ACTION_DIST)
			sprites[i].taken = true;
		else if (angle_sprite < (game_data->fov_angle / 2))
		{
			sprites[i].angle = atan2(sprites[i].y - game_data->player->y,
					sprites[i].x - game_data->player->x)
				- game_data->player_angle + M_PI;
			sprites[i].visible = true;
		}
	}
}

void	sprites_calculations(t_game	*game_data)
{
	int			i;

	detect_vis_sprites(game_data);
	i = 0;
	while (game_data->sprites[i].texture)
	{
		if (game_data->sprites[i].visible)
		{
			set_height(game_data, &game_data->sprites[i]);
			set_width(game_data, &game_data->sprites[i]);
			sort_sprites(game_data->sprites);
		}
		i++;
	}
}
