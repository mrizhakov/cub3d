/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_demo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:48:34 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/20 22:44:14 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static mlx_image_t* image;

// void ft_draw_square(t_game *game_data)
// {
// 	(void)game_data;
// 	int side_len;
// 	int x;
// 	int y;
// 	int offset_x;
// 	int offset_y;



// 	side_len = 10;
// 	x = 0;
// 	y = 0;
// 	offset_x = WINDOW_WIDTH / 2;
// 	offset_y = WINDOW_HEIGHT / 2;

// 	while (i! = side_len)
// 	{
// 		mlx_put_string
// 		i++;
// 	}

// 	int offset_y;
	
	
	
// }

int32_t check_pix(t_pixel pix)
{
    if (pix.x < 0 || pix.y < 0 || pix.x > WINDOW_WIDTH || pix.y > WINDOW_HEIGHT)
    {
        perror("Invalid pixel");
        return (0);
    }
    else
        return(1);
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

#include <stdio.h>
#include <stdlib.h>

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



int32_t draw_line(t_game *game_data, t_pixel start, t_pixel end)
{
    (void)game_data;
    if (check_pix(start) && check_pix(end))
    {
        if (start.x == end.x)
            draw_v_line(game_data, start, end);
        if (start.y == end.y)
            draw_h_line(game_data, start, end);
        else
        {
            drawLine(start.x, start.y, end.x, end.y, start.color);
        }
        return (1);
    }
    return(0);
}

int32_t draw_rectangle(t_game *game_data, t_pixel start, t_pixel end)
{
    (void)game_data;
    if (check_pix(start) && check_pix(end))
    {
        while(start.x < end.x)
        {
            drawLine(start.x, start.y, start.x, end.y, start.color);
            // printf("Drawing string\n");
            start.x++;
        }
        while(start.x > end.x)
        {
            drawLine(start.x, start.y, start.x, end.y, start.color);
            // printf("Drawing string\n");
            start.x--;
        }
        if(start.x == end.x)
        {
            drawLine(start.x, start.y, start.x, end.y, start.color);
            // printf("Drawing string\n");
            // start.x--;
        }
        return(1);
    }
    return(0);
}


int32_t draw_square(t_game *game_data, t_pixel start, unsigned int side_len)
{
    unsigned int i;
    
    i = 0;
    (void)game_data;
    if (check_pix(start))
    {
        while (i != side_len)
        {
            drawLine(start.x, start.y, start.x, start.y + side_len, start.color);
            // printf("Drawing line\n");
            i++;
            start.x++;
        }
        // printf("Not drawing string\n");
        return(1);
    }
    return(0);
}


int32_t draw_grid(t_game *game_data, t_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    t_pixel origin;
    origin = start;
    int border;
    border = 1;
    // printf("Printing out maze for educational purposes: \n\n");
    while (y != MAZE_DIMENSION - 1)
    {


        while (x != MAZE_DIMENSION - 1)
        {
            drawLine(start.x, start.y, start.x + side_len, start.y, start.color);
            drawLine(start.x, start.y, start.x, start.y + side_len, start.color);


            // if (game_data->maze.g[y][x] == 1)
            //     draw_square(game_data, start, side_len);
            // printf("%i", game_data->maze.g[y][x]);
            start.x += side_len;
            x++;
        }
        //printf("\n");
        // drawLine(start.x, start.y, start.x, start.y + side_len, start.color);

        
        x = 0;
        start.x = (side_len + border) * x;
        start.y += side_len + border *2;
        // start.y += side_len;

        y++;
    }
    // printf("\nIs the maze valid? %i\n", game_data->maze.valid_maze);
    return(1);
}

int32_t draw_minimap(t_game *game_data, t_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    t_pixel origin;
    origin = start;

    t_pixel player;
    player.color = 0xFF00FFFF;
    // int border;
    // border = 1;
    // printf("Printing out maze for educational purposes: \n\n");
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            if (is_valid_int(game_data->maze.g[y][x]))
            {
                drawLine(start.x, start.y, start.x + side_len, start.y, start.color);
                drawLine(start.x, start.y, start.x , start.y + side_len, start.color);
                // draw_square(game_data, start, side_len);

            }
            if (game_data->maze.g[y][x] == 1)
                draw_square(game_data, start, side_len);
            if (game_data->maze.g[y][x] == 3)
            {
                player.x = start.x;
                player.y = start.y;
                draw_square(game_data, player, side_len);
            }
            // printf("%i", game_data->maze.g[y][x]);
            // start.x += side_len + border;
            start.x += side_len;

            x++;
        }
        // printf("\n");
        x = 0;
        start.x = origin.x + side_len * x;

        // start.x = origin.x + (side_len + border) * x;
        // start.y += side_len + border *2;
        start.y += side_len;

        y++;
    }
    // printf("\nIs the maze valid? %i\n", game_data->maze.valid_maze);
    return(1);
}

