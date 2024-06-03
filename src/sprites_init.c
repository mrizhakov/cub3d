/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:46:59 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 21:46:10 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	calcul_angle_sprite(float p_angle,
		t_sprite *sprite, t_float_pixel *player)
{
	float	angle_sprite;

	angle_sprite = p_angle
		- atan2(sprite->y - player->y, sprite->x - player->x);
	if (angle_sprite > M_PI)
		angle_sprite -= 2 * M_PI;
	if (angle_sprite < -M_PI)
		angle_sprite += 2 * M_PI;
	angle_sprite = fabs(angle_sprite);
	return (angle_sprite);
}

int	init_sprites(t_game *game_data, char t, int x, int y)
{
	int			i;

	i = 0;
	while (game_data->sprites[i].texture)
		i++;
	if (i >= 10)
		return (1);
	game_data->sprites[i].x = x * game_data->texture_width
		+ game_data->texture_width / 2;
	game_data->sprites[i].y = y * game_data->texture_width
		+ game_data->texture_width / 2;
	game_data->sprites[i].map_x = x;
	game_data->sprites[i].map_y = y;
	game_data->sprites[i].index = i;
	if (t == 'M')
		game_data->sprites[i].texture = TEX_MUSHR;
	return (0);
}
