#include "../cub3d.h"

int32_t check_pix(t_float_pixel pix)
{
    if (pix.x < 0 || pix.y < 0 || pix.x > WINDOW_WIDTH - 1 || pix.y > WINDOW_HEIGHT -1)
    {
        ft_putendl_fd("Invalid pixel", 2);
        return (0);
    }
    else
        return(1);
}

int32_t draw_line(t_game *game_data, t_float_pixel start, t_float_pixel end)
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
            drawLine(init_slope_data(start.x, start.y, end.x, end.y), start.color);
        }
        return (1);
    }
    return(0);
}

void draw_black_background(t_game *game_data)
{
    t_float_pixel black_background;
    t_float_pixel end;

    black_background.y = 0;
    black_background.x = 0;
    black_background.color = 0x000000FF;
    end.x = WINDOW_WIDTH - 1;
    end.y = WINDOW_HEIGHT - 1;
    draw_rectangle(game_data, black_background, end);
}

int32_t draw_rectangle(t_game *game_data, t_float_pixel start, t_float_pixel end)
{
    (void)game_data;
    if (check_pix(start) && check_pix(end))
    {
        while(start.x < end.x)
        {
            drawLine(init_slope_data(start.x, start.y, start.x, end.y), start.color);
            start.x++;
        }
        while(start.x > end.x)
        {
            drawLine(init_slope_data(start.x, start.y, start.x, end.y), start.color);
            start.x--;
        }
        if(start.x == end.x)
        {
            drawLine(init_slope_data(start.x, start.y, start.x, end.y), start.color);
        }
        return(1);
    }
    return(0);
}

int32_t draw_square(t_game *game_data, t_float_pixel start, unsigned int side_len)
{
    unsigned int i;

    i = 0;
    (void)game_data;
    if (check_pix(start))
    {
        while (i != side_len)
        {
            drawLine(init_slope_data(start.x, start.y, start.x, start.y + side_len), start.color);
            i++;
            start.x++;
        }
        return(1);
    }
    return(0);
}

int32_t draw_grid(t_game *game_data, t_float_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    // t_float_pixel origin;
    // origin = start;
    int border;
    border = 1;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            drawLine(init_slope_data(start.x, start.y, start.x + side_len, start.y), start.color);
            drawLine(init_slope_data(start.x, start.y, start.x, start.y + side_len), start.color);
            start.x += side_len;
            x++;
        }
        x = 0;
        start.x = (side_len + border) * x;
        start.y += side_len + border *2;
    }
    return(1);
}

int32_t draw_minimap(t_game *game_data, t_float_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    t_float_pixel origin;
    origin = start;
    t_float_pixel player;
    player.color = 0xFF00FFFF;
	t_float_pixel mushroom;
	mushroom.color = 0xFFFF00FF;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            if (is_valid_char(game_data->maze.g[y][x]))
            {
                drawLine(init_slope_data(start.x, start.y, start.x + side_len - 1, start.y), start.color);
                drawLine(init_slope_data(start.x, start.y, start.x , start.y + side_len), start.color);
            }
            if (game_data->maze.g[y][x] == '1')
                draw_square(game_data, start, side_len);
            if (game_data->maze.g[y][x] == 'N' || game_data->maze.g[y][x] == 'E' || game_data->maze.g[y][x] == 'W' || game_data->maze.g[y][x] == 'S')
            {
                player.x = start.x;
                player.y = start.y;
                // draw_square(game_data, player, side_len);
            }
			if (game_data->maze.g[y][x] == 'M')
			{
				mushroom.x = start.x;
				mushroom.y = start.y;
				// draw_square(game_data, mushroom, side_len);
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

int32_t draw_minimap_with_border(t_game *game_data, t_float_pixel start, unsigned int side_len)
{
    (void)game_data;
    int x;
    int y;

    x = 0;
    y = 0;
    t_float_pixel origin;
    origin = start;

    t_float_pixel player;
    player.color = 0xFF00FFFF;
    int border;
    border = 1;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            if (is_valid_int(game_data->maze.g[y][x]))
            {
                drawLine(init_slope_data(start.x, start.y, start.x + side_len, start.y), start.color);
                drawLine(init_slope_data(start.x, start.y, start.x , start.y + side_len), start.color);
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

int32_t draw_player(t_game *game_data, t_float_pixel *player, unsigned int side_len)
{
    (void)player;
    t_float_pixel player_square;

    player_square.x = (game_data->player->x / game_data->texture_width * MINIMAP_SQUARE_SIDE_LEN) - 1;
    player_square.y = (game_data->player->y / game_data->texture_width * MINIMAP_SQUARE_SIDE_LEN) - 1;
    player_square.color = game_data->player->color;
    draw_square(game_data, player_square, side_len);
    return(1);
}

int32_t	conv_x(int32_t x, int32_t y, float angle)
{
	return (x * cos(angle) - y * sin(angle));
}

int32_t	conv_y(int32_t x, int32_t y, float angle)
{
	return (x * sin(angle) + y * cos(angle));
}

t_float_pixel rotatePoint(t_float_pixel p, t_float_pixel center, float angle) {
    t_float_pixel rotated;
    rotated.x = center.x + (p.x - center.x) * cos(angle) - (p.y - center.y) * sin(angle);
    rotated.y = center.y + (p.x - center.x) * sin(angle) + (p.y - center.y) * cos(angle);
    return rotated;
}

int32_t draw_map_sprite(t_game *game_data, t_float_pixel *sprite, unsigned int side_len)
{
    (void)sprite;
    t_float_pixel sprite_square;
	size_t	i;

	i = 0;
	while (game_data->sprites[i].texture)
	{
		sprite_square.x = (game_data->sprites[i].x / game_data->texture_width * MINIMAP_SQUARE_SIDE_LEN) - 1;
		sprite_square.y = (game_data->sprites[i].y / game_data->texture_width * MINIMAP_SQUARE_SIDE_LEN) - 1;
		if (game_data->sprites[i].visible)
			sprite_square.color = 0xFFFF00FF;
		else
			sprite_square.color = 0x00FFFFFF;
		draw_square(game_data, sprite_square, side_len);
		i++;
	}
	return(0);
}
