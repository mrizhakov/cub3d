/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:09 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/05/23 14:35:38 by ddavlety         ###   ########.fr       */
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
// #include <integer.h>
// #include <inttypes.h> // For PRIu32 macro



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
# define TURNING_SPEED 0.05
# define VALID_CHAR_MAP "NEWSMD10 \n"
# define ICON "./src/textures/icon.png"

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

typedef enum e_casttype
{
	W_NONE,
	W_WALL,
	W_DOOR,
	W_SPRITE,
}			t_casttype;

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

// player x and y position using floats
typedef struct	s_float_pixel
{
	float		y;
	float		x;
	uint32_t	color;
}				t_float_pixel;


// used for cursor movement
typedef struct 	s_point {
	float		x;				// x : Width  | x-axis
	float		y;				// y : Height | y-axis
}				t_point;

typedef struct	s_doors
{
	float	x;
	float	y;
	int		map_x;
	int		map_y;
	bool	isopen;
	float	action_time;
	bool	visible;
	float	distance;
	int		texture;
	float	angle;
	float	dimentions;
	float	bott_pixel;
	float	top_pixel;
	float	left_pixel;
	float	err_line;
	float	right_pixel;
	float	err_colon;
	float	animation_time;
}				t_doors;

typedef struct s_sprite
{
	float	x;
	float	y;
	int		map_x;
	int		map_y;
	bool	visible;
	float	distance;
	int		texture;
	float	angle;
	float	dimentions;
	float	bott_pixel;
	float	top_pixel;
	float	left_pixel;
	float	err_line;
	float	right_pixel;
	float	err_colon;
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
	float			player_init_dir;
	int				maze_closed;

	// player
	t_float_pixel	*player;
	float			player_angle;
	int				player_turn_dir;
	int				player_walk_dir;
	int				player_strafe_dir;
	int				player_turn_speed;
	float			fov_angle;
	int				num_rays;
	float			dist_proj_plane;

	// draw
	int             redraw_minimap;
	int				texture_width;
	// maze
	t_sprite		sprites[11];
	t_doors			doors[11];
	t_point			cursor; //cursor position
	t_maze			maze;  // the maze
	float			z_buffer[WINDOW_WIDTH];
	float			animat_time;
}				t_game;

typedef struct 	s_raycast {
	int is_ray_facing_down;
	int is_ray_facing_right;
	int is_ray_facing_up;
	int is_ray_facing_left;
	float xintercept;
	float yintercept;
	float xstep;
	float ystep;
	float distance;
	float next_hor_touch_x;
	float next_hor_touch_y;
	int found_hor_hit;
	float hor_wall_hit_x;
	float hor_wall_hit_y;
	int found_vert_hit;
	float vert_wall_hit_x;
	float vert_wall_hit_y;
	float next_vert_touch_x;
	float next_vert_touch_y;
	float  shortest_wall_hit_x;
	float  shortest_wall_hit_y;
	int		was_hit_vertical;
	float distance_hor;
	float distance_vert;
	t_doors		*door;
	t_sprite	*sprite;
}				t_raycast;

// Error handling and parsing
int				error_handling(int argc, const char *argv[]);
int				map_parsing(char *filename, t_game *game_data);
void			init_data(t_game *game_data);
int				check_read_file(int fd);
int				check_file_extension(char *filename, char *file_extension);
int				check_textures(t_game *game_data);
int				check_colors_ok(t_game *game_data);
int				is_valid_char(char matrix_val);
int				is_valid_int(int matrix_val);
int				maze_check(t_game *game_data);

// Memory management
int				initialise_game(t_game *game_data);
void			init_maze(t_game *game_data);
void			free_on_exit(t_game *game_data);
void			free_to_null_string(char **str);
void			free_char_arr(char **str);
void			free_textures(t_game *game_data);


