/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:23:44 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/11 18:40:24 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../MLX42/include/MLX42/MLX42.h"

// #define WIDTH 512
// #define HEIGHT 512



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
	// ft_print_parsed_map(game_data);
	maze_check_closed(game_data);

	printf("north texture is : %s", game_data->no_texture_filename);

	load_textures(game_data);
	printf("Is map is closed %i\n", game_data->maze_closed);
	mlx_demo(game_data);
	free_on_exit(game_data);
	printf("Exiting\n");

	return (EXIT_SUCCESS);
}
