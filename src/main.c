/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:23:44 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/15 20:17:13 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int32_t	main(int argc, const char *argv[])
{
	t_game *game_data;

	game_data = (t_game *)ft_calloc(sizeof(t_game), 1);
	if (!game_data)
		return (perror("Error: Failed to allocate memory for game data"), EXIT_FAILURE);
	if (error_handling(argc, argv) || initialise_game(game_data))
		return (free_on_exit(game_data), 1);
	if (map_parsing((char *)argv[1], game_data))
		return (free_on_exit(game_data), 1);

	// printf("north texture is : %s", game_data->texture_filename[NO]);
	if (maze_check_closed(game_data))
		return(free_on_exit(game_data), 1);

	if (load_textures(game_data))
		return(free_on_exit(game_data), 1);
	mlx_run(game_data);
	free_on_exit(game_data);
	printf("Exiting\n");
	return (EXIT_SUCCESS);
}
