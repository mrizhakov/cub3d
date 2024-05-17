#include "../cub3d.h"



void	detect_vis_sprites(t_game *game_data)
{
	t_sprite	*sprites;
	t_double_pixel	*player;
	double		angle_sprite;
	int			i;

	sprites = game_data->sprites;
	player = game_data->player;
	i = 0;
	while (i < 1) // change to nu of sprites
	{
		angle_sprite = game_data->player_angle
			- atan2(sprites[i].y - player->y, sprites[i].x - player->x);
		if (angle_sprite < (FOV / 2))
		{
			sprites[i].distance = distance_between_points(sprites[i].x, sprites[i].y,player->x,player->y);
			game_data->vis_sprite[game_data->vis_sprites] = sprites[i];
			game_data->vis_sprites++;
		}
		i++;
	}
}

int	init_sprites(t_game *game_data, char t, int x, int y)
{
	int			i;

	i = 0;
	while (game_data->sprites[i].texture)
		i++;
	if (i >= 10)
		return (1);
	game_data->sprites[i].x = x;
	game_data->sprites[i].y = y;
	if (t == 'M')
		game_data->sprites[i].texture = MUSHR;
	detect_vis_sprites(game_data);
	return (0);
}

void	draw_sprites(t_game	*game_data)
{
	double	sprite_height;
	double	top_pixel;
	double	bott_pixel;
	t_sprite	vis_sprites;

	vis_sprites = game_data->vis_sprite[0]; // while loop this
	sprite_height = game_data->texture_width / vis_sprites.distance * game_data->dist_proj_plane;
	top_pixel = (WINDOW_HEIGHT / 2)  - (sprite_height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	bott_pixel = (WINDOW_HEIGHT / 2)  + (sprite_height / 2);
	if (bott_pixel >= WINDOW_HEIGHT)
		bott_pixel = WINDOW_HEIGHT - 1;
	for (int i = top_pixel; i < bott_pixel; i++)
	{
		for(int j = 1; j < 4; j++)
			mlx_put_pixel(game_data->img, j, i, 0xFF0000FF);
	}
}
