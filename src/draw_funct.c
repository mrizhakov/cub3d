#include "../cub3d.h"

static int32_t draw_rectangle(t_game *game_data, t_float_pixel start, t_float_pixel end)
{
	(void)game_data;
	if (check_pix(start) && check_pix(end))
	{
		while(start.x < end.x)
		{
			drawLine(init_slope_data(start.x, start.y, start.x, end.y, game_data->img), start.color);
			start.x++;
		}
		while(start.x > end.x)
		{
			drawLine(init_slope_data(start.x, start.y, start.x, end.y, game_data->img), start.color);
			start.x--;
		}
		if(start.x == end.x)
		{
			drawLine(init_slope_data(start.x, start.y, start.x, end.y, game_data->img), start.color);
		}
		return(1);
	}
	return(0);
}

void draw_black_background(t_game *game_data)
{
	t_float_pixel black_background;
	t_float_pixel end;

	black_background.y = 0;
	black_background.x = 0;
	black_background.color = game_data->color[C].rgb_color;
	end.x = WINDOW_WIDTH - 1;
	end.y = WINDOW_HEIGHT - 1;
	draw_rectangle(game_data, black_background, end);
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
			drawLine(init_slope_data(start.x, start.y, start.x, start.y + side_len, game_data->img), start.color);
			i++;
			start.x++;
		}
		return(1);
	}
	return(0);
}
