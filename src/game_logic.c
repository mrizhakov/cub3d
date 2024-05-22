#include "../cub3d.h"

int prevent_wall_collisions(t_game *game_data, double player_y_check, double player_x_check, int y_map_padding, int x_map_padding)
{
    (void)game_data;
    if (player_x_check >= 0 && player_y_check >= 0
        && player_x_check <= game_data->texture_width * (MAZE_DIMENSION - 1)
        && player_y_check <= game_data->texture_width * (MAZE_DIMENSION - 1))
    {
        // printf("Entered outside loop\n");
        if (game_data->maze.g[((int)player_y_check + y_map_padding) / game_data->texture_width][((int)player_x_check + x_map_padding)/ game_data->texture_width] != '1')
        // if (game_data->maze.g[((int)player_y_check + y_map_padding) / game_data->texture_width][((int)player_x_check + x_map_padding)/ game_data->texture_width] == '0'
        //     || game_data->maze.g[((int)player_y_check + y_map_padding) / game_data->texture_width][((int)player_x_check + x_map_padding)/ game_data->texture_width] == 'N'
        //     || game_data->maze.g[((int)player_y_check + y_map_padding) / game_data->texture_width][((int)player_x_check + x_map_padding)/ game_data->texture_width] == 'E'
        //     || game_data->maze.g[((int)player_y_check + y_map_padding) / game_data->texture_width][((int)player_x_check + x_map_padding)/ game_data->texture_width] == 'W'
        //     || game_data->maze.g[((int)player_y_check + y_map_padding) / game_data->texture_width][((int)player_x_check + x_map_padding)/ game_data->texture_width] == 'S')
        {
            // printf("Succesful move to pos x %f, y %f\n", player_x_check, player_y_check);

            game_data->player->y = player_y_check;
            game_data->player->x = player_x_check;
            game_data->player_walk_dir = 0;
            return (0);
        }
    }
    // printf("Unsuccesful move to pos x %f, y %f\n", player_x_check, player_y_check);

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

// void strafing_movement(t_game *game_data, )
// {

// }

// Function too long, thinking how to split it without adding vars to the struct
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
    if (game_data->player_strafe_dir == -1)
    {
        player_x_check += sin(game_data->player_angle) * PLAYER_STEP ;
        player_y_check -= cos(game_data->player_angle) * PLAYER_STEP ;
    }
    else if (game_data->player_strafe_dir == 1)
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
    if (game_data->player_walk_dir != 0 || game_data->player_strafe_dir != 0)
    {
        // printf("Attempting move to pos x %f, y %f\n", game_data->player->x + player_x_check, game_data->player->y + player_y_check);

        prevent_wall_collisions(game_data, game_data->player->y + player_y_check,  game_data->player->x + player_x_check, 240, 240);
        game_data->player_walk_dir = 0;
        game_data->player_strafe_dir = 0;
    }
	sprites_calculations(game_data);
}
