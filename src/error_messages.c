/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:43:02 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/01 14:43:02 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	memory_error(void)
{
	perror("Error: Failed to allocate memory for game data");
	return (EXIT_FAILURE);
}

int	parsing_error(const char *msg, int fd)
{
	ft_putendl_fd(msg, 2);
	if (fd != -1)
		close(fd);
	return (1);
}
