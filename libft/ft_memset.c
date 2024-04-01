/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:10:16 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/18 19:35:09 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = c;
	return (s);
}
/*
int main()
{
    int x;
	x = 'x'; 
    
    char p[] = "hey ho";
    ft_memset(p, x, 3);

    printf("%s\n", p);
}*/
