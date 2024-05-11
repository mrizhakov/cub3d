#include "../cub3d.h"

int		load_textures(t_game *game_data)
{
	(void)game_data;
	game_data->textures = malloc(sizeof (t_textures));
	if (!game_data->textures)
		return (1);
    game_data->textures->north = mlx_load_png(game_data->texture_filename[NO]);
    game_data->textures->south = mlx_load_png(game_data->texture_filename[SO]);
    game_data->textures->west = mlx_load_png(game_data->texture_filename[WE]);
	game_data->textures->east = mlx_load_png(game_data->texture_filename[EA]);
	if (!game_data->textures->north || !game_data->textures->east
		|| !game_data->textures->west || !game_data->textures->south)
	{
		free_textures(game_data);
		return 1;
	}
    return 0;
}
