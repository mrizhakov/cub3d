/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizhakov <mrizhakov@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:01:00 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/03/26 18:35:36 by mrizhakov        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void error_handling(int argc)
{
    if (argc != 2)
    {
        perror("Please provide a map\n");
        exit(1);
    }
}
