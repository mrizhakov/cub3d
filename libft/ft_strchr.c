/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:49:08 by eltongid          #+#    #+#             */
/*   Updated: 2023/01/04 15:16:14 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p != (char)c)
	{
		if (!*p++)
			return (NULL);
	}
	return (p);
}
/*
int main(void) 
{
    char string[] = "hello, world!";
    char c = 'l';


    printf("%s\n", ft_strchr(string, c));
    printf("%s\n", strchr(string, c));
    return 0;
}
*/
