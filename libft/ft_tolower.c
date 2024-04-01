/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:51:00 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/19 18:52:42 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c += 32);
	else
		return (c);
}
/*
int main(void) 
{
  char c = 'A';
  printf("%c\n", ft_tolower(c));
  return 0;
}*/
