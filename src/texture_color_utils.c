/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:26:36 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/04 11:34:40 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_tokens(char token_texture[TEX_NO + 1][4],
	char token_color[SUR_NO + 1][2])
{
	{
		ft_strlcpy(token_texture[NO], "NO", 3);
		ft_strlcpy(token_texture[SO], "SO", 3);
		ft_strlcpy(token_texture[WE], "WE", 3);
		ft_strlcpy(token_texture[EA], "EA", 3);
		ft_strlcpy(token_texture[TEX_MUSHR], "MU", 3);
		ft_strlcpy(token_texture[TEX_MUSHR_2], "MU2", 4);
		ft_strlcpy(token_texture[TEX_MUSHR_M], "MUM", 4);
		ft_strlcpy(token_texture[TEX_DOOR_CL], "DO0", 4);
		ft_strlcpy(token_texture[TEX_DOOR_1], "DO1", 4);
		ft_strlcpy(token_texture[TEX_DOOR_OP], "DO2", 4);
		ft_strlcpy(token_texture[TEX_PSY_1], "PS1", 4);
		ft_strlcpy(token_texture[TEX_PSY_2], "PS2", 4);
		ft_strlcpy(token_texture[TEX_PSY_3], "PS3", 4);
		ft_strlcpy(token_texture[TEX_NO], "", 1);
	}
	{
		ft_strlcpy(token_color[F], "F", 2);
		ft_strlcpy(token_color[C], "C", 2);
		ft_strlcpy(token_color[SUR_NO], "", 1);
	}
}
