/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:21:09 by ddavlety          #+#    #+#             */
/*   Updated: 2024/05/07 17:05:55 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (!(*little))
		return ((char *)big);
	while (*big && len != 0)
	{
		if (!ft_strncmp(big, little, ft_strlen(little))
			&& len >= ft_strlen(little))
			return ((char *)big);
		big++;
		len--;
	}
	return (0);
}
