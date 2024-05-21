#include "../cub3d.h"

int		load_textures(t_game *game_data)
{
	int	i;

	i = 0;
	while (i < TEX_NO)
	{
		game_data->textures[i] = mlx_load_png(game_data->texture_filename[i]);
		i++;
	}
	game_data->icon = mlx_load_png(ICON);
	if (!game_data->icon)
		ft_putendl_fd("Warning\nIcon is not set", 2);
	while (--i >= 0)
	{
		if (!game_data->textures[i])
			return (free_textures(game_data), 1);
	}
	return (0);
}