// Extra MLX testing functions
int32_t			mlx_run(t_game *game_data);
int32_t			conv_x(int32_t x, int32_t y, float angle);
int32_t			conv_y(int32_t x, int32_t y, float angle);
t_float_pixel	rotatePoint(t_float_pixel p, t_float_pixel center, float angle);

//Drawing functions
int32_t			draw_rectangle(t_game *game_data, t_float_pixel start, t_float_pixel end);
void			drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);
int32_t			draw_h_line(t_game *game_data, t_float_pixel start, t_float_pixel end);
int32_t			draw_v_line(t_game *game_data, t_float_pixel start, t_float_pixel end);
int32_t			check_pix(t_float_pixel pix);
int32_t			draw_minimap(t_game *game_data, t_float_pixel start, unsigned int side_len);
int32_t			draw_minimap_with_border(t_game *game_data, t_float_pixel start, unsigned int side_len);
int32_t			draw_player(t_game *game_data, t_float_pixel *player, unsigned int side_len);
void			draw_black_background(t_game *game_data);
int32_t			draw_grid(t_game *game_data, t_float_pixel start, unsigned int side_len);
int32_t			draw_square(t_game *game_data, t_float_pixel start, unsigned int side_len);
int32_t			draw_line(t_game *game_data, t_float_pixel start, t_float_pixel end);
void			draw_sprites(t_game	*game_data);
int32_t			draw_map_sprite(t_game *game_data, t_float_pixel *sprite, unsigned int side_len);

//Raycast
float			check_angle_overflow(t_game *game_data, float player_angle);
void			draw_ray(t_game *game_data, float ray_angle);
void			draw_fov(t_game *game_data);
void			cast_ray(t_game *game_data, float ray_angle, int column_id);
int				is_ray_facing_down(float ray_angle);
int				is_ray_facing_right(float ray_angle);
int				is_ray_facing_up(float ray_angle);
int				is_ray_facing_left(float ray_angle);
void			ray_orientation(t_raycast *ray, float ray_angle);
void			ray_horiz_calc(t_game *game_data, t_raycast *ray, float ray_angle);
void			ray_horiz_loop(t_game *game_data, t_raycast *ray, t_casttype);
void			ray_vert_calc(t_game *game_data, t_raycast *ray, float ray_angle);
void			ray_vert_loop(t_game *game_data, t_raycast *ray, t_casttype);
void			ray_shortest_distance(t_raycast *ray, t_game *game_data);
void			draw_textures(mlx_texture_t *, int column_id, float wall_top_pixel, float wall_bottom_pixel, int texOffsetX);
void			draw_3d_projection(t_game *game_data, int column_id, t_raycast *ray, float ray_angle);


//Game logic
int				prevent_wall_collisions(t_game *game_data, float player_y_check, float player_x_check, int map_padding);
void			update_pos(t_game *game_data);

//Testing functions, remove for final version
void			ft_print_parsed_map(t_game *game_data);
void			print_maze(t_game *game_data);

//Extra mlx
int32_t			ft_float_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int				load_textures(t_game *game_data);


//pixels and colors
void			put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color);
t_color			convertColors(mlx_texture_t* texture, uint32_t index, float distance);
int				router_parse_data(char *line, t_game *game_data);
void			put_pixel_uint(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);

//sprites
int				init_sprites(t_game *game_data, char t, int x, int y);
void			sprites_calculations(t_game	*game_data);
t_sprite		*which_sprite(t_game *game_data, int y, int x);

//doors
int				init_doors(t_game *game_data, char t, int x, int y);
int				check_door_place(t_game *game_data, int y, int x);
void			open_door(t_game *game_data);
t_doors			*which_door(t_game *game_data, int y, int x);


//hooks
void			ft_animation(void *param);
void			ft_keyboad_hook(void* param);
void			ft_cursor_hook(float xpos, float ypos, void* param);

//Utils
float			distance_between_points(float x1, float y1, float x2, float y2);

#endif
