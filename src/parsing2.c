#include "../cub3d.h"

int	parse_texture_file(t_direct direction, t_game *game_data, char *link)
{
	int		texture_fd;
	char	*file_name;

	if (!link || !link[0])
		return ("Empty file name for texture", 1);
	file_name = ft_strtrim(link, "\n");
	texture_fd = open(file_name, O_RDONLY);
	if (!texture_fd)
		return(perror("Error opening texture files"), 2);
	if (check_file_extension(file_name, ".png") || check_read_file(texture_fd))
		return (close(texture_fd), ft_putendl_fd("Error reading png file", 2), 2);
	if (direction == NO)
		game_data->no_texture_filename = file_name;
	else if (direction == SO)
		game_data->so_texture_filename = file_name;
	else if (direction == WE)
		game_data->we_texture_filename = file_name;
	else if (direction == EA)
		game_data->ea_texture_filename = file_name;
	game_data->texture_count[direction] += 1;
	return (0);
}

int parse_color(t_colors color, t_game *game_data, char *data)
{
	char	**colors;
	t_rgb	rgb;
	size_t	i;

	data = ft_strtrim(data, "\n");
	colors = ft_split(data, ',');
	i = 0;
	while (colors[i])
	{
		if (i >= 3)
			return (rgb.valid_rgb = -1, 1);
		rgb.color[i] = ft_atoi(colors[i]);

	}

}

int	router(char *line, t_game *game_data)
{
	char	**tokens;
	char	*token_texture[] = {"NO", "SO", "WE", "EA"};
	char	*token_color[] = {"F", "C"};
	size_t	i;
	size_t	j;

	i = 0;
	tokens = ft_split(line, ' ');
	while (tokens[i])
	{
		j = 0;
		while (token_texture[j])
			if (!ft_strncmp(tokens[i], token_texture[j++], ft_strlen(tokens[i]))
				&& parse_texture_file(j - 1, game_data, tokens[i + 1]))
					return (1); // free memory
		j = 0;
		while (token_color[j])
			if (!ft_strncmp(tokens[i], token_texture[j++], ft_strlen(tokens[i]))
				&& parse_color(j - 1, game_data, tokens[i + 1]))
					return (1); //free memory
		i++;
	}
}
