/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:32:51 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/18 17:36:49 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(sign * res));
}
/*
int main()
{
    printf("ft_atoi: %d\n", ft_atoi("   ---+---+123,4b567"));
    printf("atoi: %d\n", atoi("   ---+---+123,4b567"));
    printf("ft_atoi: %d\n", ft_atoi("  -123,4b567"));
    printf("atoi: %d\n", atoi("  -123,4b567"));
}*/
