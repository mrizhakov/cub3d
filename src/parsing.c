/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:04:16 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/01 15:18:07 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_colors_ok(t_game *game_data)
{
	t_rgb	rgb;

	if (game_data->color_count[F] == 1
		&& game_data->color_count[C] == 1
		&& game_data->color[F].valid_rgb == 1
		&& game_data->color[C].valid_rgb == 1)
	{
		rgb = game_data->color[F];
		game_data->color[F].rgb_color = (int32_t)ft_float_pixel(rgb.color[0]
				% 0xFF, rgb.color[1] % 0xFF, rgb.color[2] % 0xFF, 255);
		rgb = game_data->color[C];
		game_data->color[C].rgb_color = (int32_t)ft_float_pixel(rgb.color[0]
				% 0xFF, rgb.color[1] % 0xFF, rgb.color[2] % 0xFF, 255);
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}

int	init_player(t_game *game_data, char direction, int x_axis, int y_axis)
{
	if (game_data->player_init_dir)
		return (ft_putendl_fd("Error", 2), 1);
	game_data->player_init_loc[0] = x_axis;
	game_data->player_init_loc[1] = y_axis;
	game_data->player->y = y_axis
		* game_data->texture_width + game_data->texture_width / 2;
	game_data->player->x = x_axis
		* game_data->texture_width + game_data->texture_width / 2;
	game_data->player_init_dir = direction;
	game_data->player->color = 0x00FF00FF;
	if (direction == 'N')
		game_data->player_angle = -M_PI / 2;
	else if (direction == 'S')
		game_data->player_angle = M_PI / 2;
	else if (direction == 'E')
		game_data->player_angle = 0;
	else
		game_data->player_angle = M_PI;
	return (EXIT_SUCCESS);
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
		if (init_doors(game_data, tokens[i], x, y))
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

int	parse_maze(t_game *game_data, char *line)
{
	int			i;
	static int	j;

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
		if (tokenize(game_data, j + 1, i, VALID_CHAR_MAP) == 1)
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

int	map_parsing(char *filename, t_game *game_data)
{
	int		fd;
	char	*map_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening map"), EXIT_FAILURE);
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
			return (free(map_line), parsing_error("Error\nWrong maze", fd));
		else
			if (router_parse_data(map_line, game_data))
				return (free(map_line),
					parsing_error("Error\nWrong textures", fd));
		free(map_line);
	}
}
