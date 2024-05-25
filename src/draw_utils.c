#include "../cub3d.h"

int32_t check_pix(t_float_pixel pix)
{
	if (pix.x < 0 || pix.y < 0 || pix.x > WINDOW_WIDTH - 1 || pix.y > WINDOW_HEIGHT -1)
	{
		ft_putendl_fd("Warning\nInvalid pixel", 2);
		return (0);
	}
	else
		return(1);
}
