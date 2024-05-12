/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:55:17 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/12 15:27:24 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Bug-testing function for map parsing

void ft_print_parsed_map(t_game *game_data)
{
	printf("game_data.no_texture_filename contains %s\n", game_data->texture_filename[NO]);
	printf("game_data.so_texture_filename contains %s\n", game_data->texture_filename[SO]);
	printf("game_data.we_texture_filename contains %s\n", game_data->texture_filename[WE]);
	printf("game_data.ea_texture_filename contains %s\n", game_data->texture_filename[EA]);
	// printf("Are all textures present? %s\n", game_data->all_textures_ok ? "true" : "false");
	// printf("game_data->all_textures_ok contains %i\n", game_data->all_textures_ok);

	printf("parse_color game_data->floor.color[0] contains %i\n", game_data->color[F].color[0]);
    printf("parse_color game_data->floor.color[1] contains %i\n", game_data->color[F].color[1]);
    printf("parse_color game_data->floor.color[2] contains %i\n", game_data->color[F].color[2]);
    printf("Is floor valid? parse_color game_data->floor.valid_rgb contains %i\n", game_data->color[F].valid_rgb);

	printf("parse_color game_data->ceiling.color[0] contains %i\n", game_data->color[C].color[0]);
    printf("parse_color game_data->ceiling.color[1] contains %i\n", game_data->color[C].color[1]);
    printf("parse_color game_data->ceiling.color[2] contains %i\n", game_data->color[C].color[2]);
    printf("Is ceiling valid? parse_color game_data->ceiling.valid_rgb contains %i\n", game_data->color[C].valid_rgb);
	print_maze(game_data);
}
