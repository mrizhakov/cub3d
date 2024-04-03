/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:12:53 by eltongid          #+#    #+#             */
/*   Updated: 2023/01/04 15:36:11 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*psrc;
	char	*pdest;
	size_t	i;

	psrc = (char *)src;
	pdest = (char *)dest;
	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*(pdest + i) = *(psrc + i);
		i++;
	}
	return (dest);
}
/*
int main()
{
    
    char psrc[] = "uur ur";
    char pdest[] = "xxxxxxx";

    ft_memcpy(pdest, psrc, 5);

    printf("%s\n", pdest);
}*/
