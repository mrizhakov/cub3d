/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:09 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/05/18 00:25:02 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./MLX42/include/MLX42/MLX42_Int.h"
# include "./libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
#include <inttypes.h> // For PRIu32 macro



# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1000 // not sure why doesnt  work properly with non-square big window size
// which one ?
//#define WIDTH 1280
//#define HEIGHT 1024 // change to window_heigh and window_width
# define FILE_READ_BUFFER 1024
# define MAZE_DIMENSION 40
# define PLAYER_STEP 30
# define MAP_PADDING 2

# define MINIMAP_SQUARE_SIDE_LEN 15

// # define MINIMAP_Y_OFFSET 10
// # define MINIMAP_X_OFFSET 10
// # define MAX_DEPTH_OF_FIELD 8
# define FOV 60
# define TURNING_SPEED 0.025
# define VALID_CHAR_MAP "NEWS10M \n"

// # define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2 ))
# define ICON "./src/textures/icon.png"


typedef enum e_directions
{
	NO,
	SO,
	WE,
	EA,
}	t_direct;

typedef enum e_colors
{
	F,
	C,
}	t_colors;

//save textures here
// typedef struct s_textures
// {
// 	mlx_texture_t		*north;
// 	mlx_texture_t		*south;
// 	mlx_texture_t		*east;
// 	mlx_texture_t		*west;
// }						t_textures;

// typedef struct s_text_images
// {
// 	mlx_image_t		*north;
// 	mlx_image_t		*south;
// 	mlx_image_t		*east;
// 	mlx_image_t		*west;
// }						t_text_images;

// used for colors
typedef struct	s_rgb
{
	int			color[3];
	int			valid_rgb;
	uint32_t	rgb_color;
}				t_rgb;

//maze
typedef struct	s_maze
{
	char	g[MAZE_DIMENSION][MAZE_DIMENSION];
	int		valid_maze;
}				t_maze;

// player x and y position using doubles
typedef struct	s_double_pixel
{
	double		y;
	double		x;
	uint32_t	color;
}				t_double_pixel;

typedef struct	s_doors t_doors;

// used for flood_fill
typedef struct 	s_point {
	double		x;				// x : Width  | x-axis
	double		y;				// y : Height | y-axis
}				t_point;

typedef struct s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;
}			t_color;

typedef struct	s_game
{
	// mlx
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[4];
	mlx_texture_t	*icon;
	// t_text_images	*images;

	// textures
	char			*texture_filename[4];
	int				texture_count[4];
	bool				all_textures_ok;

    // colors
	t_rgb			color[2];
	int				color_count[2];

	// maze parse
	// int				player_count;
	int				player_init_loc[2];
	double			player_init_dir;
	int				maze_closed;

	// player
	t_double_pixel	*player;
	double			player_angle;
	int				player_turn_dir;
	int				player_walk_dir;
	int				player_strafe_dir;
	int				player_turn_speed;
	double			fov_angle;
	int				num_rays;
	double			dist_proj_plane;

	// draw
	int             redraw_minimap;
	int				texture_width;
	// maze
	t_point			cursor;
	t_maze			maze;  // the maze
}				t_game;

typedef struct 	s_raycast {
	int is_ray_facing_down;
    int is_ray_facing_right;
    int is_ray_facing_up;
    int is_ray_facing_left;
	double xintercept;
    double yintercept;
	double xstep;
    double ystep;


	double wallHitX;
    double wallHitY;

    double distance;


    double next_hor_touch_x;
    double next_hor_touch_y;
    int found_hor_hit;
    double hor_wall_hit_x;
    double hor_wall_hit_y;


	int found_vert_hit;
    double vert_wall_hit_x;
    double vert_wall_hit_y;
    double next_vert_touch_x;
    double next_vert_touch_y;

    double  shortest_wall_hit_x;
    double  shortest_wall_hit_y;
    int     was_hit_vertical;

	double distance_hor;
    double distance_vert;


}				t_raycast;

