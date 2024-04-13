/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:09 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/04/14 00:08:19 by mrizakov         ###   ########.fr       */
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


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024
// which one ?
#define WIDTH 512
#define HEIGHT 512
#define FILE_READ_BUFFER 1024


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


typedef struct	s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_textures	*textures;
	char		*no_texture_filename;
	char		*so_texture_filename;
	char		*we_texture_filename;
	char		*ea_texture_filename;

	char		*whole_map;

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


// Memory management
void	initialise_to_null(t_game *game_data);

void	free_on_exit(t_game *game_data);
void	free_to_null_string(char *str);









// #endif // cub3d_H
