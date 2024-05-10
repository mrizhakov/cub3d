/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:00:24 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/05/10 14:01:35 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char *parse_textures(char *map_line, char *direction)
{
	char *texture_line;
	char *texture_filename;
	int texture_fd;

	texture_line = ft_strnstr(map_line, direction, ft_strlen(map_line));
	if (!texture_line)
		return (NULL);
	if (texture_line != map_line)
		return (NULL);
	texture_line += 2;
	texture_filename = ft_strtrim(texture_line, " \n");
	texture_fd = open(texture_filename, O_RDONLY);
	if (texture_fd == -1)
		return(free(texture_filename), perror("Error opening texture files"), NULL);
	if (check_file_extension(texture_filename, ".png") || check_read_file(texture_fd))
	{
		perror("Texture files are no bueno. Bring your nice .png's!"); // perror does not contain error
		free(texture_filename);
		free(map_line);
		close(texture_fd);
		return (NULL);
	}
	return (texture_filename);
}

int	check_texture(char *texture, int texture_count)
{
	if (texture && texture_count == 1)
		return (1);
	else
		return (0);
}

int	check_textures_ok(t_game *game_data)
{
	int	i;

	i = check_texture(game_data->no_texture_filename, game_data->texture_count[NO]);
	i = check_texture(game_data->so_texture_filename, game_data->texture_count[SO]);
	i = check_texture(game_data->we_texture_filename, game_data->texture_count[WE]);
	i = check_texture(game_data->ea_texture_filename, game_data->texture_count[EA]);
	game_data->all_textures_ok = i;
	return (i);
}

int parse_directions(t_game *game_data, char *map_line)
{
	if (ft_strnstr(map_line, "NO", ft_strlen(map_line)))
	{
		if (!game_data->no_texture_filename)
			game_data->no_texture_filename = parse_textures(map_line, "NO");
		game_data->texture_count[NO]++;
	}
	if (ft_strnstr(map_line, "SO", ft_strlen(map_line)))
	{
		if (!game_data->so_texture_filename)
			game_data->so_texture_filename = parse_textures(map_line, "SO");
		game_data->texture_count[SO]++;
	}
	if (ft_strnstr(map_line, "WE", ft_strlen(map_line)))
	{
		if (!game_data->we_texture_filename)
			game_data->we_texture_filename = parse_textures(map_line, "WE");
		game_data->texture_count[WE]++;
	}
	if (ft_strnstr(map_line, "EA", ft_strlen(map_line)))
	{
		if (!game_data->ea_texture_filename)
			game_data->ea_texture_filename = parse_textures(map_line, "EA");
		game_data->texture_count[EA]++;
	}
	return (check_textures_ok(game_data)); // why checking textures all the time?
}

t_rgb read_color(char *map_line, char *surface)
{
	t_rgb rgb;

	rgb.valid_rgb = -1;
	char *color_line;
	char *color_def;

	color_line = ft_strnstr(map_line, surface, ft_strlen(map_line));
	if (!color_line)
		return (rgb);
	color_line++;
	color_def = ft_strtrim(color_line, " \n"); // malloc here
	char **color_array = ft_split(color_def, ',');

	int i = 0;
	while (color_array[i] != NULL)
	{
		rgb.color[i] = ft_atoi(color_array[i]);
		printf("Array %i is : |%d|\n", i, rgb.color[i]);
		i++;
		if (i > 3)
		{
			perror("Invalid color");
			free_to_null_string(&color_def);
			rgb.valid_rgb = -1;
			return (rgb);
		}
	}

	int y = 0;
	while (y != i && rgb.color[y] >= 0 && rgb.color[y] <= 255)
	{
		printf("Y is %i\n", y);
		y++;
	}
	rgb.valid_rgb = 1;
	if (y != 3)
	{
		rgb.valid_rgb = -1;
		printf("Y is %i, triggered unvalidity check\n", y);
	}
	printf("Is it a valid RGB? r : %i, g: %i. b: %i, validity: %i\n", rgb.color[0], rgb.color[1], rgb.color[2], rgb.valid_rgb);
	free_to_null_string(&color_def);
	free_to_null_char_arr(color_array);
	return (rgb);
}

int parse_color(t_game *game_data, char *map_line)
{
	if (ft_strnstr(map_line, "F", ft_strlen(map_line)))
	{
		game_data->floor_count++;
		if (game_data->floor.valid_rgb == -1)
			game_data->floor = read_color(map_line, "F");
	}
	if (ft_strnstr(map_line, "C", ft_strlen(map_line)))
	{
		game_data->ceiling_count++;
		if (game_data->ceiling.valid_rgb == -1)
			game_data->ceiling = read_color(map_line, "C");
	}
	return (0);
}

int check_colors_ok(t_game *game_data)
{
	if (game_data->floor_count == 1
		&& game_data->ceiling_count == 1
		&& game_data->floor.valid_rgb == 1
		&& game_data->ceiling.valid_rgb == 1)
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
		if (map_line == NULL)
		{
			if (!check_textures_ok(game_data)
				|| !check_colors_ok(game_data))
				return (1);
			close(fd);
			return (0);
		}
		parse_directions(game_data, map_line); // returns 1 if everything correct
		parse_color(game_data, map_line);
		if (game_data->all_textures_ok == 1 && check_colors_ok(game_data)) // how many times you want to parse maze?
			maze_parse(game_data, map_line);

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

int no_of_players(t_game *game_data, char matrix_val)
{
	int i;

	i = 0;
	if (matrix_val == 'N' || matrix_val == 'S' || matrix_val == 'W' || matrix_val == 'E')
	{
		i++;
		game_data->player_count++;
	}
	return (i);
} // just one player per map
