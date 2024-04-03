/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:08:09 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/18 18:09:04 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int	main()
{
	int a; 

	char str1[] = "string"; 
	//char str2[] = "string with 123435";
	//char str3[] ="0110";
	//char str4[] = " "; 

	a = isdigit(str1);
	printf("%d", a); 
}*/
