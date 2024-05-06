/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:16:29 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/23 21:56:56 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	k;

	k = ft_strlen(src);
	j = 0;
	if (size <= 0)
		return (k);
	while ((size - 1) > j && *src)
	{
		*dst++ = *src++;
		j++;
	}
	*dst = '\0';
	return (k);
}
