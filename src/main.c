/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:23:44 by mrizakov          #+#    #+#             */
/*   Updated: 2024/04/11 18:10:48 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int main(int argc, const char *argv[])
{
	(void)argv;
	error_handling(argc, argv);
	map_parsing();

	return (EXIT_SUCCESS);
}
