/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:17:05 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/01 15:17:06 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_textures(t_game *game_data)
{
	int	i;

	i = 0;
	while (i < TEX_NO)
	{
		game_data->textures[i] = mlx_load_png(game_data->texture_filename[i]);
		i++;
	}
	game_data->icon = mlx_load_png(ICON);
	if (!game_data->icon)
		ft_putendl_fd("Warning\nIcon is not set", 2);
	while (--i >= 0)
	{
		if (!game_data->textures[i])
			return (free_textures(game_data), 1);
	}
	return (0);
}

int	check_texture(const char *texture, int texture_count)
{
	if (texture && texture_count == 1)
		return (1);
	else
		return (0);
}

int	check_textures(t_game *game_data)
{
	int	i;
	int	texture;

	texture = 0;
	while (texture < TEX_NO)
	{
		i = check_texture(game_data->texture_filename[texture],
				game_data->texture_count[texture]);
		if (i == 0)
		{
			game_data->all_textures_ok = i;
			return (i);
		}
		texture++;
	}
	game_data->all_textures_ok = i;
	return (i);
}
