/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:54:27 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/29 01:25:06 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"


int32_t draw_minimap_ff(t_game *game_data, t_double_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    t_double_pixel origin;
    origin = start;
    t_double_pixel player;
    player.color = 0xFF00FFFF;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            if (is_valid_char(game_data->maze.g[y][x]))
            {
                drawLine(start.x, start.y, start.x + side_len - 1, start.y, start.color);
                drawLine(start.x, start.y, start.x , start.y + side_len, start.color);
            }
            if (game_data->maze.g[y][x] == '1')
                draw_square(game_data, start, side_len);
            if (game_data->maze.g[y][x] == 'N' || game_data->maze.g[y][x] == 'E' || game_data->maze.g[y][x] == 'W' || game_data->maze.g[y][x] == 'S')
            {
                player.x = start.x;
                player.y = start.y;
                draw_square(game_data, player, side_len);
            }
            start.x += side_len;
            x++;
        }
        x = 0;
        start.x = origin.x + side_len * x;
        start.y += side_len;
        y++;
    }
    return(1);
}


// void sleep_for_0_3_seconds() {
//     struct timespec ts;
//     ts.tv_sec = 0;
//     ts.tv_nsec = 300000000; // 0.3 seconds in nanoseconds

//     nanosleep(&ts, NULL);
// }

// void    minimap_check_visualization(t_game *game_data)
// {
//     uint32_t color = ft_double_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
//     t_double_pixel h_start;
//     h_start.y = 1;
//     h_start.x = 1;
//     h_start.color = color;
//     draw_black_background(game_data);
//     draw_minimap_ff(game_data, h_start, MINIMAP_SQUARE_SIDE_LEN);
//     // Suspend execution for 0.1 second
//     // sleep_for_0_3_seconds();
//     // usleep(microseconds);    
// }



int fill(t_game *game_data, t_point size, t_point cur, int to_fill)
{
        
    if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x)
        return(1);
    if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| game_data->maze.g[cur.y][cur.x] != to_fill )
    {
        if (game_data->maze.g[cur.y][cur.x] == '0' || game_data->maze.g[cur.y][cur.x] == 'N' 
            || game_data->maze.g[cur.y][cur.x] == 'E' || game_data->maze.g[cur.y][cur.x] == 'W' 
            || game_data->maze.g[cur.y][cur.x] == 'S')
        {
            printf("Maze not closed at location x %i, y %i, character %c\n", cur.x, cur.y, game_data->maze.g[cur.y][cur.x]);
            return(0);
        }
        return (1);
        
    }
    // printf("Fill flood painting in squares position x %i, y %i\n", cur.x, cur.y);
    

	game_data->maze.g[cur.y][cur.x] = 'X';
    // minimap_check_visualization(game_data);
    
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
    game_data->maze_closed = flood_fill(game_data, maze_end, game_data->maze_start);
    printf("\nin maze check_closed------------> Is_closed is  %i\n", game_data->maze_closed);
    return(0);
}