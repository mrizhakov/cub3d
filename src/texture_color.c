#include "../cub3d.h"

int	parse_texture_file(t_direct direction, t_game *game_data, char *link)
{
	int		texture_fd;
	char	*file_name;

	if (!link || !link[0])
		return (ft_putendl_fd("Empty file name for texture", 2), 1);
	file_name = ft_strtrim(link, "\n");
	texture_fd = open(file_name, O_RDONLY);
	if (texture_fd == -1)
		return(free(file_name), perror("Error opening texture files"), 2);
	if (check_file_extension(file_name, ".png") || check_read_file(texture_fd))
		return (free(file_name), close(texture_fd), ft_putendl_fd("Error reading png file", 2), 2);
	game_data->texture_filename[direction] = file_name;
	game_data->texture_count[direction] += 1;
	return (0);
}

int parse_color_data(t_surface surface, t_game *game_data, char *data)
{
	char	**colors;
	t_rgb	rgb;
	ssize_t	i;
	size_t	j;

	data = ft_strtrim(data, "\n");
	colors = ft_split(data, ',');
	free(data);
	i = 0;
	while (colors[i])
	{
		j = 0;
		while(colors[i][j])
			if (!ft_isdigit(colors[i][j++]))
				return (free_char_arr(colors), rgb.valid_rgb = -1, 1);
		if (i >= 3)
			return (free_char_arr(colors), rgb.valid_rgb = -1, 1);
		rgb.color[i] = ft_atoi(colors[i]);
		i++;
	}
	if (i < 3)
		return (free_char_arr(colors), rgb.valid_rgb = -1, 1);
	i = -1;
	while (++i < 3)
		if (rgb.color[i] < 0 || rgb.color[i] > 255)
			return (free_char_arr(colors), rgb.valid_rgb = -1, 1);
	free_char_arr(colors);
	game_data->color[surface] = rgb;
	game_data->color_count[surface]++;
	game_data->color[surface].valid_rgb = 1;
	return (0);
}

int	router_parse_data(char *line, t_game *game_data)
{
	char	**tokens;
	char	*token_texture[] = {"NO", "SO", "WE", "EA", "MU", "MU2", "MUM", "DO0", "DO1", "DO2", "PS1", "PS2", "PS3", NULL};
	char	*token_color[] = {"F", "C", NULL};
	int	i;
	int	j;

	i = 0;
	tokens = ft_split(line, ' ');
	while (tokens[i])
	{
		j = -1;
		while (token_texture[++j])
			if (!ft_strncmp(tokens[i], token_texture[j], 3) // why 3?
				&& parse_texture_file(j, game_data, tokens[i + 1]))
					return (free_char_arr(tokens), 1);
		j = -1;
		while (token_color[++j])
			if (!ft_strncmp(tokens[i], token_color[j], 3) // why 3?
				&& parse_color_data(j, game_data, tokens[i + 1]))
					return (free_char_arr(tokens), 1);
		i++;
	}
	free_char_arr(tokens);
	return (0);
}