int32_t draw_player(t_game *game_data, t_pixel *player, unsigned int side_len)
{
    (void)player;
    // game_data->player->x = game_data->player_init_loc[0] * side_len;
    // game_data->player->y = game_data->player_init_loc[1] * side_len;

    draw_square(game_data, *game_data->player, side_len);
    
    // draw_line(game_data, *game_data->player, )
    // draw_square(game_data, *player, side_len);
    // (void)game_data;
    // int x;
    // int y;

    // x = 0;
    // y = 0;
    // t_pixel origin;
    // origin = start;
    // int border;
    // border = 1;
    // printf("Printing out maze for educational purposes: \n\n");
    // while (y != MAZE_DIMENSION - 1)
    // {
    //     while (x != MAZE_DIMENSION - 1)
    //     {
    //         if (game_data->maze.g[y][x] == 'N')
    //             draw_square(game_data, start, side_len);
    //         printf("%i", game_data->maze.g[y][x]);
    //         start.x += side_len + border;
    //         x++;
    //     }
    //     printf("\n");
    //     x = 0;
    //     start.x = origin.x + (side_len + border) * x;
    //     start.y += side_len + border *2;
    //     y++;
    // }
    // printf("\nIs the maze valid? %i\n", game_data->maze.valid_maze);
    return(1);
}







void ft_generate_rectangle_data(t_game *game_data)
{
	int column;

	int offset_y = WINDOW_HEIGHT / 3;
	int rectangle_height = WINDOW_HEIGHT/ 3 /2;
	long my_color = 0xFFFF00FF;
	column = 0;
	while (column != WINDOW_WIDTH - 1)
	{

		game_data->wall->column_start[column].y = offset_y;
		printf("Column is %i\n", game_data->wall->column_start[column].y);

		game_data->wall->column_start[column].x = column;
		game_data->wall->column_start[column].color = my_color;
		
		game_data->wall->column_end[column].y = offset_y + rectangle_height;
		game_data->wall->column_end[column].x = column;
		game_data->wall->column_end[column].color = my_color;

		column++;
	}
}

void ft_draw_rectangle(mlx_image_t *image, t_game *game_data)
{
	(void)game_data;
	(void)image;
	int columns;
	

	columns = 0;
	// while (columns != WINDOW_WIDTH - 1)
	// {
	// 	mlx_put_pixel(image, game_data->wall->column_start[columns].x, game_data->wall->column_start[columns].y, game_data->wall->column_start[columns].color);
	// 	mlx_put_pixel(image, game_data->wall->column_end[columns].x, game_data->wall->column_end[columns].y, game_data->wall->column_end[columns].color);

	// 	printf("Put pixel at START x %i, y %i, color %u\n", game_data->wall->column_start[columns].x, game_data->wall->column_start[columns].y, game_data->wall->column_start[columns].color);
	// 	printf("Put pixel at END x %i, y %i, color %u\n", game_data->wall->column_end[columns].x, game_data->wall->column_end[columns].y, game_data->wall->column_end[columns].color);
	// 	columns++;
	// }
}

// rotated.x = p.x * cos(angle) - p.y * sin(angle);
//     rotated.y = p.x * sin(angle) + p.y * cos(angle);

int32_t	conv_x(int32_t x, int32_t y, double angle)
{
	return (x * cos(angle) - y * sin(angle));

	// return ((x - y) * cos(0.523599));
}

int32_t	conv_y(int32_t x, int32_t y, double angle)
{
	return (x * sin(angle) + y * cos(angle));
	// return ((x + y) * sin(0.523599));

	
}


t_pixel rotatePoint(t_pixel p, t_pixel center, double angle) {
    t_pixel rotated;
    rotated.x = center.x + (p.x - center.x) * cos(angle) - (p.y - center.y) * sin(angle);
    rotated.y = center.y + (p.x - center.x) * sin(angle) + (p.y - center.y) * cos(angle);
    return rotated;
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

void prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check)
{
    (void)game_data;
    (void)player_y_check;
    (void)player_x_check;
    

    
    
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
    
    t_pixel h_end;
    h_end.y = 42;
    h_end.x = 42;
    h_end.color = color;

    t_pixel black_square;
    black_square.y = 0;
    black_square.x = 0;
    black_square.color = 0x000000FF;

    
    // game_data->player->y = 0;
    // game_data->player->x = 0;
    // game_data->player->color = 0xFF00FFFF;
    
    int side_len;
    side_len = 25;

    // draw_h_line(game_data, h_end, h_start);
    // draw_v_line(game_data, h_end, h_start);
    // draw_line(game_data, h_end, h_start);

    // draw_rectangle(game_data, h_start, h_end);
    //prevent_wall_collisions(game_data);

    draw_square(game_data, black_square, WINDOW_HEIGHT - 1);
    //draw_grid(game_data, h_start, side_len);

    draw_minimap(game_data, h_start, side_len);
    draw_player(game_data, game_data->player, 3);


    // draw_player(game_data, h_start, side_len);






	
	// ft_draw_square(game_data);


	// ft_generate_rectangle_data(game_data);
	// ft_projection_rectangle_data(game_data);
	// ft_draw_rectangle(image, game_data);
	
	//mlx_put_pixel(image, 50, 200, color); //first X, then Y
}

void ft_hook(void* param)
{
    t_game *game_data = param;

    int player_y_check;
    int player_x_check;
    
    player_y_check = game_data->player->y;
    player_x_check = game_data->player->x;
    

	if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game_data->mlx);
	}
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_UP))
    {
        game_data->player->y -= game_data->player_step;
        // if (prevent_wall_collisions)
        //     game_data->player->y -= game_data->player_step; 
    }
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_DOWN))
        game_data->player->y += game_data->player_step;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
        game_data->player->x -= game_data->player_step;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
        game_data->player->x += game_data->player_step;


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

	if (!(game_data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
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
	init_wall(game_data);
	mlx_loop_hook(game_data->mlx, ft_randomize, game_data);
	mlx_loop_hook(game_data->mlx, ft_hook, game_data);

	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
    return(EXIT_SUCCESS);

}