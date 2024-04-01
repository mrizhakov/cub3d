/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:25:31 by eltongid          #+#    #+#             */
/*   Updated: 2023/01/04 15:37:45 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && (i < len))
	{
		if (big[i] == little[j])
		{
			while ((big[i + j] == little[j] || little[j] == '\0')
				&& (i + j) <= len)
			{
				if (!little[j])
					return ((char *) &big[i]);
				j++;
			}	
		}
		j = 0;
		i++;
	}
	return (0);
}
/*
int main()
{
    char big[] = "there will be more time";
    char little[] = "more";
    char *more = ft_strnstr(big, little, 30);
    printf("more: %s\n", more );
}*/
