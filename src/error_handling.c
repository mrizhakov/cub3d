/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:01:00 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/04/11 18:11:24 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int error_handling(int argc, const char *argv[])
{
    (void)argv;
    if (argc != 2)
    {
        perror("Please provide a map\n");
        return (0);
    }
    return (0);
}
