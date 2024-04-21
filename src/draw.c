/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:44:08 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/21 16:11:52 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int32_t check_pix(t_pixel pix)
{
    if (pix.x < 0 || pix.y < 0 || pix.x > WINDOW_WIDTH || pix.y > WINDOW_HEIGHT)
    {
        perror("Invalid pixel");
        return (0);
    }
    else
        return(1);
}

int32_t draw_line(t_game *game_data, t_pixel start, t_pixel end)
{
    (void)game_data;
    if (check_pix(start) && check_pix(end))
    {
        if (start.x == end.x)
            draw_v_line(game_data, start, end);
        if (start.y == end.y)
            draw_h_line(game_data, start, end);
        else
        {
            drawLine(start.x, start.y, end.x, end.y, start.color);
        }
        return (1);
    }
    return(0);
}

void draw_black_background(t_game *game_data)
{
    t_pixel black_background;
    t_pixel end;

    black_background.y = 0;
    black_background.x = 0;
    black_background.color = 0x000000FF;
    end.x = WINDOW_WIDTH - 1;
    end.y = WINDOW_HEIGHT - 1;
    draw_rectangle(game_data, black_background, end);
}

int32_t draw_rectangle(t_game *game_data, t_pixel start, t_pixel end)
{
    (void)game_data;
    if (check_pix(start) && check_pix(end))
    {
        while(start.x < end.x)
        {
            drawLine(start.x, start.y, start.x, end.y, start.color);
            start.x++;
        }
        while(start.x > end.x)
        {
            drawLine(start.x, start.y, start.x, end.y, start.color);
            start.x--;
        }
        if(start.x == end.x)
            drawLine(start.x, start.y, start.x, end.y, start.color);
        return(1);
    }
    return(0);
}

int32_t draw_square(t_game *game_data, t_pixel start, unsigned int side_len)
{
    unsigned int i;
    
    i = 0;
    (void)game_data;
    if (check_pix(start))
    {
        while (i != side_len)
        {
            drawLine(start.x, start.y, start.x, start.y + side_len, start.color);
            i++;
            start.x++;
        }
        return(1);
    }
    return(0);
}


int32_t draw_grid(t_game *game_data, t_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    t_pixel origin;
    origin = start;
    int border;
    border = 1;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            drawLine(start.x, start.y, start.x + side_len, start.y, start.color);
            drawLine(start.x, start.y, start.x, start.y + side_len, start.color);
            start.x += side_len;
            x++;
        }
        x = 0;
        start.x = (side_len + border) * x;
        start.y += side_len + border *2;
    }
    return(1);
}

int32_t draw_minimap(t_game *game_data, t_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    t_pixel origin;
    origin = start;
    t_pixel player;
    player.color = 0xFF00FFFF;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            if (is_valid_int(game_data->maze.g[y][x]))
            {
                drawLine(start.x, start.y, start.x + side_len, start.y, start.color);
                drawLine(start.x, start.y, start.x , start.y + side_len, start.color);
            }
            if (game_data->maze.g[y][x] == 1)
                draw_square(game_data, start, side_len);
            if (game_data->maze.g[y][x] == 3)
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


int32_t draw_minimap_with_border(t_game *game_data, t_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    t_pixel origin;
    origin = start;

    t_pixel player;
    player.color = 0xFF00FFFF;
    int border;
    border = 1;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            if (is_valid_int(game_data->maze.g[y][x]))
            {
                drawLine(start.x, start.y, start.x + side_len, start.y, start.color);
                drawLine(start.x, start.y, start.x , start.y + side_len, start.color);
            }
            if (game_data->maze.g[y][x] == 1)
                draw_square(game_data, start, side_len);
            if (game_data->maze.g[y][x] == 3)
            {
                player.x = start.x;
                player.y = start.y;
                draw_square(game_data, player, side_len);
            }
            start.x += side_len + border;
            x++;
        }
        x = 0;
        start.x = origin.x + side_len * x;
        start.y += side_len + border *2;
        y++;
    }
    return(1);
}

int32_t draw_player(t_game *game_data, t_pixel *player, unsigned int side_len)
{
    (void)player;
    draw_square(game_data, *game_data->player, side_len);
    return(1);
}

int32_t	conv_x(int32_t x, int32_t y, double angle)
{
	return (x * cos(angle) - y * sin(angle));

	// return ((x - y) * cos(0.523599));
}

int32_t	conv_y(int32_t x, int32_t y, double angle)
{
	return (x * sin(angle) + y * cos(angle));
	// return ((x + y) * sin(0.523599));

	
}

t_pixel rotatePoint(t_pixel p, t_pixel center, double angle) {
    t_pixel rotated;
    rotated.x = center.x + (p.x - center.x) * cos(angle) - (p.y - center.y) * sin(angle);
    rotated.y = center.y + (p.x - center.x) * sin(angle) + (p.y - center.y) * cos(angle);
    return rotated;
}