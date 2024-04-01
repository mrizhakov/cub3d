/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizhakov <mrizhakov@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:01:00 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/03/26 17:12:37 by mrizhakov        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int error_handling(int argc, const char *argv[])
{
    if (argc != 2)
    {
        perror("Please provide a map\n");
        return (0);
    }
    return (0);
}
