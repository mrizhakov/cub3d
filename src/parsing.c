/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:00:24 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/05/10 21:38:20 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// char *parse_textures(char *map_line, char *direction)
// {
// 	char *texture_line;
// 	char *texture_filename;
// 	int texture_fd;

// 	texture_line = ft_strnstr(map_line, direction, ft_strlen(map_line));
// 	if (!texture_line)
// 		return (NULL);
// 	if (texture_line != map_line)
// 		return (NULL);
// 	texture_line += 2;
// 	texture_filename = ft_strtrim(texture_line, " \n");
// 	texture_fd = open(texture_filename, O_RDONLY);
// 	if (texture_fd == -1)
// 		return(free(texture_filename), perror("Error opening texture files"), NULL);
// 	if (check_file_extension(texture_filename, ".png") || check_read_file(texture_fd))
// 	{
// 		perror("Texture files are no bueno. Bring your nice .png's!"); // perror does not contain error
// 		free(texture_filename);
// 		free(map_line);
// 		close(texture_fd);
// 		return (NULL);
// 	}
// 	return (texture_filename);
// }

int	check_texture(char *texture, int texture_count)
{
	if (texture && texture_count == 1)
		return (1);
	else
		return (0);
}

int	check_textures(t_game *game_data)
{
	int	i;

	i = check_texture(game_data->texture_filename[NO], game_data->texture_count[NO]);
	i = check_texture(game_data->texture_filename[SO], game_data->texture_count[SO]);
	i = check_texture(game_data->texture_filename[WE], game_data->texture_count[WE]);
	i = check_texture(game_data->texture_filename[EA], game_data->texture_count[EA]);
	game_data->all_textures_ok = i;
	return (i);
}

// int parse_directions(t_game *game_data, char *map_line)
// {
// 	if (ft_strnstr(map_line, "NO", ft_strlen(map_line)))
// 	{
// 		if (!game_data->texture_filename[NO])
// 			game_data->texture_filename[NO] = parse_textures(map_line, "NO");
// 		game_data->texture_count[NO]++;
// 	}
// 	if (ft_strnstr(map_line, "SO", ft_strlen(map_line)))
// 	{
// 		if (!game_data->texture_filename[NO])
// 			game_data->texture_filename[NO] = parse_textures(map_line, "SO");
// 		game_data->texture_count[SO]++;
// 	}
// 	if (ft_strnstr(map_line, "WE", ft_strlen(map_line)))
// 	{
// 		if (!game_data->texture_filename[NO])
// 			game_data->texture_filename[NO] = parse_textures(map_line, "WE");
// 		game_data->texture_count[WE]++;
// 	}
// 	if (ft_strnstr(map_line, "EA", ft_strlen(map_line)))
// 	{
// 		if (!game_data->texture_filename[NO])
// 			game_data->texture_filename[NO] = parse_textures(map_line, "EA");
// 		game_data->texture_count[EA]++;
// 	}
// 	return (check_textures_ok(game_data)); // why checking textures all the time?
// }

// t_rgb read_color(char *map_line, char *surface)
// {
// 	t_rgb rgb;

// 	rgb.valid_rgb = -1;
// 	char *color_line;
// 	char *color_def;

// 	color_line = ft_strnstr(map_line, surface, ft_strlen(map_line));
// 	if (!color_line)
// 		return (rgb);
// 	color_line++;
// 	color_def = ft_strtrim(color_line, " \n"); // malloc here
// 	char **color_array = ft_split(color_def, ',');

// 	int i = 0;
// 	while (color_array[i] != NULL)
// 	{
// 		rgb.color[i] = ft_atoi(color_array[i]);
// 		printf("Array %i is : |%d|\n", i, rgb.color[i]);
// 		i++;
// 		if (i > 3)
// 		{
// 			perror("Invalid color");
// 			free_to_null_string(&color_def);
// 			rgb.valid_rgb = -1;
// 			return (rgb);
// 		}
// 	}

