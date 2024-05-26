#include "../cub3d.h"

int	check_texture(const char *texture, int texture_count)
{
	if (texture && texture_count == 1)
		return (1);
	else
		return (0);
}

int	check_textures(t_game *game_data)
{
	int	i;
	int	texture;

	texture = 0;
	while (texture < TEX_NO)
	{
		i = check_texture(game_data->texture_filename[texture], game_data->texture_count[texture]);
		if (i == 0)
		{
			game_data->all_textures_ok = i;
			return (i);
		}
		texture++;
	}
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
		game_data->color[F].rgb_color = (int32_t)ft_float_pixel(game_data->color[F].color[0] % 0xFF, game_data->color[F].color[1]% 0xFF, game_data->color[F].color[2]% 0xFF, 255);
		game_data->color[C].rgb_color = (int32_t)ft_float_pixel(game_data->color[C].color[0] % 0xFF, game_data->color[C].color[1]% 0xFF, game_data->color[C].color[2]% 0xFF, 255);
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
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
	game_data->player->y = y_axis * game_data->texture_width + game_data->texture_width / 2; // NOLINT(*-narrowing-conversions, *-integer-division)
	game_data->player->x = x_axis * game_data->texture_width + game_data->texture_width / 2; // NOLINT(*-narrowing-conversions, *-integer-division)
	game_data->player_init_dir = direction;
	game_data->player->color = 0x00FF00FF;
	if (direction == 'N')
		game_data->player_angle = - M_PI / 2;
	else if (direction == 'S')
		game_data->player_angle = M_PI / 2;
	else if (direction == 'E')
		game_data->player_angle = 0;
	else
		game_data->player_angle = M_PI;
	return (EXIT_SUCCESS);
}

char	put_sign(char c, char *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i] && tokens[i] != c)
		i++;
	if (i > 7 && i < 10)
		return ('X');
	else if (i <= 7)
		return (tokens[i]);
	else
		return (0);
}

int	tokenize(t_game *game_data, int y, int x, char *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (game_data->maze.g[y][x] == tokens[i])
			break ;
		i++;
	}
	if (i == 4)
	{
		if (init_sprites(game_data, tokens[i], x, y))
			return (ft_putendl_fd("Error\nMax 10 sprites allowed", 2), 1);
	}
	else if (i == 5)
	{
		if (init_doors(game_data, tokens[i], x ,y))
			return (ft_putendl_fd("Error\nMax 10 doors allowed", 2), 1);
	}
	else if (i > 4)
		return (2);
	else
	{
		if (init_player(game_data, tokens[i], x, y))
			return (ft_putendl_fd("Error\nTwo or more players", 2), 1);
	}
	return (0);
}

int	check_parse(size_t j, t_game *game_data)
{
	if (j == 0)
		return (0);
	if (maze_check(game_data))
		return (1);
	else
		return (0);
}

int	ft_istabs(char *line)
{
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
	int			i;
	static	int	j;

	i = 1;
	if (j + 1 == MAZE_DIMENSION)
		return (EXIT_FAILURE);
	if (ft_istabs(line))
		return (check_parse(j, game_data));
	while (i < MAZE_DIMENSION && line[i - 1])
	{
		game_data->maze.g[j + 1][i] = put_sign(line[i - 1], VALID_CHAR_MAP);
		if (game_data->maze.g[j + 1][i] == 0)
			return (EXIT_FAILURE);
		if(tokenize(game_data, j + 1, i, VALID_CHAR_MAP) == 1)
			 return (EXIT_FAILURE);
		i++;
	}
	if (line[i - 1])
		return (EXIT_FAILURE);
	while (i < MAZE_DIMENSION)
		game_data->maze.g[j + 1][i++] = 'X';
	j++;
	return (EXIT_SUCCESS);
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
				return (parsing_error("Error\nSettings are non-valid", fd));
			return (close(fd), 0);
		}
		if (check_textures(game_data) && check_colors_ok(game_data)
			&& parse_maze(game_data, map_line))
				return(free(map_line), parsing_error("Error\nWrong maze", fd));
		else
			if (router_parse_data(map_line, game_data))
				return(free(map_line), parsing_error("Error\nWrong textures", fd));
		free(map_line);
	}
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
