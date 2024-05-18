#include "../cub3d.h"

void	set_height(t_game *game_data, t_sprite *vis_sprite)
{
	double	sprite_height;
	double	top_pixel;
	double	bott_pixel;

	sprite_height = (game_data->texture_width
						/ vis_sprite->distance) * game_data->dist_proj_plane;
	top_pixel = (WINDOW_HEIGHT / 2)  - (sprite_height / 2);
	if (top_pixel < 0)
		top_pixel = 0;
	bott_pixel = (WINDOW_HEIGHT / 2)  + (sprite_height / 2);
	if (bott_pixel >= WINDOW_HEIGHT)
		bott_pixel = WINDOW_HEIGHT - 1;
	vis_sprite->top_pixel = top_pixel;
	vis_sprite->bott_pixel = bott_pixel;
	vis_sprite->dimentions = sprite_height;
}

void	set_width(t_game *game_data, t_sprite *vis_sprite)
{
	double	posX;
	double	leftX;
	double	rightX;

	posX = tan(vis_sprite->angle) * game_data->dist_proj_plane;
	leftX = (WINDOW_WIDTH / 2) + posX;
	rightX = leftX + vis_sprite->dimentions;
	if (leftX < 0)
		leftX = 0;
	if (rightX >= WINDOW_WIDTH)
		rightX = WINDOW_WIDTH - 1;
	vis_sprite->left_pixel = leftX;
	vis_sprite->right_pixel = rightX;
}

void	detect_vis_sprites(t_game *game_data)
{
	t_sprite	*sprites;
	t_double_pixel	*player;
	double		angle_sprite;
	int			i;

	sprites = game_data->sprites;
	player = game_data->player;
	i = 0;
	// game_data->vis_sprites_no = 0;
	while (sprites[i].texture) // change to nu of sprites
	{
		angle_sprite = game_data->player_angle
			- atan2(sprites[i].y - player->y, sprites[i].x - player->x);
		if (angle_sprite > M_PI)
			angle_sprite -= 2 * M_PI;
		if (angle_sprite < - M_PI)
			angle_sprite += 2 * M_PI;
		angle_sprite = fabs(angle_sprite);
		if (angle_sprite < (game_data->fov_angle / 2))
		{
			sprites[i].distance = distance_between_points(sprites[i].x, sprites[i].y, player->x, player->y);
			sprites[i].angle = fmod(atan2(sprites[i].y - player->y, sprites[i].x - player->x) - game_data->player_angle + M_PI,
									2 * M_PI) - M_PI;
			sprites[i].visible = true;
		}
		else
			sprites[i].visible = false;
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
	game_data->sprites[i].x = x * game_data->texture_width + game_data->texture_width / 2;
	game_data->sprites[i].y = y * game_data->texture_width + game_data->texture_width / 2;
	if (t == 'M')
		game_data->sprites[i].texture = MUSHR;
	return (0);
}

void	draw_sprites(t_game	*game_data)
{
	int			i;
	double		line;

	detect_vis_sprites(game_data);
	i = 0;
	while (game_data->sprites[i].texture)
	{
		if (game_data->sprites[i].visible)
		{
			set_height(game_data, &game_data->sprites[i]);
			set_width(game_data, &game_data->sprites[i]);
			line = game_data->sprites[i].top_pixel;
			uint32_t	texOffset = 0;
			// double err_line = (game_data->sprites[i].bott_pixel - game_data->sprites[i].top_pixel) / game_data->texture_width;
			while (line < game_data->sprites[i].bott_pixel)
			{

				mlx_texture_t	*texture = game_data->textures[game_data->sprites[i].texture];
				double	colon;
				double	err_colon = (game_data->sprites[i].right_pixel - game_data->sprites[i].left_pixel)
							/ game_data->texture_width;
				colon = game_data->sprites[i].left_pixel;
				while (colon < game_data->sprites[i].right_pixel)
				{
					uint32_t index = ((colon - game_data->sprites[i].left_pixel) + texOffset) * 4;
					put_pixel(game_data->img, colon, line,
								convertColors(texture, index, game_data->sprites[i].distance));
					// double prev_colon = colon;
					colon += err_colon;
					// colon++;
					// while (colon - prev_colon > 1)
					// {
					// 	printf("(int)(colon - prev_colon) > 1");
					// 	put_pixel(game_data->img, prev_colon++, line,
					// 			convertColors(texture, index, game_data->sprites[i].distance));
					// }
				}
				texOffset += texture->width;
				if (texOffset > texture->width * texture->height)
					texOffset = 0;
				// double prev_line = line;
				// line += err_line;
				line++;
				// while ((int)(line - prev_line) > 1)
				// {
				// 	colon = 0;
				// 	while (colon < game_data->sprites[i].right_pixel)
				// 	{
				// 		uint32_t index = ((colon - game_data->sprites[i].left_pixel) + texOffset) * 4;
				// 		put_pixel(game_data->img, colon, line,
				// 					convertColors(texture, index, game_data->sprites[i].distance));
				// 		double prev_colon = colon;
				// 		colon += err_colon;
				// 		while ((int)(colon - prev_colon) > 1)
				// 			put_pixel(game_data->img, prev_colon++, line,
				// 					convertColors(texture, index, game_data->sprites[i].distance));
				// 	}
				// 	prev_line++;
				// }
			}
		}
		i++;
	}
}
