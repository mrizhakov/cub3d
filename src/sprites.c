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
	while (i < 10)
	{
		angle_sprite = game_data->player_angle
			- atan2(sprites[i].y - player->y, sprites[i].x - player->x);
		if (angle_sprite < (FOV / 2))
		{
			game_data->vis_sprite[game_data->vis_sprites] = sprites[i];
			game_data->vis_sprites++;
		}
	}
}

void	draw_sprites()
{

}
