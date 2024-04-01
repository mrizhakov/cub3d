/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:53:14 by eltongid          #+#    #+#             */
/*   Updated: 2023/01/04 15:27:31 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*str;
	size_t	len;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!s1 || !str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int main()
{
    char *str = "hello world"; 
    char *s1; 
    s1 = ft_strdup(str);
    printf("%s\n", s1); 
    printf("%s\n", s1); 
}*/
