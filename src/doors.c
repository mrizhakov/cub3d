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
	game_data->doors[i].map_x = x;
	game_data->doors[i].map_y = y;
	if (t == 'D')
		game_data->doors[i].texture = TEX_DOOR_CL;
	return (0);
}

t_doors	*which_door(t_game *game_data, int y, int x)
{
	int i;

	i = 0;
	if (y >= MAZE_DIMENSION || x >= MAZE_DIMENSION)
		return (NULL);
	while (game_data->doors[i].texture)
	{
		if (game_data->doors[i].map_x == x
			&& game_data->doors[i].map_y == y)
			return (&game_data->doors[i]);
		i++;
	}
	ft_putendl_fd("Warning\ndoor not found", 2);
	return (game_data->doors);
}
