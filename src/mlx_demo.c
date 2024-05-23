#include "../cub3d.h"

static mlx_image_t* image;

void	draw_textures(mlx_texture_t *texture, int column_id, double wall_top_pixel,
						double wall_bottom_pixel, int textOffX)
{
	uint32_t		i;
	// uint32_t		height;
	double			prev_pixel;
	double			err;
	double			wall_height;

	i = 0 + ((textOffX) * 4);
	// height = texture->height;
	wall_height = wall_bottom_pixel - wall_top_pixel;
	err = wall_height / texture->height;
	while (wall_top_pixel < - 10)
	{
		wall_top_pixel += err;
		i += texture->width * 4;
	}
	while (wall_top_pixel < wall_bottom_pixel - 1)
	{
		prev_pixel = wall_top_pixel;
		put_pixel(image, column_id, (int)wall_top_pixel,
					convertColors(texture, i, wall_height));
		// err = (wall_bottom_pixel - wall_top_pixel) / height;
		wall_top_pixel += err;
		while (wall_top_pixel - prev_pixel > 1)
			put_pixel(image, column_id, (int)++prev_pixel,
						convertColors(texture, i, wall_height));
		i += texture->width * 4;
		if (wall_top_pixel > WINDOW_HEIGHT + 10)
			break;
	}
}

// Function to draw a line between two points (x0, y0) and (x1, y1), need to be made norm-compliant and readable
void drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
    int32_t dx;
    int32_t dy;

    if (x1 > x0)
        dx = x1 - x0;
    else
        dx = x0 - x1;
    if (y1 > y0)
        dy = y1 - y0;
    else
        dy = y0 - y1;

    // uint32_t dx = abs(x1 - x0);
    // uint32_t dy = abs(y1 - y0);
    int32_t sx = x0 < x1 ? 1 : -1;
    int32_t sy = y0 < y1 ? 1 : -1;
    int32_t err = (dx > dy ? dx : -dy) / 2;
    int32_t e2;

    while (1) {
        // Plot current point
        // printf("Putting pixel at (%d, %d), color %d\n", x0, y0, color);

        put_pixel_uint(image, x0, y0, color);

        // Check if we've reached the end point
        if (x0 == x1 && y0 == y1) break;
        // Calculate next point
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

int32_t draw_h_line(t_game *game_data, t_double_pixel start, t_double_pixel end)
{
    (void)game_data;
    if (check_pix(start) && check_pix(end) && start.y == end.y)
    {
        while (start.x < end.x)
        {
            put_pixel_uint(image, start.x, start.y, start.color);
            start.x++;
        }
        while (start.x > end.x)
        {
            put_pixel_uint(image, start.x, start.y, start.color);
            start.x--;
        }
        if (start.x == end.x)
        {
            put_pixel_uint(image, start.x, start.y, start.color);
        }
        return(1);
    }
    else
    {
        perror("Invalid horizontal line position");
        return(0);
    }
}

int32_t draw_v_line(t_game *game_data, t_double_pixel start, t_double_pixel end)
{
    (void)game_data;
    if (check_pix(start) && check_pix(end) && start.x == end.x)
    {
        while (start.y < end.y)
        {
            put_pixel_uint(image, start.x, start.y, start.color);
            start.y++;
        }
        while (start.y > end.y)
        {
            put_pixel_uint(image, start.x, start.y, start.color);
            start.y--;
        }
        if (start.y == end.y)
        {
            put_pixel_uint(image, start.x, start.y, start.color);
        }
        return(1);
    }
    else
    {
        perror("Invalid vertical line position");
        return(0);
    }
}

// -----------------------------------------------------------------------------

int32_t ft_double_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_draw_image(void* param)
{
	t_game *game_data;
	game_data = (t_game *)param;
	uint32_t color = ft_double_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);

    t_double_pixel h_start;
    h_start.y = 0;
    h_start.x = 0;
    h_start.color = color;
    if (game_data->redraw_minimap == 0)
    {
        draw_black_background(game_data);
        draw_fov(game_data);
        draw_minimap(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        draw_player(game_data, game_data->player, 3);
		draw_sprites(game_data);
		draw_map_sprite(game_data, NULL, 3);

        // other potentially usefull drawing functions

        // draw_grid(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        // draw_minimap_with_border(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        // game_data->redraw_minimap = draw_minimap(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        // draw_ray(game_data, game_data->player_angle);
    }
	// mlx_focus(game_data->mlx);
}



void	init_data(t_game *game_data)
{
	game_data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
}

int32_t mlx_run(t_game *game_data)
{
	if (!(game_data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(game_data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT))) //static image here
	{
		mlx_close_window(game_data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game_data->mlx, image, 0, 0) == -1) //static image here
	{
		mlx_close_window(game_data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	game_data->img = image;
	game_data->animat_time = mlx_get_time();
	if (game_data->icon)
		mlx_set_icon(game_data->mlx, game_data->icon);
	// mlx_set_setting(MLX_FULLSCREEN, true);
	// mlx_set_cursor_mode(game_data->mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(game_data->mlx, ft_animation, game_data);
	mlx_loop_hook(game_data->mlx, ft_draw_image, game_data);
	mlx_loop_hook(game_data->mlx, ft_keyboad_hook, game_data);
	// mlx_cursor_hook(game_data->mlx, ft_cursor_hook, game_data);
	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
    return(EXIT_SUCCESS);
}
