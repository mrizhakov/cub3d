#include "../cub3d.h"


void	delete_image(mlx_t *mlx, void **img_ptr)
{
	if (*img_ptr)
	{
		mlx_delete_image(mlx, *img_ptr);
		*img_ptr = NULL;
	}
}