// Error handling and parsing
int				error_handling(int argc, const char *argv[]);
int				map_parsing(char *filename, t_game *game_data);
void			init_data(t_game *game_data);
// int				valid_file(char *filename);
int				check_read_file(int fd);
int				check_file_extension(char *filename, char *file_extension);
char			*parse_textures(char *map_line, char *direction);
int				check_textures(t_game *game_data);
int				check_colors_ok(t_game *game_data);
int				is_valid_char(char matrix_val);
int				no_of_players(t_game *game_data, char matrix_val);
int				parse_color(t_game *game_data, char *map_line);
int				is_valid_int(int matrix_val);
int				maze_check_closed(t_game *game_data);

// Memory management
int				initialise_game(t_game *game_data);
void			init_maze(t_game *game_data);
void			free_on_exit(t_game *game_data);
void			free_to_null_string(char **str);
void			free_char_arr(char **str);
void			free_textures(t_game *game_data);


// Extra MLX testing functions
int32_t			mlx_run(t_game *game_data);
int32_t			conv_x(int32_t x, int32_t y, double angle);
int32_t			conv_y(int32_t x, int32_t y, double angle);
t_double_pixel	rotatePoint(t_double_pixel p, t_double_pixel center, double angle);

//Drawing functions
int32_t			draw_rectangle(t_game *game_data, t_double_pixel start, t_double_pixel end);
void			drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);
int32_t			draw_h_line(t_game *game_data, t_double_pixel start, t_double_pixel end);
int32_t			draw_v_line(t_game *game_data, t_double_pixel start, t_double_pixel end);
int32_t			check_pix(t_double_pixel pix);
int32_t			draw_minimap(t_game *game_data, t_double_pixel start, unsigned int side_len);
int32_t			draw_minimap_with_border(t_game *game_data, t_double_pixel start, unsigned int side_len);
int32_t			draw_player(t_game *game_data, t_double_pixel *player, unsigned int side_len);
void			draw_black_background(t_game *game_data);
int32_t			draw_grid(t_game *game_data, t_double_pixel start, unsigned int side_len);
int32_t			draw_square(t_game *game_data, t_double_pixel start, unsigned int side_len);
int32_t			draw_line(t_game *game_data, t_double_pixel start, t_double_pixel end);

//Raycast
double			check_angle_overflow(t_game *game_data, double player_angle);
void			draw_ray(t_game *game_data, double ray_angle);
void			draw_fov(t_game *game_data);
void			cast_ray(t_game *game_data, double ray_angle, int column_id);
int				is_ray_facing_down(double ray_angle);
int				is_ray_facing_right(double ray_angle);
int				is_ray_facing_up(double ray_angle);
int				is_ray_facing_left(double ray_angle);
void			ray_orientation(t_raycast *ray, double ray_angle);
void			ray_horiz_calc(t_game *game_data, t_raycast *ray, double ray_angle);
void			ray_horiz_loop(t_game *game_data, t_raycast *ray);
void			ray_vert_calc(t_game *game_data, t_raycast *ray, double ray_angle);
void			ray_vert_loop(t_game *game_data, t_raycast *ray);
void			ray_shortest_distance(t_raycast *ray, t_game *game_data);
void			ray_init_data(t_raycast *ray);
void			draw_textures(t_game *game_data, int column_id, double wall_top_pixel, double wall_bottom_pixel, int texOffsetX);
void			draw_3d_projection(t_game *game_data, int column_id, t_raycast *ray, double ray_angle);


//Game logic
int				prevent_wall_collisions(t_game *game_data, double player_y_check, double player_x_check, int y_map_padding, int x_map_padding);
void			update_pos(t_game *game_data);

//Testing functions, remove for final version
void			ft_print_parsed_map(t_game *game_data);
void			print_maze(t_game *game_data);

//Extra mlx
int32_t			ft_double_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int				load_textures(t_game *game_data);


//error_

int	router_parse_data(char *line, t_game *game_data);


#endif
