/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:09 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/04/21 20:21:45 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define cub3d_H

#include "./MLX42.h"
#include "./libft/libft.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <errno.h>


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000 // not sure why doesnt  work properly with non-square big window size
// which one ?
//#define WIDTH 1280
//#define HEIGHT 1024 // change to window_heigh and window_width
#define FILE_READ_BUFFER 1024
#define MAZE_DIMENSION 40
#define PLAYER_STEP 3
#define MAP_PADDING 2

#define MINIMAP_SQUARE_SIDE_LEN 15
#define MINIMAP_Y_OFFSET 10
#define MINIMAP_X_OFFSET 10



# define NORTH "./textures/DarkAbstractBackgrounds_03.png"
# define SOUTH "./textures/DarkAbstractBackgrounds_06.png"
# define EAST  "./textures/DarkAbstractBackgrounds_09.png"
# define WEST  "./textures/DarkAbstractBackgrounds_10.png"

typedef struct s_textures
{
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*east;
	mlx_texture_t		*west;
	//mlx_texture_t		*floor;
	//mlx_texture_t		*ceiling;
}						t_textures;

typedef struct	s_map
{
	int	no;
	int	we;
	int	so;
	int	ea;
}				t_map;

typedef struct	s_rgb
{
	int	color[3];
	int valid_rgb;
}				t_rgb;

typedef struct	s_maze
{
	int	g[MAZE_DIMENSION][MAZE_DIMENSION];
	int valid_maze;
}				t_maze;

typedef struct s_raycast
{

	double			cam;
	double			ray_x;
	double			ray_y;
	double			first_intersection_x;
	double			first_intersection_y;
	double			grid_step_dist_x;
	double			grid_step_dist_y;
	int				map_x;
	int				map_y;
	double			step_x;
	double			step_y;
	double			side_dist_x;
	double			side_dist_y;
	
	
}	t_raycast;
//storing WINDOW_WIDTH number of elements,
//each should contain x, y coordinates and color
//both of the starting point and the end point


typedef struct	s_pixel
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	color;
}				t_pixel;

typedef struct	s_wall
{
	t_pixel	column_start[WINDOW_WIDTH];
	t_pixel	column_end[WINDOW_WIDTH];
}				t_wall;

typedef struct	s_game
{
	double		pl_pos_x;
	double		pl_pos_y;
	double		cam_plane_x;
	double		cam_plane_y;
	double		player_dir_x;
	double		player_dir_y;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_textures		*textures;
	char			*no_texture_filename;
	char			*so_texture_filename;
	char			*we_texture_filename;
	char			*ea_texture_filename;
	int				no_texture_count;
	int 			so_texture_count;
	int				we_texture_count;
	int 			ea_texture_count;
	int				all_textures_ok;
	int				direction_count;
	t_rgb			floor;
	t_rgb			ceiling;
	int				floor_count;
	int				ceiling_count;
	int				player_count;
	int				player_init_loc[2];
	double			player_init_dir;
	int				minimap_side_len;
	int				player_step;
	int             redraw_minimap;



	t_maze			maze;
	t_pixel			*player;
	t_pixel			*minimap;


	t_wall			*wall;
	t_wall			*projection;
	t_pixel			*center;

	
	char			*whole_map;

}				t_game;

int 	error_handling(int argc, const char *argv[]);
int		map_parsing(char *filename, t_game *game_data);
void	init_data(t_game *game_data);
void 	initialise_game(t_game *game_data);
int		load_textures(t_game *game_data);
int 	valid_file(char *filename);
int		check_read_file(int fd);
int		check_file_extension(char *filename, char *file_extension);
char	*parse_textures(char *map_line, char *direction);
void	check_textures_ok(t_game *game_data);
int		check_colors_ok(t_game *game_data);
int		is_valid_char(char matrix_val);
int		no_of_players(t_game *game_data, char matrix_val);

int		parse_color(t_game *game_data, char *map_line);
int		is_valid_int(int matrix_val);

//raycast
// static void raycasting_init(int x, t_game *game_data, t_raycast *ray_data);

// Memory management
void	initialise_to_null(t_game *game_data);
void    init_maze(t_game *game_data);

void	free_on_exit(t_game *game_data);
void	free_to_null_string(char *str);
void	free_to_null_char_arr(char **str);
void	free_wall(t_game *game_data);
void	init_wall(t_game *game_data);

// Extra MLX testing functions
int32_t mlx_demo(t_game *game_data);
void	ft_generate_rectangle_data(t_game *game_data);
void	ft_draw_rectangle(mlx_image_t *image, t_game *game_data);
int32_t	conv_x(int32_t x, int32_t y, double angle);
int32_t	conv_y(int32_t x, int32_t y, double angle);
t_pixel	rotatePoint(t_pixel p, t_pixel center, double angle);
void	ft_projection_rectangle_data(t_game *game_data);


//Drawing functions
int32_t draw_rectangle(t_game *game_data, t_pixel start, t_pixel end);
void	drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);
int32_t	draw_h_line(t_game *game_data, t_pixel start, t_pixel end);
int32_t	draw_v_line(t_game *game_data, t_pixel start, t_pixel end);
int32_t check_pix(t_pixel pix);
int32_t draw_minimap(t_game *game_data, t_pixel start, unsigned int side_len);
int32_t draw_minimap_with_border(t_game *game_data, t_pixel start, unsigned int side_len);
int32_t draw_player(t_game *game_data, t_pixel *player, unsigned int side_len);
void	draw_black_background(t_game *game_data);
int32_t draw_grid(t_game *game_data, t_pixel start, unsigned int side_len);


//Game logic
// int		prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check);
int     prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check, int y_map_padding, int x_map_padding);



//Testing functions, remove for final version
void	ft_print_parsed_map(t_game *game_data);
void	print_maze(t_game *game_data);



//Extra mlx

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);










// #endif // cub3d_H




