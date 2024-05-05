/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:54:27 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/05 19:14:39 by mrizakov         ###   ########.fr       */
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
    return(fill(game_data, size, begin, 'Z'));
}

int		maze_check_closed(t_game *game_data)
{
    int is_closed;
    t_point maze_end;
    t_point maze_start;

    is_closed = 0;
    maze_end.x = MAZE_DIMENSION;
    maze_end.y = MAZE_DIMENSION;
    maze_start.x = 0;
    maze_start.y = 0;
    game_data->maze_closed = flood_fill(game_data, maze_end, maze_start);
    printf("\nin maze check_closed------------> Is_closed is  %i\n", game_data->maze_closed);
    return(0);
}