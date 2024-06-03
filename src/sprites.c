/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:46:59 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 15:35:09 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_sprite_line(t_game *game_data, t_sprite sprite,
								float offset, float line)
{
	float			left;
	mlx_texture_t	*texture;
	float			prev_left;
	t_color			color;

	texture = game_data->textures[sprite.texture];
	left = sprite.left_pixel;
	while (left < 0)
	{
		offset += 4;
		left += sprite.err_column;
	}
	while (left < sprite.right_pixel)
	{
		if (left >= WINDOW_WIDTH || texture->width
			* texture->height * 4 - 4 <= offset)
			break ;
		color = convert_colors(texture, offset, sprite.dimentions);
		if (sprite.distance < game_data->z_buffer[(int)left]
			&& texture->pixels[(int)offset + 3] != 0)
			put_pixel(game_data->img, left, line, color);
		prev_left = left;
		left += sprite.err_column;
		while ((left - prev_left) > 1 && prev_left < sprite.right_pixel - 1)
		{
			if (sprite.distance < game_data->z_buffer[(int)++prev_left]
				&& texture->pixels[(int)offset + 3] != 0)
				put_pixel(game_data->img, prev_left, line, color);
		}
		offset += 4;
	}
}

static void	draw_sprite(t_game *game_data, t_sprite	sprite,
		mlx_texture_t *texture)
{
	float			line;
	float			prev_line;
	uint32_t		tex_offset;

	line = sprite.top_pixel;
	tex_offset = 0;
	while (line < 0 || texture->pixels[tex_offset * 4
			+ (texture->width * 2) + 3] == 0)
	{
		line += sprite.err_line;
		tex_offset += texture->width;
	}
	while (line < sprite.bott_pixel)
	{
		draw_sprite_line(game_data, sprite, tex_offset * 4, line);
		tex_offset += texture->width;
		if (tex_offset >= texture->width * texture->height)
			break ;
		prev_line = line;
		line += sprite.err_line;
		while ((line - prev_line) > 1 && prev_line < sprite.bott_pixel - 1)
			draw_sprite_line(game_data, sprite, tex_offset * 4, ++prev_line);
		if (line > WINDOW_HEIGHT)
			break ;
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
			draw_sprite(game_data, game_data->sprites[i],
				game_data->textures[game_data->sprites[i].texture]);
		}
		i++;
	}
}
