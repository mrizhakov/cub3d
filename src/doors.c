#include "../cub3d.h"

int	check_door_place(t_game *game_data, int y, int x)
{
	bool	i;
	char	map[40][40];

	i = true;
	ft_memcpy(map, game_data->maze.g, sizeof(map));
	if (y > 0 && y < MAZE_DIMENSION - 1)
		if (map[y - 1][x] == '1' && map[y + 1][x] == '1')
			i = !i;
	if (x > 0 && x < MAZE_DIMENSION - 1)
		if (map[y][x - 1] == '1' && map[y][x + 1] == '1')
			i = !i;
	return (i);
}

int	init_doors(t_game *game_data, char t, int x, int y)
{
	int			i;

	i = 0;
	while (game_data->doors[i].texture)
		i++;
	if (i >= 10)
		return (1);
	game_data->doors[i].x = x * game_data->texture_width + game_data->texture_width / 2;
	game_data->doors[i].y = y * game_data->texture_width + game_data->texture_width / 2;
	if (t == 'C')
		game_data->doors[i].texture = DOOR;
	return (0);
}
