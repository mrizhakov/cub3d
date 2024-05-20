#include "../cub3d.h"

int	init_doors(t_game *game_data, char t, int x, int y)
{
	int			i;

	i = 0;
	while (game_data->doors[i].texture)
		i++;
	if (i >= 10)
		return (1);
	game_data->doors[i].x = x * game_data->texture_width;
	game_data->doors[i].y = y * game_data->texture_width;
	if (t == 'C')
		game_data->sprites[i].texture = DOOR;
	return (0);
}
