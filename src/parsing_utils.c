/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:13:32 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/01 15:16:58 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_char(char matrix_val)
{
	char	*set;
	int		i;

	set = "012NEWS Z\n\t";
	i = -1;
	while (set[++i])
		if (matrix_val == set[i])
			return (1);
	return (0);
}

int	is_valid_int(int matrix_val)
{
	if (matrix_val == 1 || matrix_val == 0 || matrix_val == 3)
		return (1);
	else
		return (0);
}

int	ft_istabs(char *line)
{
	if (line[0] >= '\t' && line[0] <= '\r')
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

char	put_sign(char c, char *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i] && tokens[i] != c)
		i++;
	if (i > 7 && i < 10)
		return ('X');
	else if (i <= 7)
		return (tokens[i]);
	else
		return (0);
}

int	check_parse(size_t j, t_game *game_data)
{
	if (j == 0)
		return (0);
	if (maze_check(game_data))
		return (1);
	else
		return (0);
}
