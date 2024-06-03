/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:59:07 by ddavlety          #+#    #+#             */
/*   Updated: 2024/06/03 21:51:25 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_anim_door(void *param)
{
	t_game	*game_data;
	int		i;
	float	anim_time;

	anim_time = ANIM_TIME;
	game_data = (t_game *)param;
	if (mlx_get_time() - game_data->animat_time > anim_time)
	{
		i = 0;
		while (game_data->doors[i].texture)
		{
			if (game_data->doors[i].isopen
				&& game_data->doors[i]. texture < TEX_DOOR_OP)
				game_data->doors[i].texture++;
			else if (!game_data->doors[i].isopen
				&& game_data->doors[i]. texture > TEX_DOOR_CL)
				game_data->doors[i].texture--;
			i++;
		}
		update_pos(game_data);
		game_data->animat_time = mlx_get_time();
	}
}

void	ft_anim_sprite(void *param)
{
	t_game	*game_data;
	int		i;
	float	anim_time;

	anim_time = ANIM_TIME;
	game_data = (t_game *)param;
	if (game_data->psycho)
		anim_time = 0.001;
	if (mlx_get_time() - game_data->animat_time > anim_time)
	{
		i = 0;
		while (game_data->sprites[i].texture)
		{
			if (game_data->sprites[i].texture == TEX_MUSHR)
				game_data->sprites[i].texture = TEX_MUSHR_2;
			else
				game_data->sprites[i].texture = TEX_MUSHR;
			i++;
		}
		update_pos(game_data);
	}
}

void	ft_keyboad_hook(void *param)
{
	t_game	*game_data;

	game_data = param;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game_data->mlx);
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_W))
		game_data->player_walk_dir = 1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_S))
		game_data->player_walk_dir = -1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_A))
		game_data->player_strafe_dir = -1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_D))
		game_data->player_strafe_dir = 1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
		game_data->player_turn_dir = -1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
		game_data->player_turn_dir = 1;
	if (mlx_is_key_down(game_data->mlx, MLX_KEY_E))
		open_door(game_data);
	if (game_data->player_walk_dir != 0 || game_data->player_turn_dir != 0
		|| game_data->player_strafe_dir != 0)
		update_pos(game_data);
}

void	ft_cursor_hook(double xpos, double ypos, void *param)
{
	t_point	cursor;
	t_game	*game_data;

	cursor = ((t_game *)param)->cursor;
	game_data = (t_game *)param;
	if (cursor.x == 0)
	{
		game_data->cursor.x = xpos;
		return ;
	}
	if (cursor.x > xpos)
		game_data->player_turn_dir = -1;
	else if (cursor.x < xpos)
		game_data->player_turn_dir = 1;
	game_data->cursor.x = xpos;
	update_pos(game_data);
	(void)ypos;
}

void	ft_psychodelic(void *param)
{
	t_game	*game_data;

	game_data = (t_game *)param;
	if (mlx_get_time() - game_data->phycho_time > PSYCHO)
	{
		check_colors_ok(game_data);
		game_data->psycho = false;
		game_data->dist_proj_plane = (WINDOW_WIDTH / 2)
			/ tan(game_data->fov_angle / 2);
	}
	psycho_trigger(game_data);
}
