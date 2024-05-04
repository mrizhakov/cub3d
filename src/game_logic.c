/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:59:45 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/04 14:10:18 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"



// Prototype code for finding the end of the ray drawn from the player

// game_data->maze.g.y*MINIMAP_SQUARE_SIDE_LEN;
// game_data->maze.g.x*MINIMAP_SQUARE_SIDE_LEN;
// game_data->maze.g.y = 0;
// game_data->maze.g.x = 0;


// int prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check)
// {
//     (void)game_data;
//     printf("game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
//     if (player_x_check >= 0 && player_y_check >= 0 && player_x_check <= WINDOW_WIDTH - 1 && player_y_check <= WINDOW_HEIGHT - 1)
//     {
//         if (game_data->maze.g[(player_y_check ) / MINIMAP_SQUARE_SIDE_LEN][(player_x_check)/ MINIMAP_SQUARE_SIDE_LEN] == 0 
//             || game_data->maze.g[(player_y_check ) / MINIMAP_SQUARE_SIDE_LEN][(player_x_check)/ MINIMAP_SQUARE_SIDE_LEN] == 3)
//         {
//             game_data->player->y = player_y_check;
//             game_data->player->x = player_x_check; 
//             game_data->redraw_minimap = 0;
//             return (0);
//         }
//     }
//     return(1);   
// }



int prevent_wall_collisions(t_game *game_data, double player_y_check, double player_x_check, int y_map_padding, int x_map_padding)
{
    (void)game_data;
    printf("game_data->player->x and y in struct is %f and %f\n", game_data->player->x,  game_data->player->y);
    if (player_x_check >= 0 && player_y_check >= 0 && player_x_check <= WINDOW_WIDTH - 1 && player_y_check <= WINDOW_HEIGHT - 1)
    {
        printf("Trying move to: \n");
        //printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %f\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN]);
        printf("player_y_check is %f\n", player_y_check);
        printf("player_x_check is %f\n", player_x_check);
        printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %f\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
        printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %f\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);

        // if (game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == '0' || game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 3)
        if (game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == '0' 
            || game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 'N'
            || game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 'E'
            || game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 'W'
            || game_data->maze.g[((int)player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][((int)player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 'S')
        {
            //printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %f\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / PLAYER_STEP]);
            printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %f\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
            printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %f\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);
            printf("player_y_check is %f\n", player_y_check);
            printf("player_x_check is %f\n", player_x_check);

            game_data->player->y = player_y_check;
            game_data->player->x = player_x_check;
            game_data->player_walk_dir = 0;

            // game_data->redraw_minimap = 0;
            printf("Valid mode to -> game_data->player->x and y in struct is %f and %f\n", game_data->player->x,  game_data->player->y);
            return (0);
        }
    }
    printf("Invalid move try to ->  player_y_check %f and player_x_check %f \n", player_y_check, player_x_check);
    return(1);   
}

double   check_angle_overflow(t_game *game_data, double player_angle)
{
    // printf("Player angle is %f, player_direction_x is %f, player_direction_y is %f\n", game_data->player_angle, game_data->player_dir_x, game_data->player_dir_y);
    if (player_angle < 0)
        player_angle += 2 * M_PI;
    if (player_angle > (2 * M_PI))
        player_angle -= 2 * M_PI;
    printf("Player angle is %f\n", player_angle);

    // game_data->player_dir_x = cos(game_data->player_angle) * 5;
    // game_data->player_dir_y = sin(game_data->player_angle) * 5;
    //game_data->redraw_minimap = 0;
    game_data->player_turn_dir = 0;
    return (player_angle);
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
    move_step = game_data->player_walk_dir * PLAYER_STEP;
    player_x_check += cos(game_data->player_angle) * move_step;
    player_y_check += sin(game_data->player_angle) * move_step;

    if (game_data->player_walk_dir != 0)
    {
        prevent_wall_collisions(game_data, game_data->player->y + player_y_check,  game_data->player->x + player_x_check, 0, 0);
        game_data->player_walk_dir = 0;
    }
    // if (game_data->player_walk_dir != 0)
    // {
    // game_data->player->x += cos(game_data->player_angle) * move_step;
    // game_data->player->y += sin(game_data->player_angle) * move_step;
    // game_data->player_walk_dir = 0;
    // }
    // game_data->player_walk_dir = 0;

}




// void game_loop()
// {
//     while (!game_over)
//     {
//         // Process input
//         handle_input(get_keyboard_input());

//         // Update game logic
//         update_game_state();

//         // Render the scene
//         render_scene();
//     }
// }

// void handle_input(int key)
// {
//     // Process keyboard input
//     switch (key)
//     {
//         case KEY_UP:
//             move_player_forward();
//             break;
//         case KEY_DOWN:
//             move_player_backward();
//             break;
//         // Other input handling...
//     }
// }

// void render_scene()
// {
//     // Clear screen
// 	clear_screen();

//     // Draw game map
// 	draw_map();

//     // Draw player and other game objects
// 	draw_player();
// 	draw_objects();

//     // Display the rendered scene on the screen
// 	update_screen();
// }

