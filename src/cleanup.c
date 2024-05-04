/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:53:12 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/04 17:53:19 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

}