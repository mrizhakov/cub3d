#include "../cub3d.h"

t_sprite	*use_mushr(t_game *game_data)
{
	int	i;

	i = -1;
	while (game_data->sprites[++i].texture)
	{
		if (game_data->sprites[i].taken)
		{
			game_data->sprites[i].taken = false;
			return (&game_data->sprites[i]);
		}
	}
	return NULL;
}

void	psycho_trigger(t_game *game_data)
{

	//use mushroom
	if (mlx_get_time() - game_data->phycho_time > PSYCHO && use_mushr(game_data))
	{
		game_data->psycho = true;
		game_data->phycho_time = mlx_get_time();
		if (arc4random() % 2 == 1)
			game_data->dist_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	}
}
