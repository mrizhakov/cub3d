/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:10:56 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/18 18:10:59 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int main()
{
    char str1[] = "0000";
    char str2[] = "dsg h12";
    char str3[] = " $^#$%%^*";

    printf("%i\n", ft_isprint(str1));
    printf("%i\n", ft_isprint(str2));
    printf("%i\n", ft_isprint(str3));
}
*/