// 	int y = 0;
// 	while (y != i && rgb.color[y] >= 0 && rgb.color[y] <= 255)
// 	{
// 		printf("Y is %i\n", y);
// 		y++;
// 	}
// 	rgb.valid_rgb = 1;
// 	if (y != 3)
// 	{
// 		rgb.valid_rgb = -1;
// 		printf("Y is %i, triggered unvalidity check\n", y);
// 	}
// 	printf("Is it a valid RGB? r : %i, g: %i. b: %i, validity: %i\n", rgb.color[0], rgb.color[1], rgb.color[2], rgb.valid_rgb);
// 	free_to_null_string(&color_def);
// 	free_char_arr(color_array);
// 	return (rgb);
// }

// int parse_color(t_game *game_data, char *map_line)
// {
// 	if (ft_strnstr(map_line, "F", ft_strlen(map_line)))
// 	{
// 		game_data->color_count[F]++;
// 		if (game_data->color[F].valid_rgb == -1)
// 			game_data->color[F] = read_color(map_line, "F");
// 	}
// 	if (ft_strnstr(map_line, "C", ft_strlen(map_line)))
// 	{
// 		game_data->color_count[C]++;
// 		if (game_data->color[C].valid_rgb == -1)
// 			game_data->color[C] = read_color(map_line, "C");
// 	}
// 	return (0);
// }

int check_colors_ok(t_game *game_data)
{
	if (game_data->color_count[F] == 1
		&& game_data->color_count[C] == 1
		&& game_data->color[F].valid_rgb == 1
		&& game_data->color[C].valid_rgb == 1)
		return (1);
	else
		return (0);
}

