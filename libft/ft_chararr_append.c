/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chararr_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:18:09 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/15 16:50:14 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**append_arr_str(char **arr, char *str)
{
	char	**new_arr;
	ssize_t	i;

	i = -1;
	new_arr = (char **)ft_calloc(sizeof(char *), ft_arr_len(arr) + 2);
	while (arr[++i])
		new_arr[i] = arr[i];
	new_arr[i++] = str;
	new_arr[i] = NULL;
	free(arr);
	return (new_arr);
}
