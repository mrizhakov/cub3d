#include "../cub3d.h"

int		load_textures(t_game *game_data)
{
	(void)game_data;
	game_data->textures = malloc(sizeof (t_textures));
	if (!game_data->textures)
		return (1);
    game_data->textures->north = mlx_load_png(game_data->no_texture_filename);
	game_data->textures->east = mlx_load_png(game_data->ea_texture_filename);
    game_data->textures->west = mlx_load_png(game_data->we_texture_filename);
    game_data->textures->south = mlx_load_png(game_data->so_texture_filename);
	if (!game_data->textures->north || !game_data->textures->east 
		|| !game_data->textures->west || !game_data->textures->south)
	{
		free_textures(game_data);
		return 1;
	}
    return 0;    
}