void print_maze(t_game *game_data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	printf("Printing out maze for educational purposes: \n\n");
	while (y != MAZE_DIMENSION - 1)
	{
		while (x != MAZE_DIMENSION - 1)
		{
			printf("%c", game_data->maze.g[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	printf("\nIs the maze valid? %i\n", game_data->maze.valid_maze);
}

int skip_empty_line(char *map_line)
{
	while ((*map_line) && (*map_line == ' ' || *map_line == '\n'))
	{
		if (*map_line == '\n')
			return (1);
		map_line++;
	}
	return (0);
}

int maze_parse(t_game *game_data, char *map_line)
{
	int i;
	int x_axis;
	static int y_axis = 1;

	i = 0;
	x_axis = 1;
	while (is_valid_char(map_line[i]))
	{
		if (skip_empty_line(map_line))
			return (0);
		if (map_line[i] == '\n' || map_line[i] == '\r')
		{
			y_axis++;
			return (0);
		}
		if (map_line[i] == '\t')
		{
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			i++;
		}
		if (map_line[i] == '0')
		{
			game_data->maze.g[y_axis][x_axis] = '0';
			x_axis++;
			i++;
		}
		if (map_line[i] == ' ')
		{
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			i++;
		}
		if (map_line[i] == '1')
		{
			game_data->maze.g[y_axis][x_axis] = '1';
			x_axis++;
			i++;
		}
		if (map_line[i] == '2')
		{
			game_data->maze.g[y_axis][x_axis] = 'Z';
			x_axis++;
			i++;
		}
		if (map_line[i] == 'N' || map_line[i] == 'E' || map_line[i] == 'W' || map_line[i] == 'S')
		{
			game_data->player_init_loc[0] = x_axis;
			game_data->player_init_loc[1] = y_axis;
			game_data->player->y = y_axis * MINIMAP_SQUARE_SIDE_LEN + MINIMAP_SQUARE_SIDE_LEN / 2;
			game_data->player->x = x_axis * MINIMAP_SQUARE_SIDE_LEN + MINIMAP_SQUARE_SIDE_LEN / 2;

			if (map_line[i] == 'N')
			{
				game_data->player_init_dir = 'N';
				game_data->maze.g[y_axis][x_axis] = 'N';
			}
			if (map_line[i] == 'E')
			{
				game_data->player_init_dir = 'E';
				game_data->maze.g[y_axis][x_axis] = 'E';
			}

			if (map_line[i] == 'W')
			{
				game_data->player_init_dir = 'W';
				game_data->maze.g[y_axis][x_axis] = 'W';
			}
			if (map_line[i] == 'S')
			{
				game_data->player_init_dir = 'S';
				game_data->maze.g[y_axis][x_axis] = 'S';
			}
			x_axis++;
			i++;
		}
	}
	return (1);
}

int	init_player(t_game *game_data, char direction, int x_axis, int y_axis)
{
	if (game_data->player_init_dir)
		return (ft_putendl_fd("Error", 2), 1);
	game_data->player_init_loc[0] = x_axis;
	game_data->player_init_loc[1] = y_axis;
	game_data->player->y = y_axis * MINIMAP_SQUARE_SIDE_LEN + MINIMAP_SQUARE_SIDE_LEN / 2;
	game_data->player->x = x_axis * MINIMAP_SQUARE_SIDE_LEN + MINIMAP_SQUARE_SIDE_LEN / 2;
	game_data->player_init_dir = direction;
	return (0);
}

int	put_sign(char c, char *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i] && tokens[i] != c)
		i++;
	if (i > 5 && i < 9)
		return ('Z');
	else if (i <= 5)
		return (tokens[i]);
	else
		return (0);
}

int	is_player(t_game *game_data, int y, int x, char *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (game_data->maze.g[y][x] == tokens[i])
			break ;
		i++;
	}
	if (i >= 4)
		return (1);
	else
		return (0);
}

int	parse_maze(t_game *game_data, char *line)
{
	size_t			i;
	static	size_t	j;

	i = 1;
	if (j + 1 == MAZE_DIMENSION)
		return (1); //map is too big
	game_data->maze.g[j + 1][0] = 'Z';
	while (i < MAZE_DIMENSION && line[i - 1])
	{
		game_data->maze.g[j + 1][i] = put_sign(line[i - 1], "NEWS10 \n");
		if (game_data->maze.g[j + 1][i] == 0)
			return (1); //??
		if(!is_player(game_data, j + 1, i, "NEWS"))
			if (init_player(game_data, game_data->maze.g[j + 1][i], i, j + 1))
				return (ft_putendl_fd("Two or more players", 2), 1); //??
		i++;
	}
	if (line[i - 1])
		return (1); // map is too big
	while (i < MAZE_DIMENSION)
		game_data->maze.g[j + 1][i++] = 'Z';
	j++;
	return (0);
}

int map_parsing(char *filename, t_game *game_data)
{
	int fd;
	char *map_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return(perror("Error opening map"), EXIT_FAILURE);
	while (1)
	{
		map_line = get_next_line(fd);
		if (!map_line)
		{
			if (!check_textures(game_data)
				|| !check_colors_ok(game_data))
				return (ft_putendl_fd("Error\nSettings are non-valid", 2), 1);
			close(fd);
			return (0);
		}
		if (check_textures(game_data) && check_colors_ok(game_data))// how many times you want to parse maze?
			parse_maze(game_data, map_line); // maze_parse(game_data, map_line);
		else
		{
			if (router_parse_data(map_line, game_data))
				return(free(map_line), close(fd), 1);
		}
		free(map_line);
	}
	close(fd);
	return (0);
}

int iffile_cub(char *map_file_name)
{
	char *find_ber;

	find_ber = ft_strrchr(map_file_name, '.');
	if (!find_ber || ft_strncmp(find_ber, ".cub", 5) != 0)
	{
		printf("Error: Not a .cub file.\n");
		return (1);
	}
	return (0);
}

int is_valid_char(char matrix_val)
{
	char	set[] = "012NEWS Z\n\t";
	int		i;

	i = -1;
	while (set[++i])
		if (matrix_val == set[i])
			return (1);
	return (0);
}

int is_valid_int(int matrix_val)
{
	if (matrix_val == 1 || matrix_val == 0 || matrix_val == 3)
		return (1);
	else
		return (0);
}

// int of_players(t_game *game_data, char matrix_val)
// {
// 	int i;

// 	i = 0;
// 	if (matrix_val == 'N' || matrix_val == 'S' || matrix_val == 'W' || matrix_val == 'E')
// 	{
// 		i++;
// 		game_data->player_count++;
// 	}
// 	return (i);
// } // just one player per map
