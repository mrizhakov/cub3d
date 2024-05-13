/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:00:24 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/05/13 13:40:38 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int check_colors_ok(t_game *game_data)
{
	if (game_data->color_count[F] == 1
		&& game_data->color_count[C] == 1
		&& game_data->color[F].valid_rgb == 1
		&& game_data->color[C].valid_rgb == 1)
	{
		game_data->color[F].rgb_color = (int32_t)ft_double_pixel(game_data->color[F].color[0] % 0xFF, game_data->color[F].color[1]% 0xFF, game_data->color[F].color[2]% 0xFF, 255);
		game_data->color[C].rgb_color = (int32_t)ft_double_pixel(game_data->color[C].color[0] % 0xFF, game_data->color[C].color[1]% 0xFF, game_data->color[C].color[2]% 0xFF, 255);
		return (1);
	}
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
	if (i > 5 && i < 8)
		return ('X');
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

int	check_parse(size_t j, t_game *game_data)
{
	if (j == 0)
		return (0);
	if (maze_check_closed(game_data))
		return (1);
	else
		return (0);
}

int	ft_istabs(char *line)
{
	// size_t	i;

	// i = 0;
	if (line[0] >= '\t' && line[0] <= '\r')
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	parse_maze(t_game *game_data, char *line)
{
	size_t			i;
	static	size_t	j;

	i = 1;
	if (j + 1 == MAZE_DIMENSION)
		return (1);
	if (ft_istabs(line))
		return (check_parse(j, game_data));
	while (i < MAZE_DIMENSION && line[i - 1])
	{
		game_data->maze.g[j + 1][i] = put_sign(line[i - 1], "NEWS10 \n");
		if (game_data->maze.g[j + 1][i] == 0)
			return (ft_putendl_fd("Error\nMap error", 2), 1); //??
		if(!is_player(game_data, j + 1, i, "NEWS"))
			if (init_player(game_data, game_data->maze.g[j + 1][i], i, j + 1))
				return (ft_putendl_fd("Error\nTwo or more players", 2), 1); //??
		i++;
	}
	if (line[i - 1])
		return (1); // map is too big
	while (i < MAZE_DIMENSION)
		game_data->maze.g[j + 1][i++] = 'X';
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
			if (!check_textures(game_data) || !check_colors_ok(game_data))
				return (ft_putendl_fd("Error\nSettings are non-valid", 2), 1);
			return (close(fd), 0);
		}
		if (check_textures(game_data) && check_colors_ok(game_data)
			&& parse_maze(game_data, map_line))
				return(free(map_line), close(fd), 1);
		else
			if (router_parse_data(map_line, game_data))
				return(free(map_line), close(fd), 1);
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
