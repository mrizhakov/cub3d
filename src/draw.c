#include "../cub3d.h"

void draw_minimap(t_game *game_data, t_float_pixel start, uint32_t side_len)
{
	t_float_pixel	origin;
	int				x;
	int				y;

	y = 0;
	origin = start;
	while (y != MAZE_DIMENSION - 1)
	{
		x = 0;
		while (x != MAZE_DIMENSION - 1)
		{
			if (game_data->maze.g[y][x] == '1')
				draw_square(game_data, start, side_len);
			start.x += side_len;
			x++;
		}
		start.x = origin.x;
		start.y += side_len;
		y++;
	}
}

int32_t draw_player(t_game *game_data, t_float_pixel *player, uint32_t side_len)
{
	(void)player;
	t_float_pixel player_square;

	player_square.x = (game_data->player->x / game_data->texture_width * MINIMAP_SQUARE_SIDE_LEN) - 1;
	player_square.y = (game_data->player->y / game_data->texture_width * MINIMAP_SQUARE_SIDE_LEN) - 1;
	player_square.color = game_data->player->color;
	// draw_square(game_data, player_square, side_len);
	(void)side_len;
	return(1);
}

// int32_t draw_map_sprite(t_game *game_data, t_float_pixel *sprite, uint32_t side_len)
// {
// 	(void)sprite;
// 	t_float_pixel sprite_square;
// 	size_t	i;

// 	i = 0;
// 	while (game_data->sprites[i].texture)
// 	{
// 		sprite_square.x = (game_data->sprites[i].x / game_data->texture_width * MINIMAP_SQUARE_SIDE_LEN) - 1;
// 		sprite_square.y = (game_data->sprites[i].y / game_data->texture_width * MINIMAP_SQUARE_SIDE_LEN) - 1;
// 		if (game_data->sprites[i].visible)
// 			sprite_square.color = 0xFFFF00FF;
// 		else
// 			sprite_square.color = 0x00FFFFFF;
// 		draw_square(game_data, sprite_square, side_len);
// 		i++;
// 	}
// 	return(0);
// }

void	put_sprite_map(t_raycast data, uint32_t len)
{
	float	i;
	float	j;

	j = 0;
	while (j <= len)
	{
		i = 0;
		data.offSet = 4 * j;
		while (i <= len)
		{
			put_pixel(data.img, data.top + j, data.column + i,
					convertColors(data.texture, data.offSet, 3000));
			i += data.err;
			data.offSet += 4 * data.texture->width;
			if (data.texture->height * data.texture->width * 4
				- data.offSet < 3)
				break ;
		}
		j += data.err;
	}
}

int32_t draw_map_sprite(t_game *game_data, t_float_pixel *sprite, uint32_t side_len)
{
	(void)sprite;
	t_raycast data;
	size_t	i;

	i = 0;
	while (game_data->sprites[i].texture)
	{
		if (!game_data->sprites[i].taken)
		{
			data.top =  (game_data->sprites[i].map_x * MINIMAP_SQUARE_SIDE_LEN) - 1;
			data.bott = data.top + side_len;
			data.img = game_data->img;
			data.column = (game_data->sprites[i].map_y * MINIMAP_SQUARE_SIDE_LEN) - 1;
			data.texture = game_data->textures[TEX_MUSHR_M];
			data.err = side_len / (float)data.texture->height;
			data.offSet = 0;
			put_sprite_map(data, side_len);
		}
		i++;
	}
	return(0);
}
