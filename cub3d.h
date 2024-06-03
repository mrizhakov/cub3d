/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:09 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/06/03 19:21:11 by ddavlety         ###   ########.fr       */
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

# ifndef PSYCHO
#  define PSYCHO 7
# endif
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define FLT_MAX 3.402823E+38
# define DOORS_CO 10
# define SPRITES_CO 10
# define TEXTURE_WINDTH 512
# define ACTION_DIST 600
# define ANIM_TIME 0.5
# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 740
# define FILE_READ_BUFFER 1024
# define MAZE_DIMENSION 40
# define PLAYER_STEP 30
# define MAP_PADDING 2
# define MINIMAP_SQUARE_SIDE_LEN 15
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
	TEX_MUSHR_M,
	TEX_DOOR_CL,
	TEX_DOOR_1,
	TEX_DOOR_OP,
	TEX_PSY_1,
	TEX_PSY_2,
	TEX_PSY_3,
	TEX_NO,
}			t_textures;

typedef enum e_surface
{
	F,
	C,
	SUR_NO,
}	t_surface;

typedef enum e_casttype
{
	W_NONE,
	W_WALL,
	W_DOOR,
	W_SPRITE,
}			t_casttype;

typedef struct s_draw
{
	mlx_texture_t	*texture;
	int				column;
	float			top;
	float			bott;
	float			height;
	float			err;
	mlx_image_t		*img;
}					t_draw;

typedef struct s_slope
{
	uint32_t	x0;
	uint32_t	y0;
	uint32_t	x1;
	uint32_t	y1;
	uint32_t	color;
	int32_t		dx;
	int32_t		dy;
	int32_t		sx;
	int32_t		sy;
	int32_t		err;
	int32_t		e2;
}				t_slope;

typedef struct s_rgb
{
	int			color[3];
	int			valid_rgb;
	uint32_t	rgb_color;
}				t_rgb;

typedef struct s_maze
{
	char		g[MAZE_DIMENSION][MAZE_DIMENSION];
	int			valid_maze;
}				t_maze;

typedef struct s_float_pixel
{
	float		y;
	float		x;
	uint32_t	color;
}				t_float_pixel;

typedef struct s_point {
	float		x;
	float		y;
}				t_point;

typedef struct s_doors
{
	float		x;
	float		y;
	int			map_x;
	int			map_y;
	bool		isopen;
	float		action_time;
	bool		visible;
	float		distance;
	int			texture;
	float		angle;
	float		dimentions;
	float		bott_pixel;
	float		top_pixel;
	float		left_pixel;
	float		err_line;
	float		right_pixel;
	float		err_column;
	float		animation_time;
}				t_doors;

typedef struct s_sprite
{
	float		x;
	float		y;
	int			map_x;
	int			map_y;
	bool		visible;
	bool		taken;
	float		distance;
	int			texture;
	float		angle;
	float		dimentions;
	float		bott_pixel;
	float		top_pixel;
	float		left_pixel;
	float		err_line;
	float		right_pixel;
	float		err_column;
}				t_sprite;

typedef struct s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;
}			t_color;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[TEX_NO];
	mlx_texture_t	*icon;
	char			*texture_filename[TEX_NO];
	int				texture_count[TEX_NO];
	bool			all_textures_ok;
	t_rgb			color[2];
	int				color_count[2];
	int				player_init_loc[2];
	char			player_init_dir;
	int				maze_closed;
	t_float_pixel	*player;
	float			player_angle;
	int				player_turn_dir;
	int				player_walk_dir;
	int				player_strafe_dir;
	int				player_turn_speed;
	float			fov_angle;
	int				num_rays;
	float			dist_proj_plane;
	int				redraw_minimap;
	int				texture_width;
	t_sprite		sprites[SPRITES_CO + 1];
	t_doors			doors[DOORS_CO + 1];
	t_point			cursor;
	t_maze			maze;
	float			z_buffer[WINDOW_WIDTH];
	float			animat_time;
	bool			psycho;
	float			phycho_time;
}				t_game;

typedef struct s_raycast
{
	int				is_ray_facing_down;
	int				is_ray_facing_right;
	int				is_ray_facing_up;
	int				is_ray_facing_left;
	float			xintercept;
	float			yintercept;
	float			xstep;
	float			ystep;
	float			distance;
	float			next_hor_touch_x;
	float			next_hor_touch_y;
	int				found_hor_hit;
	float			hor_wall_hit_x;
	float			hor_wall_hit_y;
	int				found_vert_hit;
	float			ver_wall_hit_x;
	float			ver_wall_hit_y;
	float			next_vert_touch_x;
	float			next_vert_touch_y;
	float			shortest_wall_hit_x;
	float			shortest_wall_hit_y;
	int				was_hit_vertical;
	float			distance_hor;
	float			distance_vert;
	mlx_texture_t	*texture;
	int				column;
	float			top;
	float			bott;
	float			height;
	int				offset;
	float			err;
	mlx_image_t		*img;
	t_doors			*door[ORIENT];
}					t_raycast;

