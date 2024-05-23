/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:09 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/05/23 11:48:51 by ddavlety         ###   ########.fr       */
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
# include <float.h>
#include <inttypes.h> // For PRIu32 macro



# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 740
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
# define VALID_CHAR_MAP "NEWSMD10 \n"
// # define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2 ))
# define ICON "./src/textures/icon.png"

// typedef union u_rgba
// {
// 	uint32_t	color_int;
// 	t_color		color_t;
// }				t_rgba;


typedef enum e_orientation
{
	HOR,
	VERT,
	ORIENT,
}			t_orientation;

typedef enum e_directions
{
	NO,
	SO,
	WE,
	EA,
}	t_direct;

typedef enum e_textures
{
	TEX_MUSHR = 4,
	TEX_MUSHR_2,
	TEX_DOOR_CL,
	TEX_DOOR_1,
	TEX_DOOR_OP,
	TEX_NO,
}			t_textures;

typedef enum e_surface
{
	F,
	C,
}	t_surface;

typedef enum e_walltype
{
	W_NONE,
	W_WALL,
	W_DOOR,
}			t_walltype;

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


// used for cursor movement
typedef struct 	s_point {
	double		x;				// x : Width  | x-axis
	double		y;				// y : Height | y-axis
}				t_point;

typedef struct	s_doors
{
	double	x;
	double	y;
	int		map_x;
	int		map_y;
	bool	isopen;
	double	action_time;
	bool	visible;
	double	distance;
	int		texture;
	double	angle;
	double	dimentions;
	double	bott_pixel;
	double	top_pixel;
	double	left_pixel;
	double	err_line;
	double	right_pixel;
	double	err_colon;
	double	animation_time;
}				t_doors;

typedef struct s_sprite
{
	double	x;
	double	y;
	bool	visible;
	double	distance;
	int		texture;
	double	angle;
	double	dimentions;
	double	bott_pixel;
	double	top_pixel;
	double	left_pixel;
	double	err_line;
	double	right_pixel;
	double	err_colon;
}				t_sprite;

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
	mlx_texture_t	*textures[TEX_NO];
	mlx_texture_t	*icon;

	// textures
	char			*texture_filename[TEX_NO];
	int				texture_count[TEX_NO];
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
	t_sprite		sprites[11];
	t_doors			doors[11];
	t_point			cursor; //cursor position
	t_maze			maze;  // the maze
	double			z_buffer[WINDOW_WIDTH];
	double			animat_time;
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
	// double wallHitX;
    // double wallHitY;
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
	//added by ddavlety 21.05
	t_doors	*door;

	//added by ddavlety 21.05
}				t_raycast;

// Error handling and parsing
int				error_handling(int argc, const char *argv[]);
int				map_parsing(char *filename, t_game *game_data);
void			init_data(t_game *game_data);
// int				valid_file(char *filename);
int				check_read_file(int fd);
int				check_file_extension(char *filename, char *file_extension);
// char			*parse_textures(char *map_line, char *direction);
int				check_textures(t_game *game_data);
int				check_colors_ok(t_game *game_data);
int				is_valid_char(char matrix_val);
// int				no_of_players(t_game *game_data, char matrix_val);
// int				parse_color(t_game *game_data, char *map_line);
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
void			draw_sprites(t_game	*game_data);
int32_t			draw_map_sprite(t_game *game_data, t_double_pixel *sprite, unsigned int side_len);

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
void			ray_horiz_loop(t_game *game_data, t_raycast *ray, bool wall);
void			ray_vert_calc(t_game *game_data, t_raycast *ray, double ray_angle);
void			ray_vert_loop(t_game *game_data, t_raycast *ray, bool wall);
void			ray_shortest_distance(t_raycast *ray, t_game *game_data);
void			draw_textures(mlx_texture_t *, int column_id, double wall_top_pixel, double wall_bottom_pixel, int texOffsetX);
void			draw_3d_projection(t_game *game_data, int column_id, t_raycast *ray, double ray_angle);


//Game logic
int				prevent_wall_collisions(t_game *game_data, double player_y_check, double player_x_check, int map_padding);
void			update_pos(t_game *game_data);

//Testing functions, remove for final version
void			ft_print_parsed_map(t_game *game_data);
void			print_maze(t_game *game_data);

//Extra mlx
int32_t			ft_double_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int				load_textures(t_game *game_data);


//pixels and colors
void			put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color);
t_color			convertColors(mlx_texture_t* texture, uint32_t index, double distance);
int				router_parse_data(char *line, t_game *game_data);
void			put_pixel_uint(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);

//sprites
int				init_sprites(t_game *game_data, char t, int x, int y);
void			sprites_calculations(t_game	*game_data);
//doors
int				init_doors(t_game *game_data, char t, int x, int y);
int				check_door_place(t_game *game_data, int y, int x);
void			open_door(t_game *game_data);
t_doors			*which_door(t_game *game_data, int y, int x);


//hooks
void			ft_animation(void *param);
void			ft_keyboad_hook(void* param);
void			ft_cursor_hook(double xpos, double ypos, void* param);

//Utils
double  distance_between_points(double x1, double y1, double x2, double y2);

#endif
