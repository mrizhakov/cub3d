#include "../cub3d.h"

void	draw_textures(t_raycast data)
{
	float	i;
	float	prev_pixel;

	i = data.offSet * 4;
	while (data.top < - 10)
	{
		data.top += data.err;
		i += data.texture->width * 4;
	}
	while (data.top < data.bott - 1)
	{
		prev_pixel = data.top;
		put_pixel(data.img, data.column, (int)data.top,
					convertColors(data.texture, i, data.height));
		data.top += data.err;
		while (data.top - prev_pixel > 1)
			put_pixel(data.img, data.column, (int)++prev_pixel,
						convertColors(data.texture, i, data.height));
		i += data.texture->width * 4;
		if (data.top > WINDOW_HEIGHT + 10)
			break;
	}
}

t_slope	init_slope_data(uint32_t x0, uint32_t y0,
		uint32_t x1, uint32_t y1, mlx_image_t* image)
{
	t_slope slope;

	bzero(&slope, sizeof(slope));
	slope.img = image;
	slope.x0 = x0;
	slope.y0 = y0;
	slope.x1 = x1;
	slope.y1 = y1;
	slope.dx = x0 - x1;
	if (x0 < x1)
		slope.dx = x1 - x0;
	slope.dy = y0 - y1;
	if (y0 < y1)
		slope.dy = y1 - y0;
	slope.sx = -1;
	if (x0 < x1)
		slope.sx = 1;
	slope.sy = -1;
	if (y0 < y1)
		slope.sy = 1;
	if (slope.dx > slope.dy)
		slope.err = slope.dx / 2;
	else
		slope.err = -slope.dy / 2;
	return (slope);
}
void drawLine(t_slope data, uint32_t color)
{
	while (1)
	{
		put_pixel_uint(data.img, data.x0, data.y0, color);
		if (data.x0 == data.x1 && data.y0 == data.y1)
			break;
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

// -----------------------------------------------------------------------------

int32_t ft_float_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_draw_image(void* param)
{
	t_game *game_data;
	t_float_pixel h_start;
	uint32_t color = ft_float_pixel(56, 56, 56 ,255);

	game_data = (t_game *)param;
	h_start.y = 0;
	h_start.x = 0;
	h_start.color = color;
	if (game_data->redraw_minimap == 0)
	{
		draw_black_background(game_data);
		draw_fov(game_data);
		draw_minimap(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
		draw_player(game_data, game_data->player, 4);
		draw_sprites(game_data);
		draw_map_sprite(game_data, NULL, 10);
	}
	// mlx_focus(game_data->mlx);
}



int	init_data(t_game *game_data)
{
	if (!(game_data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(game_data->img = mlx_new_image(game_data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT))) //static image here
	{
		mlx_close_window(game_data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game_data->mlx, game_data->img, 0, 0) == -1) //static image here
	{
		mlx_close_window(game_data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	game_data->animat_time = mlx_get_time();
	return (EXIT_SUCCESS);
}

int32_t mlx_run(t_game *game_data)
{
	if (init_data(game_data))
		return (EXIT_FAILURE);
	if (game_data->icon)
		mlx_set_icon(game_data->mlx, game_data->icon);
	// mlx_set_setting(MLX_FULLSCREEN, true);
	// mlx_set_cursor_mode(game_data->mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(game_data->mlx, ft_animation, game_data);
	mlx_loop_hook(game_data->mlx, ft_draw_image, game_data);
	mlx_loop_hook(game_data->mlx, ft_keyboad_hook, game_data);
	mlx_cursor_hook(game_data->mlx, ft_cursor_hook, game_data);
	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
	return(EXIT_SUCCESS);
}
