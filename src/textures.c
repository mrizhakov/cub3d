#include "../cub3d.h"

int	load_textures(t_game *game_data)
{
	t_textures	*textures;

	//ft_printf("\n\nLoading textures\n\n");
	textures = ft_calloc(1, sizeof(t_textures));

	//add function to read file and save it as char *
	// textures->north = mlx_load_png(game_data->textures->mlx->NORTH );
	// textures->south = mlx_load_png(game_data->textures->mlx->SOUTH);
	// textures->east  = mlx_load_png(game_data->textures->mlx->EAST );
	// textures->west  = mlx_load_png(game_data->textures->mlx->WEST);
	game_data->textures = textures;
	return (0);
}
