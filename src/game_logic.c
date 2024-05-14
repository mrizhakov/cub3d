/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:59:45 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/14 17:29:32 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

int prevent_wall_collisions(t_game *game_data, double player_y_check, double player_x_check, int y_map_padding, int x_map_padding)
{
    (void)game_data;
    if (player_x_check >= 0 && player_y_check >= 0 && player_x_check <= WINDOW_WIDTH - 1 && player_y_check <= WINDOW_HEIGHT - 1)
    {
        if (game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == '0'
            || game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 'N'
            || game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 'E'
            || game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 'W'
            || game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 'S')
        {
            game_data->player->y = player_y_check;
            game_data->player->x = player_x_check;
            game_data->player_walk_dir = 0;
            return (0);
        }
    }
    return(1);
}

double   check_angle_overflow(t_game *game_data, double player_angle)
{
    if (player_angle < 0)
        player_angle += 2 * M_PI;
    if (player_angle > (2 * M_PI))
        player_angle -= 2 * M_PI;
    // printf("Player angle is %f\n", player_angle);
    game_data->player_turn_dir = 0;
    return (player_angle);
}

void strafing_movement(t_game *game_data, )
{
    
}




void update_pos(t_game *game_data)
{
    double  player_y_check;
    double  player_x_check;
    double  move_step;

    player_x_check = 0;
    player_y_check = 0;
    game_data->redraw_minimap = 0;
    game_data->player_angle += game_data->player_turn_dir * TURNING_SPEED;
    game_data->player_angle = check_angle_overflow(game_data, game_data->player_angle);
    if (game_data->player_walk_strafe == -1)
    {
            player_x_check += sin(game_data->player_angle) * PLAYER_STEP ;
            player_y_check -= cos(game_data->player_angle) * PLAYER_STEP ;
    }
    else if (game_data->player_walk_strafe == 1)
    {
            player_x_check -= sin(game_data->player_angle) * PLAYER_STEP ;
            player_y_check += cos(game_data->player_angle) * PLAYER_STEP ;
    }
    if (game_data->player_walk_dir)
    {
        move_step = game_data->player_walk_dir * PLAYER_STEP;
        player_x_check += cos(game_data->player_angle) * move_step;
        player_y_check += sin(game_data->player_angle) * move_step;
    }
    if (game_data->player_walk_dir != 0 || game_data->player_walk_strafe != 0)
    {
        prevent_wall_collisions(game_data, game_data->player->y + player_y_check,  game_data->player->x + player_x_check, 0, 0);
        game_data->player_walk_dir = 0;
        game_data->player_walk_strafe = 0;
    }
}
