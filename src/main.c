/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:23:44 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/20 00:26:44 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int main(int argc, const char *argv[])
// {
// 	(void)argv;
// 	error_handling(argc, argv);
// 	map_parsing();

// 	return (EXIT_SUCCESS);
// }

//MLX42 code example

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../MLX42/include/MLX42/MLX42.h"

// #define WIDTH 512
// #define HEIGHT 512

static mlx_image_t* image;


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
	int columns;

	columns = 0;
	while (columns != WINDOW_WIDTH - 1)
	{
		mlx_put_pixel(image, game_data->wall->column_start[columns].x, game_data->wall->column_start[columns].y, game_data->wall->column_start[columns].color);
		mlx_put_pixel(image, game_data->wall->column_end[columns].x, game_data->wall->column_end[columns].y, game_data->wall->column_end[columns].color);

		printf("Put pixel at START x %i, y %i, color %u\n", game_data->wall->column_start[columns].x, game_data->wall->column_start[columns].y, game_data->wall->column_start[columns].color);
		printf("Put pixel at END x %i, y %i, color %u\n", game_data->wall->column_end[columns].x, game_data->wall->column_end[columns].y, game_data->wall->column_end[columns].color);
		columns++;
	}
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




// void	ft_put_line(t_main *v)
// {
// 	if (v->old_x < v->new_x)
// 		v->sx = 1;
// 	else
// 		v->sx = -1;
// 	if (v->old_y < v->new_y)
// 		v->sy = 1;
// 	else
// 		v->sy = -1;
// 	v->err = v->dx + v->dy;
// 	ft_put_line_loop(v);
// }



// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	// (void)param;
	t_game *game_data; 
	game_data = (t_game *)param;
	// uint32_t color = ft_pixel(
	// 			rand() % 0xFF, // R
	// 			rand() % 0xFF, // G
	// 			rand() % 0xFF, // B
	// 			rand() % 0xFF  // A
	// 		);
	
	// t_wall *wall;

	// wall = malloc(sizeof(t_wall));
	
	// ft_generate_rectangle_data(game_data.wall, game_data);
	// init_wall(game_data);

	ft_generate_rectangle_data(game_data);
	ft_projection_rectangle_data(game_data);



	ft_draw_rectangle(image, game_data);

	// int columns;

	// columns = 0;
	// while (columns != WINDOW_WIDTH -1)
	// {
	// 	uint32_t color = ft_pixel(
	// 			rand() % 0xFF, // R
	// 			rand() % 0xFF, // G
	// 			rand() % 0xFF, // B
	// 			rand() % 0xFF  // A
	// 		);

	// 	mlx_put_pixel(image, wall->column_start[columns].x, wall->column_start[columns].y, color);

	// 	printf("Put pixel at x %i, y %i, color %u\n", wall->column_start[columns].x, wall->column_start[columns].y, wall->column_start[columns].color);

	// 	columns++;
	// }
	uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
	
	
	mlx_put_pixel(image, 50, 200, color); //first X, then Y

	
	
	// for (uint32_t i = 0; i < image->width; ++i)
	// {
	// 	for (uint32_t y = 0; y < image->height; ++y)
	// 	{
	// 		uint32_t color = ft_pixel(
	// 			rand() % 0xFF, // R
	// 			rand() % 0xFF, // G
	// 			rand() % 0xFF, // B
	// 			rand() % 0xFF  // A
	// 		);
	// 		mlx_put_pixel(image, i, y, color);
	// 	}
	// }
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
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

// -----------------------------------------------------------------------------

int32_t main(int argc, const char *argv[])
{
	mlx_t* mlx;


	(void)argc;
    (void)argv;

	t_game *game_data;
	game_data = malloc(sizeof(t_game));

    if (game_data == NULL)
    {
        perror("Error: Failed to allocate memory for game data");
        return EXIT_FAILURE;
    }
    // game_data->mlx = mlx_init();
	
	error_handling(argc, argv);
	initialise_game(game_data);
	printf("In main after init:\n");
	printf("game_data.no_texture_filename contains %s\n", game_data->no_texture_filename);
	printf("game_data.so_texture_filename contains %s\n", game_data->so_texture_filename);
	printf("game_data.we_texture_filename contains %s\n", game_data->we_texture_filename);
	printf("game_data.ea_texture_filename contains %s\n", game_data->ea_texture_filename);
	printf("game_data->all_textures_ok contains %i\n", game_data->all_textures_ok);

	print_maze(game_data);



	map_parsing((char *)argv[1], game_data);
    printf("In main after map parsing:\n");

	printf("game_data.no_texture_filename contains %s\n", game_data->no_texture_filename);
	printf("game_data.so_texture_filename contains %s\n", game_data->so_texture_filename);
	printf("game_data.we_texture_filename contains %s\n", game_data->we_texture_filename);
	printf("game_data.ea_texture_filename contains %s\n", game_data->ea_texture_filename);
	printf("Are all textures present? %s\n", game_data->all_textures_ok ? "true" : "false");
	printf("game_data->all_textures_ok contains %i\n", game_data->all_textures_ok);

	printf("parse_color game_data->floor.color[0] contains %i\n", game_data->floor.color[0]);
    printf("parse_color game_data->floor.color[1] contains %i\n", game_data->floor.color[1]);
    printf("parse_color game_data->floor.color[2] contains %i\n", game_data->floor.color[2]);
    printf("Is floor valid? parse_color game_data->floor.valid_rgb contains %i\n", game_data->floor.valid_rgb);

	printf("parse_color game_data->ceiling.color[0] contains %i\n", game_data->ceiling.color[0]);
    printf("parse_color game_data->ceiling.color[1] contains %i\n", game_data->ceiling.color[1]);
    printf("parse_color game_data->ceiling.color[2] contains %i\n", game_data->ceiling.color[2]);
    printf("Is ceiling valid? parse_color game_data->ceiling.valid_rgb contains %i\n", game_data->ceiling.valid_rgb);
	print_maze(game_data);


	(void)mlx;
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		free_on_exit(game_data); // added

		return(EXIT_FAILURE);
	}
	// if (!(image = mlx_new_image(mlx, 128, 128))) //original line for MLX

	if (!(image = mlx_new_image(mlx, WINDOW_HEIGHT, WINDOW_WIDTH)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		free_on_exit(game_data); //added

		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		free_on_exit(game_data); //added

		return(EXIT_FAILURE);
	}
	init_wall(game_data);
	mlx_loop_hook(mlx, ft_randomize, game_data);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_on_exit(game_data);
	printf("Exiting\n");
	
	return (EXIT_SUCCESS);
}
