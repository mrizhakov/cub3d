/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_demo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:48:34 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/03 22:48:34 by mrizakov         ###   ########.fr       */
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

void ft_randomize(void* param)
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
        // draw_grid(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        // draw_minimap_with_border(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        draw_minimap(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);

        // game_data->redraw_minimap = draw_minimap(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
        draw_player(game_data, game_data->player, 3);
        // raycast(game_data);
        
        draw_ray(game_data, game_data->player_angle);

        draw_fov(game_data);

    }
    
    //raycast
    // init_structs(ray_data, game_data);
    
}

void ft_hook(void* param)
{
    t_game *game_data = param;

    int player_y_check;
    int player_x_check;

    player_y_check = game_data->player->y;
    player_x_check = game_data->player->x;

    if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game_data->mlx);
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_W))
    {
        game_data->player_walk_dir = 1;
        // player_y_check += game_data->player_dir_y;
        // player_x_check += game_data->player_dir_x;
        // prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP, player_x_check, -MAP_PADDING, 0);
    }
        // prevent_wall_collisions(game_data, player_y_check - PLAYER_STEP, player_x_check, -MAP_PADDING, 0);
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_S))
    {
        game_data->player_walk_dir = -1;

        // player_y_check -= game_data->player_dir_y;
        // player_x_check -= game_data->player_dir_x;
        // prevent_wall_collisions(game_data, player_y_check + PLAYER_STEP, player_x_check, MAP_PADDING, 0);
    }
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_A))
    {
        game_data->player_turn_dir = -1;
        
        // game_data->player_angle -= 0.1;
        // check_angle_overflow(game_data);
    }
        // prevent_wall_collisions(game_data, player_y_check , player_x_check - PLAYER_STEP, 0, -MAP_PADDING);
    if (mlx_is_key_down(game_data->mlx, MLX_KEY_D))
    {
        game_data->player_turn_dir = 1;

        // game_data->player_angle += 0.1;
        // check_angle_overflow(game_data);
    }
    if (game_data->player_walk_dir != 0 || game_data->player_turn_dir != 0)
        update_pos(game_data);
        // prevent_wall_collisions(game_data, player_y_check , player_x_check + PLAYER_STEP, 0, MAP_PADDING);
// 	if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
//         prevent_wall_collisions(game_data, player_y_check , player_x_check - PLAYER_STEP, 0, -MAP_PADDING);
//     if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
//         prevent_wall_collisions(game_data, player_y_check , player_x_check + PLAYER_STEP, 0, MAP_PADDING);
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
	if (!(game_data->mlx = mlx_init(WINDOW_HEIGHT, WINDOW_WIDTH, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		free_on_exit(game_data); // added
		return(EXIT_FAILURE);
	}
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
    // printf("Initial player pos in pixels: x %f and y %f\n", game_data->player->x,  game_data->player->y);
    // printf("Initial player pos in int[2] array is: init_loc[0] or y %i and init_loc[1] x %i\n", game_data->player_init_loc[0],  game_data->player_init_loc[1]);
    // printf("Initial player pos in int[2] array is: y %i and x %i\n", game_data->player_init_loc[0],  game_data->player_init_loc[1]);
    // printf("PLAYER STEP is %i\n", PLAYER_STEP);
    // printf("No offset\n");
    // printf("Initial player direction is %f\n", game_data->player_init_dir);
	mlx_loop_hook(game_data->mlx, ft_randomize, game_data);
	mlx_loop_hook(game_data->mlx, ft_hook, game_data);

	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
    return(EXIT_SUCCESS);

}