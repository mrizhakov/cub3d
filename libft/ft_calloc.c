/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:47:10 by eltongid          #+#    #+#             */
/*   Updated: 2022/12/20 19:53:37 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*sets memory to 0, allocates memory for an array of
n elements of size bytes each and returns a pointer 
to the allocated memory */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc(nmemb * size);
	if (!p)
		return (0);
	while (i < nmemb * size)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
/*
int main(void) {
  int n = 10;
  int *array = (int *)ft_calloc(n, sizeof(int));
  if (array == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  // use the array

  free(array); // free the allocated memory when you're done with it
  return 0;
}*/
