/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_demo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:48:34 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/21 20:41:05 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static mlx_image_t* image;

// Function to draw a line between two points (x0, y0) and (x1, y1)
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
        mlx_put_pixel(image, x0, y0, color);
        // printf("(%d, %d)\n", x0, y0);

        // Check if we've reached the end point
        if (x0 == x1 && y0 == y1) break;

        // Calculate next point
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

int32_t draw_h_line(t_game *game_data, t_pixel start, t_pixel end)
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

int32_t draw_v_line(t_game *game_data, t_pixel start, t_pixel end)
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

void	ft_projection_rectangle_data(t_game *game_data)
{
	int columns;
	int offset = 600;

	columns = 0;

	// center_x = (game_data->wall->column_start[columns].x - game_data->wall->column_end[columns].x) / 2;
	// center_y = (game_data->wall->column_start[columns].y - game_data->wall->column_end[columns].y) / 2;
	double angle = M_PI / 4.0; // 45 degrees in radians

	t_pixel center;
	center.y =	game_data->wall->column_start[0].y;
	center.x =	game_data->wall->column_start[0].x;
	
	while (columns != WINDOW_WIDTH - 1)
	{
		// Rotate each point (x, y) by the angle around the center (center_x, center_y)
		// double new_y = (game_data->wall->column_start[columns].y - center_x) * sin(angle) + (y - center_y) * cos(angle) + center_y;

		// game_data->projection->column_start[columns].x = conv_x(game_data->wall->column_start[columns].x, game_data->wall->column_start[columns].y, angle);
		// game_data->projection->column_start[columns].y = conv_y(game_data->wall->column_start[columns].y, game_data->wall->column_start[columns].y, angle);

		// game_data->projection->column_end[columns].x = conv_x(game_data->wall->column_end[columns].x, game_data->wall->column_end[columns].y, angle);
		// game_data->projection->column_end[columns].y = conv_y(game_data->wall->column_end[columns].y, game_data->wall->column_end[columns].y, angle);

		game_data->projection->column_start[columns] = rotatePoint(game_data->wall->column_start[columns], center, angle);
		game_data->projection->column_end[columns] = rotatePoint(game_data->wall->column_end[columns], center, angle);

		// game_data->projection->column_start[columns] = conv_y(game_data->wall->column_start[columns].y, game_data->wall->column_start[columns].y, angle);

		// game_data->projection->column_end[columns].x = conv_x(game_data->wall->column_end[columns].x, game_data->wall->column_end[columns].y, angle);
		// game_data->projection->column_end[columns].y = conv_y(game_data->wall->column_end[columns].y, game_data->wall->column_end[columns].y, angle);

		game_data->projection->column_start[columns].color  = game_data->wall->column_start[columns].color;
		game_data->projection->column_end[columns].color  = game_data->wall->column_end[columns].color;

		game_data->projection->column_start[columns].x += offset;
		game_data->projection->column_end[columns].x += offset;

		
		// (game_data->wall->column_start[columns].x - center_x) * cos(angle) - (game_data->wall->column_start[columns].x - center_y) * sin(angle) + center_x;
		// game_data->projection->column_start[columns].y = (game_data->wall->column_start[columns].y - center_x) * sin(angle) + (game_data->projection->column_start[columns].y - center_y) * cos(angle) + center_y;
		// game_data->projection->column_start[columns].color  = game_data->wall->column_start[columns].color;

		
		// game_data->projection->column_end[columns].x = (game_data->wall->column_end[columns].x - center_x) * cos(angle) - (game_data->projection->column_end[columns].x - center_y) * sin(angle) + center_x;
		// game_data->projection->column_end[columns].y = (game_data->wall->column_end[columns].y - center_x) * sin(angle) + (game_data->projection->column_end[columns].y - center_y) * cos(angle) + center_y;
		// game_data->projection->column_end[columns].color  = game_data->wall->column_end[columns].color;
		
		printf("Converted pixel at START x %i, y %i, color %u\n", 
		game_data->projection->column_start[columns].x, 
		game_data->projection->column_start[columns].y, 
		game_data->projection->column_start[columns].color);
		printf("Converted pixel at END x %i, y %i, color %u\n", game_data->projection->column_end[columns].x, game_data->projection->column_end[columns].y, game_data->projection->column_end[columns].color);
		if (game_data->projection->column_start[columns].x < 1280 && game_data->projection->column_start[columns].y < 1280)
			mlx_put_pixel(image, game_data->projection->column_start[columns].x, game_data->projection->column_start[columns].y, game_data->projection->column_start[columns].color);
		if (game_data->projection->column_end[columns].x < 1280 && game_data->projection->column_end[columns].y < 1280)
			mlx_put_pixel(image, game_data->projection->column_end[columns].x, game_data->projection->column_end[columns].y, game_data->projection->column_end[columns].color);
		columns++;

	}
}


// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	t_game *game_data; 
	game_data = (t_game *)param;
	uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);

    t_pixel h_start;
    h_start.y = 0;
    h_start.x = 0;
    h_start.color = color;
    
    if (game_data->redraw_minimap == 0)
    {
    draw_black_background(game_data);
    // draw_grid(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
    // draw_minimap_with_border(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
    game_data->redraw_minimap = draw_minimap(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
    draw_player(game_data, game_data->player, 3);
    }
}

