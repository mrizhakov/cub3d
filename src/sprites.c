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
	vis_sprite->err_line = sprite_height / game_data->textures[vis_sprite->texture]->height;
}

void	set_width(t_game *game_data, t_sprite *vis_sprite)
{
	double	posX;
	double	leftX;
	double	rightX;

	posX = tan(vis_sprite->angle) * game_data->dist_proj_plane;
	leftX = (WINDOW_WIDTH / 2) + posX - vis_sprite->dimentions / 2;
	rightX = leftX + vis_sprite->dimentions;
	// if (leftX < 0)
	// 	leftX = 0;
	// if (rightX >= WINDOW_WIDTH)
	// 	rightX = WINDOW_WIDTH - 1;
	vis_sprite->left_pixel = leftX;
	vis_sprite->right_pixel = rightX;
	vis_sprite->err_colon = vis_sprite->dimentions / game_data->texture_width;
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
	while (sprites[i].texture)
	{
		angle_sprite = game_data->player_angle
			- atan2(sprites[i].y - player->y, sprites[i].x - player->x);
		if (angle_sprite > M_PI)
			angle_sprite -= 2 * M_PI;
		if (angle_sprite < -M_PI)
			angle_sprite += 2 * M_PI;
		angle_sprite = fabs(angle_sprite);
		if (angle_sprite < (game_data->fov_angle / 2))
		{
			sprites[i].distance = distance_between_points(player->x, player->y, sprites[i].x, sprites[i].y);
			sprites[i].angle = atan2(sprites[i].y - player->y, sprites[i].x - player->x) - game_data->player_angle + M_PI;
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

static void	draw_sprite_line(t_game *game_data, t_sprite sprite,
								double offset, double line)
{
	double			left;
	mlx_texture_t	*texture;
	uint32_t		index;
	double			prev_left;
	t_color			color;

	texture = game_data->textures[sprite.texture];
	index = offset * 4;
	left = sprite.left_pixel;
	while (left < sprite.right_pixel)
	{
		color = convertColors(texture, index, sprite.dimentions);
		if (sprite.distance < game_data->z_buffer[(int)left])
			put_pixel(game_data->img, left, line, color);
		prev_left = left;
		left += sprite.err_colon;
		while ((left - prev_left) > 1 && prev_left < sprite.right_pixel - 1)
		{
			if (sprite.distance < game_data->z_buffer[(int)++prev_left])
				put_pixel(game_data->img, prev_left, line, color);
		}
		index += 4;
	}
}

static void	draw_sprite(t_game *game_data, t_sprite	sprite)
{
	double			line;
	double			prev_line;
	uint32_t		texOffset;
	mlx_texture_t	*texture;

	line = sprite.top_pixel;
	texOffset = 0;
	texture = game_data->textures[sprite.texture];
	while (line < sprite.bott_pixel)
	{
		draw_sprite_line(game_data, sprite, texOffset, line);
		texOffset += texture->width;
		if (texOffset >= texture->width * texture->height)
			break ;
		prev_line = line;
		line += sprite.err_line;
		while ((line - prev_line) > 1 && prev_line < sprite.bott_pixel - 1)
			draw_sprite_line(game_data, sprite, texOffset, ++prev_line);

	}
}

void	sort_sprites(t_sprite sprites[10])
{
	uint32_t	i;
	uint32_t	j;
	t_sprite	tmp;

	j = 0;
	while (sprites[j].texture)
	{
		i = 0;
		while (sprites[i + 1].texture)
		{
			if (sprites[i].distance == 0 || sprites[i].distance < sprites[i + 1].distance)
			{
				tmp = sprites[i];
				sprites[i] = sprites[i + 1];
				sprites[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}
void	draw_sprites(t_game	*game_data)
{
	int			i;
	// t_sprite	vis_sprites[10];

	// detect_vis_sprites(game_data);
	i = 0;
	while (game_data->sprites[i].texture)
	{
		if (game_data->sprites[i].visible)
		{
			// set_height(game_data, &game_data->sprites[i]);
			// set_width(game_data, &game_data->sprites[i]);
			// sort_sprites(game_data->sprites);
			draw_sprite(game_data, game_data->sprites[i]);
		}
		i++;
	}
}

void	sprites_calculations(t_game	*game_data)
{
	int			i;

	detect_vis_sprites(game_data);
	i = 0;
	while (game_data->sprites[i].texture)
	{
		if (game_data->sprites[i].visible)
		{
			set_height(game_data, &game_data->sprites[i]);
			set_width(game_data, &game_data->sprites[i]);
			sort_sprites(game_data->sprites);
			// draw_sprite(game_data, game_data->sprites[i]);
		}
		i++;
	}
}
