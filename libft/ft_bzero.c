/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:37:13 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/18 17:46:47 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*bzero is a function that sets all the bytes of a given block of memory to 0. 
It takes two arguments: a pointer to the block of memory and the number 
of bytes to set to 0. 
This function is useful for initializing a block of memory to a 
known value, such as 0, 
without having to manually set each individual byte.*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*arr;
	size_t	i;

	arr = s;
	i = 0;
	while (i < n)
	{
		arr[i] = '\0';
		i++;
	}
}

/*int main(void)
{
    unsigned char arr[10] = "hey ho";
    int i; 
    i = 0; 
    ft_bzero(arr, 3);
    printf("%s\n",arr);
    while (i < 3 || arr[i])
    {
        printf("%c", arr[i]);
        i++;
    }
    return (0);
}*/
