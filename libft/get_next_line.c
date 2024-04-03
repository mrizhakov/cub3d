/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:50:24 by eltongid          #+#    #+#             */
/*   Updated: 2023/03/22 19:54:26 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buffer_to_stash(int fd, char *buffer, char **stash)
{
	int		i;
	char	*current;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free_stash(stash);
			return (NULL);
		}
		else if (i == 0)
			break ;
		buffer[i] = '\0';
		if (!(*stash))
			*stash = ft_strdup("");
		current = *stash;
		*stash = ft_strjoin(current, buffer);
		free(current);
		current = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*stash);
}

void	free_stash(char **stash)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
}

char	*extract_line(char *line)
{
	size_t	i;
	char	*stash;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	stash = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = buffer_to_stash(fd, buffer, &stash);
	free (buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash = extract_line(line);
	return (line);
}
