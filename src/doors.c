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

void	detect_vis_door(t_game *game_data)
{
	t_doors	*doors;
	t_double_pixel	*player;
	double		angle_sprite;
	int			i;

	doors = game_data->doors;
	player = game_data->player;
	i = 0;
	while (doors[i].texture)
	{
		angle_sprite = game_data->player_angle
			- atan2(doors[i].y - player->y, doors[i].x - player->x);
		if (angle_sprite > M_PI)
			angle_sprite -= 2 * M_PI;
		if (angle_sprite < -M_PI)
			angle_sprite += 2 * M_PI;
		angle_sprite = fabs(angle_sprite);
		if (angle_sprite < (game_data->fov_angle / 2))
		{
			doors[i].distance = distance_between_points(player->x, player->y, doors[i].x, doors[i].y);
			doors[i].angle = atan2(doors[i].y - player->y, doors[i].x - player->x) - game_data->player_angle + M_PI;
			doors[i].visible = true;
		}
		else
			doors[i].visible = false;
		i++;
	}
}

void	open_door(t_game *game_data)
{
	int	i;
	int	closiest;
	double	distance;

	distance = FLT_MAX;
	i = 0;
	detect_vis_door(game_data);
	while (game_data->doors[i].texture)
	{
		if (game_data->doors[i].distance < distance &&
			game_data->doors[i].visible)
		{
			distance = game_data->doors[i].distance;
			closiest = i;
		}
		i++;
	}
	if (distance < (float)800 && !game_data->doors[closiest].isopen
		&& mlx_get_time() - game_data->doors[closiest].animation_time > 2)
	{
		game_data->doors[closiest].isopen = true;
		game_data->doors[closiest].animation_time = mlx_get_time();
	}
	else if (distance < (float)800
			&& mlx_get_time() - game_data->doors[closiest].animation_time > 2)
	{
		game_data->doors[closiest].isopen = false;
		game_data->doors[closiest].animation_time = mlx_get_time();
	}
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
	return (NULL);
}
