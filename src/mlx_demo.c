#include "../cub3d.h"

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
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_set_cursor_mode(game_data->mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(game_data->mlx, ft_anim_sprite, game_data);
	mlx_loop_hook(game_data->mlx, ft_anim_door, game_data);
	mlx_loop_hook(game_data->mlx, ft_psychodelic, game_data);
	mlx_loop_hook(game_data->mlx, ft_draw_image, game_data);
	mlx_loop_hook(game_data->mlx, ft_keyboad_hook, game_data);
	mlx_cursor_hook(game_data->mlx, ft_cursor_hook, game_data);
	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
	return(EXIT_SUCCESS);
}
