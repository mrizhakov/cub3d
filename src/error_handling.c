/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:01:00 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/05/06 15:47:59 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_read_file(int fd)
{
	ssize_t bytes_read;
	char *buf[FILE_READ_BUFFER];

	bytes_read = read(fd, buf, FILE_READ_BUFFER);
	while (bytes_read)
	{
		if (bytes_read == -1)
		{
			perror("Error reading file\n");
			return (1);
		}
		bytes_read = read(fd, buf, FILE_READ_BUFFER);
	}
	close(fd);
	return (0);
}

int check_file_extension(char *filename, char *file_extension)
{
	size_t	filename_len;
	size_t	extension_len;
	char	*extension;

	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(file_extension);
	if (filename_len < extension_len + 1)
		return (1);
	extension = ft_substr(filename, filename_len - extension_len, extension_len);
	if (!extension)
		return (perror("Error: Failed to allocate memory for game data"), 1);
	if (ft_strncmp(extension, file_extension, extension_len))
		return (free(extension), 1);
	free(extension);
	return (0);
}

int error_handling(int argc, const char *argv[])
{
	int fd_map;

	(void)argv;
	if (argc != 2)
		return(write(1, "usage: ./cub3D <map>.cub\n", 25), 0);
	fd_map = open((char *)argv[1], O_RDONLY);
	if (fd_map == -1)
		return(perror("Error opening file"), 1);
	if (check_file_extension((char *)argv[1], ".cub") || check_read_file(fd_map))
		return(write(2, "Map file is no bueno!\n", 22), close(fd_map), 1);
	return (0);
}
