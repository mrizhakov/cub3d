/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:54:27 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/25 20:30:53 by mrizakov         ###   ########.fr       */
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
    // if (game_data->maze.g[cur.y][cur.x] == 0)
    // {
    //     printf("Maze not closed at location x %i, y %i\n", cur.x, cur.y);
    //     exit(0);
    //     return(0);

    // }
    if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x)
        return(1);
    
    if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| game_data->maze.g[cur.y][cur.x] != to_fill )
	// if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
	// 	|| game_data->maze.g[cur.y][cur.x] != to_fill)
    {
        if (game_data->maze.g[cur.y][cur.x] == '0' || game_data->maze.g[cur.y][cur.x] == 'N' 
            || game_data->maze.g[cur.y][cur.x] == 'E' || game_data->maze.g[cur.y][cur.x] == 'W' 
            || game_data->maze.g[cur.y][cur.x] == 'S')
        // if (game_data->maze.g[cur.y][cur.x] == 0 || game_data->maze.g[cur.y][cur.x] == 3 || game_data->maze.g[cur.y][cur.x] == 4
        //     || game_data->maze.g[cur.y][cur.x] == 5 || game_data->maze.g[cur.y][cur.x] == 6)
        {
            printf("Maze not closed at location x %i, y %i, character %c\n", cur.x, cur.y, game_data->maze.g[cur.y][cur.x]);
            print_maze(game_data);
            exit(0);
            return(0);

        }
        // printf("Fill flood returned 0, position x %i, y %i, size is x %i, y is %i\n", cur.x, cur.y, size.x, size.y);
        // printf("Fill flood returned 0, position x %i, y %i\n", cur.x, cur.y);

        return (1);
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
    printf("Fill flood painting in squares position x %i, y %i\n", cur.x, cur.y);
    

	game_data->maze.g[cur.y][cur.x] = 'X';
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
    // int is_closed;
    
    // is_closed = -1;
	// is_closed = fill(game_data, size, begin, 9);
    // print_maze(game_data);

    return(fill(game_data, size, begin, 'Z'));
}

int		maze_check_closed(t_game *game_data)
{

    int is_closed;
    is_closed = 0;
    t_point maze_end;
    maze_end.x = MAZE_DIMENSION;
    maze_end.y = MAZE_DIMENSION;
    // print_maze(game_data);
    // exit(1);
    game_data->maze_closed = flood_fill(game_data, maze_end, game_data->maze_start);
    // printf("\nin maze check_closed------------> Is_closed is  %i\n", is_closed);
    // print_maze(game_data);

    return(0);
}