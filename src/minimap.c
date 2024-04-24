/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:54:27 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/24 15:47:16 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"


// typedef struct 	s_point {
// 	int			x;				// x : Width  | x-axis
// 	int			y;				// y : Height | y-axis
// }				t_point;
 
// void	fill(char **tab, t_point size, t_point cur, char to_fill)

// int fill(int **matrix, t_point size, t_point cur, int to_fill)


int fill(t_game *game_data, t_point size, t_point cur, int to_fill)
{
    if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| game_data->maze.g[cur.y][cur.x] != to_fill)
	// if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
	// 	|| game_data->maze.g[cur.y][cur.x] != to_fill)
    {
        return (0);
        // if ((game_data->maze.g[cur.y][cur.x]) == 0)
        // {
        //     game_data->maze_closed = 1;
        //     return (0);
        // }
        // else
        // {
        //     game_data->maze_closed = 0;

        //     return (1);
        // }
    }

	game_data->maze.g[cur.y][cur.x] = 7;
	fill(game_data, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(game_data, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(game_data, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(game_data, size, (t_point){cur.x, cur.y + 1}, to_fill);
    return(1);
}
//run as many times as needed on different parts of the matrix
//returns 0 if it encounters non-closed spaces (spaces bordering with characters 9 or 8)

int	flood_fill(t_game *game_data, t_point size, t_point begin)
{
    int is_closed;
    
    is_closed = -1;
	is_closed = fill(game_data, size, begin, 9);
    return(is_closed);
}

int		maze_check_closed(t_game *game_data)
{

    // int x;
    // int y;
    int is_closed;
    is_closed = 0;
    // t_point begin;
    // t_point size
    is_closed = flood_fill(game_data, game_data->maze_end, game_data->maze_start);


    // x = 0;
    // y = 0;

    // while (y != MAZE_DIMENSION - 1)
    // {
    //     while (x != MAZE_DIMENSION - 1)
    //     {
    //         is_closed = flood_fill(game_data->maze.g, game_data->maze_end, game_data->maze_start);

    //         // is_closed = flood_fill((int **)game_data->maze.g, game_data->maze_end, game_data->maze_start);
    //         // printf("%i", game_data.maze.g[y][x]);
    //         x++;
    //     }
    //     printf("\n");
    //     x = 0;
    //     y++;
    // }
    // printf("\nIs the maze valid? %i\n", game_data->maze.valid_maze);
    // // if (!is_closed)
    printf("\n-------------> Is_closed is  %i\n", is_closed);
    print_maze(game_data);

    return(0);
}




// int fill(int **matrix, t_point size, t_point *cur, int to_fill)
// {
// 	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
// 		|| matrix[cur.y][cur.x] != to_fill)
//     {
//         if ((matrix[cur.y][cur.x]) == 9 || (matrix[cur.y][cur.x] = 2))
//             return (0);
//         else
//             return (1);
//     }

// 	matrix[cur.y][cur.x] = 1;
// 	fill(matrix, size, (t_point*){cur.x - 1, cur.y}, to_fill);
// 	fill(matrix, size, (t_point*){cur.x + 1, cur.y}, to_fill);
// 	fill(matrix, size, (t_point*){cur.x, cur.y - 1}, to_fill);
// 	fill(matrix, size, (t_point*){cur.x, cur.y + 1}, to_fill);
// }
// //run as many times as needed on different parts of the matrix
// //returns 0 if it encounters non-closed spaces (spaces bordering with characters 9 or 8)

// int	flood_fill(int **matrix, t_point *size, t_point *begin)
// {
//     int is_closed;
    
//     is_closed = -1;
// 	is_closed = fill(matrix, size, begin, matrix[begin.y][begin.x]);
//     return(is_closed);
// }

// int		maze_check_not_closed(t_game *game_data)
// {

//     int x;
//     int y;
//     int is_closed;
//     // t_point begin;
//     // t_point size


//     x = 0;
//     y = 0;

//     while (y != MAZE_DIMENSION - 1)
//     {
//         while (x != MAZE_DIMENSION - 1)
//         {
//             is_closed = flood_fill(game_data.maze.g, game_data.maze_end, game_data.maze_start);
//             // printf("%i", game_data.maze.g[y][x]);
//             x++;
//         }
//         printf("\n");
//         x = 0;
//         y++;
//     }
//     printf("\nIs the maze valid? %i\n", game_data.maze.valid_maze);
//     return(0);
// }
