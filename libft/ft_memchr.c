/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:26:59 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/18 19:08:38 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*memchr is a function that searches a block of memory for a
specific byte value. 
It takes three arguments: a pointer to the block of memory, 
the byte value to search for, and the number of bytes to search. 
It returns a pointer to the first occurrence of the specified byte 
in the block of memory, or null if the byte is not found.

The  memchr()  function  scans  the  initial n bytes of the memory area
pointed to by s for the first instance of c.  Both c and the  bytes  of
the memory area pointed to by s are interpreted as unsigned char.*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s1;

	s1 = (const unsigned char *)s;
	while (n)
	{
		if (*s1 == (unsigned char)c)
			return ((void *)s1);
		s1++;
		n--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Test data
    char str[] = "Hello, World!";
    char ch = 'o';
    size_t n = strlen(str);

    // Call memchr
    void* result = memchr(str, ch, n);

    // Print result
    if (result)
    {
        printf("Character '%c' found at position %ld\n", ch,result - str);
    }
    else
    {
        printf("Character '%c' not found\n", ch);
    }

    return 0;
}*/
