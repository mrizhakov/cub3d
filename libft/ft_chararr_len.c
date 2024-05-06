/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chararr_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:16:14 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/18 16:16:23 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_arr_len(char **arr)
{
	ssize_t	i;

	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
