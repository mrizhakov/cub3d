/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:46:59 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/01 15:47:00 by ddavlety         ###   ########.fr       */
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
	top_pixel = (WINDOW_HEIGHT / 2)  - (sprite_height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	bott_pixel = (WINDOW_HEIGHT / 2)  + (sprite_height / 2);
	if (bott_pixel >= WINDOW_HEIGHT)
		bott_pixel = WINDOW_HEIGHT - 1;
	vis_sprite->top_pixel = top_pixel;
	vis_sprite->bott_pixel = bott_pixel;
	vis_sprite->dimentions = sprite_height;
	vis_sprite->err_line = sprite_height / game_data->textures[vis_sprite->texture]->height;
}

void	set_width(t_game *game_data, t_sprite *vis_sprite)
{
	float	posX;
	float	leftX;
	float	rightX;

	posX = tan(vis_sprite->angle) * game_data->dist_proj_plane;
	leftX = (WINDOW_WIDTH / 2) + posX - vis_sprite->dimentions / 2;
	rightX = leftX + vis_sprite->dimentions;
	vis_sprite->left_pixel = leftX;
	vis_sprite->right_pixel = rightX;
	vis_sprite->err_column = vis_sprite->dimentions / game_data->texture_width;
}

static float	calculate_angle(float p_angle, t_sprite *sprite, t_float_pixel *player)
{
	float angle_sprite;

	angle_sprite = p_angle
		- atan2(sprite->y - player->y, sprite->x - player->x);
	if (angle_sprite > M_PI)
		angle_sprite -= 2 * M_PI;
	if (angle_sprite < -M_PI)
		angle_sprite += 2 * M_PI;
	angle_sprite = fabs(angle_sprite);
	return (angle_sprite);
}

void	detect_vis_sprites(t_game *game_data)
{
	t_sprite	*sprites;
	t_float_pixel	*player;
	float		angle_sprite;
	int			i;

	sprites = game_data->sprites;
	player = game_data->player;
	i = -1;
	while (sprites[++i].texture)
	{
		if (sprites[i].taken)
			continue ;
		sprites[i].visible = false;
		angle_sprite = calculate_angle(game_data->player_angle, &sprites[i], player);
		sprites[i].distance = distance_between_points(player->x, player->y, sprites[i].x, sprites[i].y);
		if (sprites[i].distance < ACTION_DIST)
			sprites[i].taken = true;
		else if (angle_sprite < (game_data->fov_angle / 2))
		{
			sprites[i].angle = atan2(sprites[i].y - player->y, sprites[i].x - player->x) - game_data->player_angle + M_PI;
			sprites[i].visible = true;
		}
	}
}

int	init_sprites(t_game *game_data, char t, int x, int y)
{
	int			i;

	i = 0;
	while (game_data->sprites[i].texture)
		i++;
	if (i >= 10)
		return (1);
	game_data->sprites[i].x = x * game_data->texture_width + game_data->texture_width / 2;
	game_data->sprites[i].y = y * game_data->texture_width + game_data->texture_width / 2;
	game_data->sprites[i].map_x = x;
	game_data->sprites[i].map_y = y;
	if (t == 'M')
		game_data->sprites[i].texture = TEX_MUSHR;
	return (0);
}

static void	draw_sprite_line(t_game *game_data, t_sprite sprite,
								float offset, float line)
{
	float			left;
	mlx_texture_t	*texture;
	float			index;
	float			prev_left;
	t_color			color;

	texture = game_data->textures[sprite.texture];
	index = offset * 4;
	left = sprite.left_pixel;
	while (left < 0)
	{
		index += 4;
		left += sprite.err_column;
	}
	while (left < sprite.right_pixel)
	{
		color = convert_colors(texture, index, sprite.dimentions);
		if (sprite.distance < game_data->z_buffer[(int)left]
				&& texture->pixels[(int)index + 3] != 0)
			put_pixel(game_data->img, left, line, color);
		prev_left = left;
		left += sprite.err_column;
		while ((left - prev_left) > 1 && prev_left < sprite.right_pixel - 1)
		{
			if (sprite.distance < game_data->z_buffer[(int)++prev_left]
				&& texture->pixels[(int)index + 3] != 0)
				put_pixel(game_data->img, prev_left, line, color);
		}
		index += 4;
		if (left >= WINDOW_WIDTH
			|| index + 3 >= texture->width * texture->height * 4)
			break ;
	}
}

static void	draw_sprite(t_game *game_data, t_sprite	sprite)
{
	float			line;
	float			prev_line;
	uint32_t		texOffset;
	mlx_texture_t	*texture;

	line = sprite.top_pixel;
	texOffset = 0;
	texture = game_data->textures[sprite.texture];
	while (line < 0 || texture->pixels[texOffset * 4 + (texture->width * 2) + 3] == 0)
	{
		line += sprite.err_line;
		texOffset += texture->width;
	}
	while (line < sprite.bott_pixel)
	{
		draw_sprite_line(game_data, sprite, texOffset, line);
		texOffset += texture->width;
		if (texOffset >= texture->width * texture->height)
			break ;
		prev_line = line;
		line += sprite.err_line;
		while ((line - prev_line) > 1 && prev_line < sprite.bott_pixel - 1)
			draw_sprite_line(game_data, sprite, texOffset, ++prev_line);
		if (line > WINDOW_HEIGHT)
			break ;
	}
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

void	draw_sprites(t_game	*game_data)
{
	int			i;

	i = 0;
	while (game_data->sprites[i].texture)
	{
		if (game_data->sprites[i].visible)
		{
			draw_sprite(game_data, game_data->sprites[i]);
		}
		i++;
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
