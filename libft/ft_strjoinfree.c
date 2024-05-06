/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:59:29 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/20 11:34:50 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	ssize_t	i;
	ssize_t	j;
	char	*ptr;

	i = -1;
	if (!s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	j = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc((j + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (*s2)
		ptr[i++] = *s2++;
	free(s1);
	ptr[i] = '\0';
	return (ptr);
}
