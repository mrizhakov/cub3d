/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:27:44 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/21 22:44:25 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int closed_maze(t_game game_data)
{
    (void)game_data;
    return(0);
}


// int closed_maze(t_game game_data)
// {
//     int x;
//     int y;

//     x = 0;
//     y = 0;
//     while (y != MAZE_DIMENSION - 1)
//     {
        
//         while (x != MAZE_DIMENSION - 1)
//         {
//             if (game_data.maze.g[y-1][x-1] == 2 || game_data.maze.g[y][x-1] == 2 || game_data.maze.g[y-1][x] == 2
//                 || game_data.maze.g[y+1][x+1] == 2|| game_data.maze.g[y+1][x] == 2 || game_data.maze.g[y][x+1] == 2
//                 || game_data.maze.g[y-1][x+1] == 2 || game_data.maze.g[y+1][x-1] == 2 || game_data.maze.g[y-1][x-1] == 9 
//                 || game_data.maze.g[y][x-1] == 9 || game_data.maze.g[y-1][x] == 9 || game_data.maze.g[y+1][x+1] == 9 
//                 || game_data.maze.g[y+1][x] == 9 || game_data.maze.g[y][x+1] == 9 || game_data.maze.g[y-1][x+1] == 9 
//                 || game_data.maze.g[y+1][x-1] == 9 )
//                 return(0);
//             printf("%i", game_data.maze.g[y][x]);
//             x++;
//         }
//         printf("\n");
//         x = 0;
//         y++;
//     }
//     return(1);
// }
