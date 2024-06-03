/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psycodelic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:30:18 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 21:14:44 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_sprite	*use_mushr(t_game *game_data)
{
	int	i;

	i = -1;
	while (game_data->sprites[++i].texture)
	{
		if (game_data->sprites[i].taken)
			return (&game_data->sprites[i]);
	}
	return (NULL);
}

void	psycho_trigger(t_game *game_data)
{
	t_sprite	*mushr;
	int			i;

	i = -1;
	mushr = use_mushr(game_data);
	if (!mushr)
		return ;
	while (game_data->sprites[++i].texture)
		if (mushr == &game_data->sprites[i])
			break ;
	game_data->psycho = i + 1;
	if (mushr)
		game_data->phycho_time = mlx_get_time();
}
