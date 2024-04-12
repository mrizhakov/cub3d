/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:00:24 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/04/11 21:38:03 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int map_parsing(char *filename)
{
    int fd;
    char *map;
    // map = NULL;
    printf("Parsing map\n");
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening map\n");
        close(fd);
        exit(errno);
    }
    if (fd != -1)
    {
        printf("File : %s \n", filename);
        printf("Map opened\n");
    }
    printf("Logging out map for debugging purposes\n");

    map = get_next_line(fd);
    printf("%s", map);
    free(map);

    while (map != NULL)
    // while (map != NULL || ft_strncmp(map, "(null)", 6) == 0)
    {
        map = get_next_line(fd);
        printf("%s", map);
        free(map);
    }
    close(fd);
    return (0);
}

int	iffile_cub(char *map_file_name)
{
	char	*find_ber;

	find_ber = ft_strrchr(map_file_name, '.');
	if (!find_ber || ft_strncmp(find_ber, ".cub", 5) != 0)
    {
        ft_printf("Error: Not a .cub file.\n");
		return (1);
    }
	return (0);
}

int			is_valid_char(char matrix_val)
{
	if (matrix_val && matrix_val != '1' && matrix_val != '0' && matrix_val != '2' && matrix_val
		!= 'N' && matrix_val != 'S' && matrix_val != 'W' && matrix_val != 'E' && matrix_val
		!= ' ')
		return (1);
	return (0);
}

int		no_of_players(char matrix_val)
{
	int i;

	i = 0;
	if (matrix_val == 'N' || matrix_val == 'S' || matrix_val == 'W' || matrix_val == 'E')
		i++;
	return (i);
}// just one player per map

