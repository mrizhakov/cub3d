/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:05:14 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/20 18:05:21 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/*
int main()
{
    char str1[] = "1111";
    char str2[] = "dsgh12";
    char str3[] = "123k4";

    printf("%i\n", ft_isalpha(str1));
    printf("%i\n", ft_isalpha(str2));
    printf("%i\n", ft_isalpha(str3));
}
*/
