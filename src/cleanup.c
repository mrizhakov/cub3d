/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:53:12 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/16 20:38:14 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	delete_image(mlx_t *mlx, void **img_ptr)
{
	if (*img_ptr)
	{
		mlx_delete_image(mlx, *img_ptr);
		*img_ptr = NULL;
	}
}

void	free_textures_images(mlx_t *mlx, mlx_texture_t *textures[4])
{
	if (!textures)
		return ;
	delete_image(mlx, (void **) &textures[NO]);
	delete_image(mlx, (void **) &textures[SO]);
	delete_image(mlx, (void **) &textures[WE]);
	delete_image(mlx, (void **) &textures[EA]);
	// free(textures);
}
