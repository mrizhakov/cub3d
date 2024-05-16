/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_demo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:48:34 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/16 19:20:48 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static mlx_image_t* image;

void	draw_pixel(uint8_t *pixel, t_color color)
{
	*(pixel++) = color.red;
	*(pixel++) = color.green;
	*(pixel++) = color.blue;
	*(pixel++) = color.alpha;
}

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color)
{
	uint8_t		*pixelstart;

	if (!img)
		ft_putendl_fd("Image does not exist", 2);
	if (!(x < img->width))
	{
		ft_putendl_fd("Pixel is out of bounds (axes x)", 2);
		printf("iso_x: %u width: %u\n", x, img->width);
	}
	if (!(y < img->height))
	{
		ft_putendl_fd("Pixel is out of bounds (axes y)", 2);
		printf("iso_y: %u height: %u\n", y, img->height);
	}
	pixelstart = &img->pixels[(y * img->width + x) * BPP];
	draw_pixel(pixelstart, color);
}

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double transform(double value) {
    const double center = 0.4; // Center of transformation
    const double scale = 10.0; // Scale factor for significance
    double shifted = value - center; // Shift to make center at 0
    double transformed = sigmoid(scale * shifted); // Apply sigmoid function
    return transformed;
}

t_color convertColors(mlx_texture_t* texture, uint32_t index, double distance)
{
	t_color		color;

	color.red = texture->pixels[index];
	color.green = texture->pixels[index + 1];
	color.blue = texture->pixels[index + 2];
	color.alpha = texture->pixels[index + 3];
	distance = transform(distance / WINDOW_HEIGHT);
	color.red = distance * color.red;
	color.green = distance * color.green;
	color.blue = distance * color.blue;
	return color;
}

double calculate_pixel_move(double wall_top_pixel, double wall_bottom_pixel, uint32_t height)
{
	double	err;

	err = (wall_bottom_pixel - wall_top_pixel) / height;
	if (err <= 1)
		return (wall_bottom_pixel + err);
	else
		return (wall_top_pixel + 1);
}

void	draw_textures(t_game *game_data, int column_id, double wall_top_pixel, double wall_bottom_pixel)
{
	uint32_t		i;
	uint32_t		height;
	double			prev_pixel;
	double			err;
	static uint32_t	j;
	double			wall_height;

	i = 0 + j;
	height = game_data->textures->north->height;
	wall_height = wall_bottom_pixel - wall_top_pixel;
	while (wall_top_pixel < wall_bottom_pixel - 1)
	{
		prev_pixel = wall_top_pixel;
		put_pixel(image, column_id, (int)wall_top_pixel, convertColors(game_data->textures->north, i, wall_height));
		err = (wall_bottom_pixel - wall_top_pixel) / height;
		wall_top_pixel += err;
		while ((int)(wall_top_pixel - prev_pixel > 1))
			put_pixel(image, column_id, (int)++prev_pixel, convertColors(game_data->textures->north, i, wall_height));
		height--;
		if (i >= game_data->textures->north->height * game_data->textures->north->width * 4)
			i = 0;
		i += game_data->textures->north->width * 4;
	}
	j = j + 4;
	if (j == game_data->textures->north->width)
		j = 0;
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

        mlx_put_pixel(image, x0, y0, color);

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
            mlx_put_pixel(image, start.x, start.y, start.color);
            start.x++;
        }
        while (start.x > end.x)
        {
            mlx_put_pixel(image, start.x, start.y, start.color);
            start.x--;
        }
        if (start.x == end.x)
        {
            mlx_put_pixel(image, start.x, start.y, start.color);
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
            mlx_put_pixel(image, start.x, start.y, start.color);
            start.y++;
        }
        while (start.y > end.y)
        {
            mlx_put_pixel(image, start.x, start.y, start.color);
            start.y--;
        }
        if (start.y == end.y)
        {
            mlx_put_pixel(image, start.x, start.y, start.color);
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


        // other potentially usefull drawing functions

        // draw_grid(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        // draw_minimap_with_border(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        // game_data->redraw_minimap = draw_minimap(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        // draw_ray(game_data, game_data->player_angle);
    }
}

void ft_keyboad_hook(void* param)
{
    t_game *game_data = param;

    // int player_y_check;
    // int player_x_check;

    // player_y_check = game_data->player->y;
    // player_x_check = game_data->player->x;

    if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game_data->mlx);
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_W))
        game_data->player_walk_dir = 1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_S))
        game_data->player_walk_dir = -1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_A))
        game_data->player_walk_strafe = -1;
    if (mlx_is_key_down(game_data->mlx, MLX_KEY_D))
        game_data->player_walk_strafe = 1;
    if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
		game_data->player_turn_dir = -1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
		game_data->player_turn_dir = 1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_E))
		printf("Action key triggered\n");
    if (game_data->player_walk_dir != 0 || game_data->player_turn_dir != 0 || game_data->player_walk_strafe != 0)
        update_pos(game_data);
}

void ft_cursor_hook(double xpos, double ypos, void* param)
{
	t_point	cursor;
	t_game	*game_data;

	cursor = ((t_game *)param)->cursor;
	game_data = (t_game *)param;
	if (cursor.x == 0)
	{
		game_data->cursor.x = xpos;
		return ;
	}
	if (cursor.x > xpos)
		game_data->player_turn_dir = -1;
	else if (cursor.x < xpos)
		game_data->player_turn_dir = 1;
	game_data->cursor.x = xpos;
	update_pos(game_data);
	(void)ypos;
}

void	init_data(t_game *game_data)
{

	game_data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
}

int32_t mlx_run(t_game *game_data)
{
	mlx_texture_t	*icon;

	if (!(game_data->mlx = mlx_init(WINDOW_HEIGHT, WINDOW_WIDTH, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(game_data->mlx, WINDOW_HEIGHT, WINDOW_WIDTH))) //static image here
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
	icon = mlx_load_png(ICON);
	if (!icon)
		ft_putendl_fd("Warning: icon is not set", 2);
	else
		mlx_set_icon(game_data->mlx, icon);
	mlx_set_cursor_mode(game_data->mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(game_data->mlx, ft_draw_image, game_data);
	mlx_loop_hook(game_data->mlx, ft_keyboad_hook, game_data);
	mlx_cursor_hook(game_data->mlx, ft_cursor_hook, game_data);
	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
    return(EXIT_SUCCESS);
}
