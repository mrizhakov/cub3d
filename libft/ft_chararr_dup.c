/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:19:56 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/18 16:20:05 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**arrstr_copy(const char **envp)
{
	char		**copy_envp;
	int32_t		len;

	len = 0;
	while (envp[len])
		len++;
	copy_envp = (char **)ft_calloc(sizeof (char *), len + 1);
	len = -1;
	while (envp[++len])
		copy_envp[len] = ft_strdup(envp[len]);
	return (copy_envp);
}
