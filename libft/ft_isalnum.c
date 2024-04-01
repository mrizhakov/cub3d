/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:54:25 by eltongid          #+#    #+#             */
/*   Updated: 2023/01/04 15:28:28 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
/*
int main()
{
    char str1[] = "1111";
    char str2[] = "dsgh12";
    char str3[] = "  ";

    printf("%i\n", ft_isalnum(str1));
    printf("%i\n", ft_isalnum(str2));
    printf("%i\n", ft_isalnum(str3));
}*/
