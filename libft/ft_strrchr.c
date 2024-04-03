/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:36:05 by eltongid          #+#    #+#             */
/*   Updated: 2023/01/04 15:41:12 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char )c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
/*
int main(void) 
{
    char string[] = "hello, world!";
    char c = 'l';


    printf("%s\n", ft_strrchr(string, c));
    printf("%s\n", strrchr(string, c));
    return 0;
}*/