void ft_hook(void* param)
{
    t_game *game_data = param;

    int player_y_check;
    int player_x_check;

    player_y_check = game_data->player->y;
    player_x_check = game_data->player->x;


    // if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
	// 	mlx_close_window(game_data->mlx);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_UP))
    //     prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP, player_x_check);
    //     // if (prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP, player_x_check))
    //     //     player_y_check += PLAYER_STEP;
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_DOWN))
    //     prevent_wall_collisions(game_data, player_y_check + PLAYER_STEP, player_x_check);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
    //     prevent_wall_collisions(game_data, player_y_check, player_x_check - PLAYER_STEP);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
    //     prevent_wall_collisions(game_data, player_y_check, player_x_check + PLAYER_STEP);



    if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game_data->mlx);
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_UP))
        prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP, player_x_check, -MAP_PADDING, 0);
        // if (prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP, player_x_check))
        //     player_y_check += PLAYER_STEP;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_DOWN))
        prevent_wall_collisions(game_data, player_y_check + PLAYER_STEP, player_x_check, MAP_PADDING, 0);
        // prevent_wall_collisions(game_data, player_y_check + PLAYER_STEP + MAP_PADDING, player_x_check);
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
        prevent_wall_collisions(game_data, player_y_check , player_x_check - PLAYER_STEP, 0, -MAP_PADDING);
        // prevent_wall_collisions(game_data, player_y_check, player_x_check - PLAYER_STEP - MAP_PADDING);
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
        prevent_wall_collisions(game_data, player_y_check , player_x_check + PLAYER_STEP, 0, MAP_PADDING);

        // prevent_wall_collisions(game_data, player_y_check, player_x_check + PLAYER_STEP + MAP_PADDING);



    // if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
	// 	mlx_close_window(game_data->mlx);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_UP))
    //     prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP - MAP_PADDING, player_x_check);
    //     // if (prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP, player_x_check))
    //     //     player_y_check += PLAYER_STEP;
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_DOWN))
    //     prevent_wall_collisions(game_data, player_y_check + PLAYER_STEP + MAP_PADDING, player_x_check);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
    //     prevent_wall_collisions(game_data, player_y_check, player_x_check - PLAYER_STEP - MAP_PADDING);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
    //     prevent_wall_collisions(game_data, player_y_check, player_x_check + PLAYER_STEP + MAP_PADDING);


	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
	// 	mlx_close_window(game_data->mlx);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_UP))
    //     prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP - MAP_PADDING, player_x_check);
    //     // if (prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP, player_x_check))
    //     //     player_y_check += PLAYER_STEP;
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_DOWN))
    //     prevent_wall_collisions(game_data, player_y_check + PLAYER_STEP + MAP_PADDING, player_x_check);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
    //     prevent_wall_collisions(game_data, player_y_check, player_x_check - PLAYER_STEP - MAP_PADDING);
	// if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
    //     prevent_wall_collisions(game_data, player_y_check, player_x_check + PLAYER_STEP + MAP_PADDING);
        
    // if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	// {
	// 	mlx_close_window(mlx);
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_UP))
	// 	image->instances[0].y -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	image->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	image->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	image->instances[0].x += 5;
}

void initialise_game(t_game *game_data)
{
	initialise_to_null(game_data);
    // Initialize game window and graphics context
    //init_window();

    // Load textures, sprites, and map data
    load_textures(game_data);
    //load_map();

    // Initialize player position and direction
    //init_player();

    // Other initialization tasks...
}

void	init_data(t_game *game_data)
{

	game_data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
}

int32_t mlx_demo(t_game *game_data)
{
    // mlx_t* mlx;
	if (!(game_data->mlx = mlx_init(WINDOW_HEIGHT, WINDOW_WIDTH, "MLX42", true)))
	// if (!(game_data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		free_on_exit(game_data); // added
		return(EXIT_FAILURE);
	}
    
	// if (!(image = mlx_new_image(mlx, 128, 128))) //original line for MLX
	if (!(image = mlx_new_image(game_data->mlx, WINDOW_HEIGHT, WINDOW_WIDTH))) //static image here
	{
		mlx_close_window(game_data->mlx);
		puts(mlx_strerror(mlx_errno));
		free_on_exit(game_data); //added
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game_data->mlx, image, 0, 0) == -1) //static image here
	{
		mlx_close_window(game_data->mlx);
		puts(mlx_strerror(mlx_errno));
		free_on_exit(game_data); //added
		return(EXIT_FAILURE);
	}
	//init_wall(game_data);
    printf("Initial player pos in pixels: x %i and y %i\n", game_data->player->x,  game_data->player->y);
    printf("Initial player pos in int[2] array is: init_loc[0] or y %i and init_loc[1] x %i\n", game_data->player_init_loc[0],  game_data->player_init_loc[1]);
    printf("Initial player pos in int[2] array is: y %i and x %i\n", game_data->player_init_loc[0],  game_data->player_init_loc[1]);
    printf("PLAYER STEP is %i\n", PLAYER_STEP);
    printf("No offset\n");

    printf("Initial player direction is %f\n", game_data->player_init_dir);



	mlx_loop_hook(game_data->mlx, ft_randomize, game_data);
	mlx_loop_hook(game_data->mlx, ft_hook, game_data);

	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
    return(EXIT_SUCCESS);

}