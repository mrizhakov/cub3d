/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intarrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:02:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:48:36 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_intarrdup(int *arr)
{
	int		*new_arr;
	ssize_t	i;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (int *)ft_calloc(sizeof(int), i + 1);
	i = -1;
	while (arr[++i])
		new_arr[i] = arr[i];
	return (new_arr);
}
