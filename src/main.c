/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:23:44 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/21 16:59:46 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../MLX42/include/MLX42/MLX42.h"

// #define WIDTH 512
// #define HEIGHT 512

int32_t main(int argc, const char *argv[])
{
	t_game *game_data;
	game_data = malloc(sizeof(t_game));

    if (game_data == NULL)
    {
        perror("Error: Failed to allocate memory for game data");
        return EXIT_FAILURE;
    }	
	error_handling(argc, argv);
	initialise_game(game_data);
	map_parsing((char *)argv[1], game_data);
	ft_print_parsed_map(game_data);
	

	mlx_demo(game_data);
	free_on_exit(game_data);
	printf("Exiting\n");
	
	return (EXIT_SUCCESS);
}
