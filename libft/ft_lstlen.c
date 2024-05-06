/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:26:51 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/15 10:26:59 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstlen(t_list **list)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	if (!*list)
		return (i);
	tmp = *list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
