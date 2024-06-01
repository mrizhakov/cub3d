/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:09:53 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/01 15:29:21 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int32_t	draw_rectangle(t_game *game_data,
	t_float_pixel start, t_float_pixel end)
{
	(void)game_data;
	if (check_pix(start) && check_pix(end))
	{
		while (start.x < end.x)
		{
			draw_line(init_slope_data(start.x, start.y, start.x,
					end.y, game_data->img), start.color);
			start.x++;
		}
		while (start.x > end.x)
		{
			draw_line(init_slope_data(start.x, start.y, start.x,
					end.y, game_data->img), start.color);
			start.x--;
		}
		if (start.x == end.x)
		{
			draw_line(init_slope_data(start.x, start.y, start.x,
					end.y, game_data->img), start.color);
		}
		return (1);
	}
	return (0);
}

void	draw_black_background(t_game *game_data)
{
	t_float_pixel	black_background;
	t_float_pixel	end;

	black_background.y = 0;
	black_background.x = 0;
	black_background.color = game_data->color[C].rgb_color;
	end.x = WINDOW_WIDTH - 1;
	end.y = WINDOW_HEIGHT - 1;
	end.color = 0;
	draw_rectangle(game_data, black_background, end);
}

int32_t	draw_square(t_game *game_data, t_float_pixel start, uint32_t side_len)
{
	uint32_t	i;

	i = 0;
	(void)game_data;
	if (check_pix(start))
	{
		while (i != side_len)
		{
			draw_line(init_slope_data(start.x, start.y, start.x,
					start.y + side_len, game_data->img), start.color);
			i++;
			start.x++;
		}
		return (1);
	}
	return (0);
}

void	draw_line(t_slope data, uint32_t color)
{
	while (1)
	{
		put_pixel_uint(data.img, data.x0, data.y0, color);
		if (data.x0 == data.x1 && data.y0 == data.y1)
			break ;
		data.e2 = data.err;
		if (data.e2 > -data.dx)
		{
			data.err -= data.dy;
			data.x0 += data.sx;
		}
		if (data.e2 < data.dy)
		{
			data.err += data.dx;
			data.y0 += data.sy;
		}
	}
}

void	draw_textures(t_raycast data)
{
	float	i;
	float	prev_pixel;

	i = data.offSet * 4;
	while (data.top < -10)
	{
		data.top += data.err;
		i += data.texture->width * 4;
	}
	while (data.top < data.bott - 1)
	{
		prev_pixel = data.top;
		put_pixel(data.img, data.column, (int)data.top,
			convert_colors(data.texture, i, data.height));
		data.top += data.err;
		while (data.top - prev_pixel > 1)
			put_pixel(data.img, data.column, (int)++prev_pixel,
				convert_colors(data.texture, i, data.height));
		i += data.texture->width * 4;
		if (data.top > WINDOW_HEIGHT + 10)
			break ;
	}
}
