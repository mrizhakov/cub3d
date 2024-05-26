#include "../cub3d.h"

int	find_wall(t_maze maze, int y, int x, int pad, int del)
{
	if (maze.g[(y) / del][(x + pad) / del] == '1')
		return (1);
	if (maze.g[(y) / del][(x - pad) / del] == '1')
		return (1);
	if (maze.g[(y - pad) / del][(x) / del] == '1')
		return (1);
	if (maze.g[(y - pad) / del][(x + pad) / del] == '1')
		return (1);
	if (maze.g[(y - pad) / del][(x - pad) / del] == '1')
		return (1);
	if (maze.g[(y + pad) / del][(x) / del] == '1')
		return (1);
	if (maze.g[(y + pad) / del][(x + pad) / del] == '1')
		return (1);
	if (maze.g[(y + pad) / del][(x - pad) / del] == '1')
		return (1);
	return (0);
}

int	find_door(t_game *game_data, int y, int x, int pad, int del)
{
	int	i;

	i = 0;
	if (game_data->maze.g[(y) / del][(x + pad) / del] == 'D')
		if (!which_door(game_data, (y) / del, (x + pad) / del)->isopen)
			i = 1;
	if (game_data->maze.g[(y) / del][(x - pad) / del] == 'D')
		if (!which_door(game_data, (y) / del, (x - pad) / del)->isopen)
			i = 1;
	if (game_data->maze.g[(y - pad) / del][(x) / del] == 'D')
		if (!which_door(game_data, (y - pad) / del, (x) / del)->isopen)
			i = 1;
	if (game_data->maze.g[(y + pad) / del][(x) / del] == 'D')
		if (!which_door(game_data, (y + pad) / del, (x) / del)->isopen)
			i = 1;
	return (i);
}
