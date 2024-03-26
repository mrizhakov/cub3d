/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizhakov <mrizhakov@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:09 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/03/26 18:37:01 by mrizhakov        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3d_H
#define cub3d_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "cub3d.h"
#include "errno.h"

// #include "libft/libft.h"

#define WIDTH 1280
#define HEIGHT 1024

void error_handling(int argc);
int map_parsing(int argc, const char *map);
// int close_fds(int map_fd);

#endif // cub3d_H
