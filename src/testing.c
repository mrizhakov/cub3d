/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:55:17 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/20 14:00:39 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void ft_print_parsed_map(t_game *game_data)
{
	printf("game_data.no_texture_filename contains %s\n", game_data->no_texture_filename);
	printf("game_data.so_texture_filename contains %s\n", game_data->so_texture_filename);
	printf("game_data.we_texture_filename contains %s\n", game_data->we_texture_filename);
	printf("game_data.ea_texture_filename contains %s\n", game_data->ea_texture_filename);
	printf("Are all textures present? %s\n", game_data->all_textures_ok ? "true" : "false");
	printf("game_data->all_textures_ok contains %i\n", game_data->all_textures_ok);

	printf("parse_color game_data->floor.color[0] contains %i\n", game_data->floor.color[0]);
    printf("parse_color game_data->floor.color[1] contains %i\n", game_data->floor.color[1]);
    printf("parse_color game_data->floor.color[2] contains %i\n", game_data->floor.color[2]);
    printf("Is floor valid? parse_color game_data->floor.valid_rgb contains %i\n", game_data->floor.valid_rgb);

	printf("parse_color game_data->ceiling.color[0] contains %i\n", game_data->ceiling.color[0]);
    printf("parse_color game_data->ceiling.color[1] contains %i\n", game_data->ceiling.color[1]);
    printf("parse_color game_data->ceiling.color[2] contains %i\n", game_data->ceiling.color[2]);
    printf("Is ceiling valid? parse_color game_data->ceiling.valid_rgb contains %i\n", game_data->ceiling.valid_rgb);
	print_maze(game_data);
    
}




// void	ft_put_line(t_main *v)
// {
// 	if (v->old_x < v->new_x)
// 		v->sx = 1;
// 	else
// 		v->sx = -1;
// 	if (v->old_y < v->new_y)
// 		v->sy = 1;
// 	else
// 		v->sy = -1;
// 	v->err = v->dx + v->dy;
// 	ft_put_line_loop(v);
// }

