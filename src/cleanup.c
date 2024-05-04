#include "../cub3d.h"

// void	cleanup_memory(t_struct *access)
// {
// 	int	i;

// 	i = 0;
// 	if (access->matrix) 
// 	{
// 		while (i < access->height)
// 		{
// 			free(access->matrix[i]);
// 			i++;
// 		}
// 		free(access->matrix);
// 		access->matrix = NULL;
// 	}
// }

// void	cleanup_on_error(t_game *access, int height)
// {
// 	int	i;

// 	i = 0;
// 	while (i < height)
// 	{
// 		free(access->matrix[i]);
// 		i++;
// 	}
// 	free(access->matrix);
// 	access->matrix = NULL;
// 	close(access->fd);
// 	access->fd = -1;
// }

void	free_textures(t_textures *textures)
{
	free(textures->north);
	free(textures->south);
	free(textures->east);
	free(textures->west);
	//free(textures->ceiling);
    //free(textures->floor);
	free(textures);
}

void	delete_image(mlx_t *mlx, void **img_ptr)
{
	if (*img_ptr)
	{
		mlx_delete_image(mlx, *img_ptr);
		*img_ptr = NULL;
	}
}

void	free_textures_images(mlx_t *mlx, t_textures *textures)
{
	if (!textures)
		return ;
	delete_image(mlx, (void **) &textures->north);
	delete_image(mlx, (void **) &textures->south);
	delete_image(mlx, (void **) &textures->west);
	delete_image(mlx, (void **) &textures->east);
	free(textures);
}

void cleanup_game()
{
    // Free allocated memory and resources
    //cleanup_textures();
    //cleanup_map();
    //close_window();
}