// Parsing
int		error_handling(int argc, const char *argv[]);
int		map_parsing(char *filename, t_game *game_data);
int		init_data(t_game *game_data);
int		check_read_file(int fd);
int		check_file_extension(char *filename, char *file_extension);
int		check_textures(t_game *game_data);
int		check_colors_ok(t_game *game_data);
int		is_valid_char(char matrix_val);
int		is_valid_int(int matrix_val);
int		ft_istabs(char *line);
char	put_sign(char c, char *tokens);
int		check_parse(size_t j, t_game *game_data);
int		maze_check(t_game *game_data);
int		parsing_error(const char *msg, int fd);

// Memory management
int		initialise_game(t_game *game_data);
void	init_maze(t_game *game_data);
void	free_on_exit(t_game *game_data);
void	free_char_arr(char **str);
void	free_textures(t_game *game_data);

// MLX run
int32_t	mlx_run(t_game *game_data);

//Drawing functions
void	draw_line(t_slope slope_data, uint32_t color, mlx_image_t *img);
int32_t	check_pix(t_float_pixel pix);
void	draw_minimap(t_game *game_data, t_float_pixel start, uint32_t side_len);
int32_t	draw_player(t_game *game_data);
void	draw_black_background(t_game *game_data);
int32_t	draw_square(t_game *game_data, t_float_pixel start, uint32_t side_len);
void	draw_sprites(t_game	*game_data);
int32_t	draw_map_sprite(t_game *game_data, uint32_t side_len);
t_slope	init_slope_data(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void	draw_textures(t_raycast data);
void	ft_draw_image(void *param);
float	transform(float value);
void	draw_minimap_fov(t_game *game_data, t_raycast ray, t_raycast ray_door);
//Raycast
float	check_angle_overflow(t_game *game_data, float player_angle);
void	draw_fov(t_game *game_data);
void	cast_ray(t_game *game_data, float ray_angle, int column_id);
void	ray_orientation(t_raycast *ray, float ray_angle);
void	ray_horiz_calc(t_game *game_data, t_raycast *ray, float ray_angle);
void	ray_horiz_loop(t_game *game_data, t_raycast *ray, t_casttype type);
void	ray_vert_calc(t_game *game_data, t_raycast *ray, float ray_angle);
void	ray_vert_loop(t_game *game_data, t_raycast *ray, t_casttype type);
void	ray_shortest_distance(t_raycast *ray, t_game *game_data);
void	draw_3d_projection(t_game *game_data, int column_id,
			t_raycast ray, float ray_angle);
void	draw_3d_door(t_game *game_data, int column_id,
			t_raycast ray, float ray_angle);
int		cast_type_hor(t_game *game_data, t_raycast *ray, t_casttype type);
int		cast_type_vert(t_game *game_data, t_raycast *ray, t_casttype type);

/* Ray_utils */
float	distance_between_points(float x1, float y1, float x2, float y2);
int		is_ray_facing_down(float ray_angle);
int		is_ray_facing_right(float ray_angle);
int		is_ray_facing_up(float ray_angle);
int		is_ray_facing_left(float ray_angle);
int		cast_type(char c, t_casttype type);

//Game logic
int		prevent_wall_collisions(t_game *game_data, float player_y_check,
			float player_x_check);
void	update_pos(t_game *game_data);
void	psycho_trigger(t_game *game_data);

//Extra mlx
int32_t	ft_float_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int		load_textures(t_game *game_data);

//pixels and colors
void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color);
t_color	convert_colors(mlx_texture_t *texture, uint32_t index, float distance);
int		router_parse_data(char *line, t_game *game_data);
void	put_pixel_uint(mlx_image_t *img, uint32_t x,
			uint32_t y, uint32_t color);
int32_t	ft_float_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//sprites
int		init_sprites(t_game *game_data, char t, int x, int y);
void	sprites_calculations(t_game	*game_data);
float	calcul_angle_sprite(float p_angle, t_sprite *sprite,
			t_float_pixel *player);

//doors
int		init_doors(t_game *game_data, char t, int x, int y);
int		check_door_place(t_game *game_data, int y, int x);
void	open_door(t_game *game_data);
t_doors	*which_door(t_game *game_data, int y, int x);
void	sort_doors(t_doors doors[DOORS_CO]);

//hooks
void	ft_anim_sprite(void *param);
void	ft_anim_door(void *param);
void	ft_keyboad_hook(void *param);
void	ft_cursor_hook(double xpos, double ypos, void *param);
void	ft_psychodelic(void *param);

//find utils
int		find_wall(t_maze maze, int y, int x, int del);
int		find_door(t_game *game_data, int y, int x, int del);

/*Texture and colors utils*/
void	init_tokens(char token_texture[TEX_NO][4], char token_color[SUR_NO][2]);

#endif
