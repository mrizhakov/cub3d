/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:16:43 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/13 14:16:44 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		load_textures(t_game *game_data)
{
	game_data->textures = malloc(sizeof(t_textures));
	if (!game_data->textures)
		return (1);
    game_data->textures->north = mlx_load_png(game_data->texture_filename[NO]);
    game_data->textures->south = mlx_load_png(game_data->texture_filename[SO]);
    game_data->textures->west = mlx_load_png(game_data->texture_filename[WE]);
	game_data->textures->east = mlx_load_png(game_data->texture_filename[EA]);
	if (!game_data->textures->north || !game_data->textures->east
		|| !game_data->textures->west || !game_data->textures->south)
	{
		free_textures(game_data);
		return (1);
	}
	// game_data->images = malloc(sizeof(t_text_images));
	if (!game_data->images)
		return (1);
	game_data->images->north = mlx_texture_to_image(game_data->mlx, game_data->textures->north);
	game_data->images->south = mlx_texture_to_image(game_data->mlx, game_data->textures->south);
	game_data->images->west = mlx_texture_to_image(game_data->mlx, game_data->textures->west);
	game_data->images->east = mlx_texture_to_image(game_data->mlx, game_data->textures->east);

    return 0;
}
