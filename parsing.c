/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizhakov <mrizhakov@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:00:24 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/03/26 18:36:47 by mrizhakov        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_parsing(int argc, const char *map)
{
    int map_fd;
    error_handling(argc);
    map_fd = open(map, O_RDONLY);
    if (map_fd == -1)
    {
        perror("Error opening map\n");
        close(map_fd);
        exit(errno);
    }
    printf("Parsing map\n");
    return (0);
}