/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:23:43 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/19 18:25:16 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned int	i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str1[i] != str2[i] || str1[i] == 0 || str2[i] == 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
    char str1[] = "";
    char str2[] = "";
    printf("%i\n", ft_strncmp(str1, str2, 1));
    printf("%i", strncmp(str1, str2, 1)); 
}
*/
