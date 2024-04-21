
#include "../cub3d.h"


// int prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check)
// {
//     (void)game_data;
//     printf("game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
//     if (player_x_check >= 0 && player_y_check >= 0 && player_x_check <= WINDOW_WIDTH - 1 && player_y_check <= WINDOW_HEIGHT - 1)
//     {
//         printf("Trying move to: \n");
//         printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %i\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN]);
//         printf("player_y_check is %i\n", player_y_check);
//         printf("player_x_check is %i\n", player_x_check);


//         printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
//         printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);

//         // if (game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 0 || game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 3)
//         if (game_data->maze.g[(player_y_check - MAP_PADDING) / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] != 0 
//             || game_data->maze.g[(player_y_check + MAP_PADDING) / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] != 3
//             || game_data->maze.g[(player_y_check - MAP_PADDING) / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] != 0
//             || game_data->maze.g[(player_y_check + MAP_PADDING) / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] != 3)
//         {
//             printf("Invalid move try to ->  player_y_check %i and player_x_check %i \n", player_y_check, player_x_check);
//             return (1);
//         }
//             else
//         {
//             printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %i\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / PLAYER_STEP]);
//             printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
//             printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);
//             printf("player_y_check is %i\n", player_y_check);
//             printf("player_x_check is %i\n", player_x_check);

//             game_data->player->y = player_y_check;
//             game_data->player->x = player_x_check; 
//             printf("Valid mode to -> game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
//             return (0);
//         }
        
//         //     //player_x_check = 25; //in pixels
//         //     //player_y_check = 15; //in pixels
//         //     //game_data->player_init_loc[0] = 1;// 2nd row this is y
//         //     //game_data->player_init_loc[1] = 2;// 3rd pos from left this x
//         //     //
//         // }


//     }
//     printf("Invalid move try to ->  player_y_check %i and player_x_check %i \n", player_y_check, player_x_check);

//     return(1);   
// }





int prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check, int y_map_padding, int x_map_padding)
{
    (void)game_data;
    printf("game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
    if (player_x_check >= 0 && player_y_check >= 0 && player_x_check <= WINDOW_WIDTH - 1 && player_y_check <= WINDOW_HEIGHT - 1)
    {
        printf("Trying move to: \n");
        printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %i\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN]);
        printf("player_y_check is %i\n", player_y_check);
        printf("player_x_check is %i\n", player_x_check);
        printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
        printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);

        // if (game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 0 || game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 3)
        if (game_data->maze.g[(player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][(player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 0 
            || game_data->maze.g[(player_y_check + y_map_padding) / MINIMAP_SQUARE_SIDE_LEN][(player_x_check + x_map_padding)/ MINIMAP_SQUARE_SIDE_LEN] == 3)
        {
            printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %i\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / PLAYER_STEP]);
            printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
            printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);
            printf("player_y_check is %i\n", player_y_check);
            printf("player_x_check is %i\n", player_x_check);

            game_data->player->y = player_y_check;
            game_data->player->x = player_x_check; 
            printf("Valid mode to -> game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
            return (0);
        }
    }
    printf("Invalid move try to ->  player_y_check %i and player_x_check %i \n", player_y_check, player_x_check);
    return(1);   
}


// int prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check)
// {
//     (void)game_data;
//     printf("game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
//     if (player_x_check >= 0 && player_y_check >= 0 && player_x_check <= WINDOW_WIDTH - 1 && player_y_check <= WINDOW_HEIGHT - 1)
//     {
//         printf("Trying move to: \n");
//         printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %i\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN]);
//         printf("player_y_check is %i\n", player_y_check);
//         printf("player_x_check is %i\n", player_x_check);
//         printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
//         printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);

//         // if (game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 0 || game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 3)
//         if (game_data->maze.g[(player_y_check) / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 0 
//             || game_data->maze.g[(player_y_check) / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 3)
//         {
//             printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %i\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / PLAYER_STEP]);
//             printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
//             printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);
//             printf("player_y_check is %i\n", player_y_check);
//             printf("player_x_check is %i\n", player_x_check);

//             game_data->player->y = player_y_check;
//             game_data->player->x = player_x_check; 
//             printf("Valid mode to -> game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
//             return (0);
//         }
//     }
//     printf("Invalid move try to ->  player_y_check %i and player_x_check %i \n", player_y_check, player_x_check);
//     return(1);   
// }


// int prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check)
// {
//     (void)game_data;
//     printf("game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
//     if (player_x_check >= 0 && player_y_check >= 0 && player_x_check <= WINDOW_WIDTH - 1 && player_y_check <= WINDOW_HEIGHT - 1)
//     {
//         printf("Trying move to: \n");
//         printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %i\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN]);
//         printf("player_y_check is %i\n", player_y_check);
//         printf("player_x_check is %i\n", player_x_check);


//         printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
//         printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);

//         // if (game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 0 || game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 3)
//         if (game_data->maze.g[(player_y_check) / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 0 
//             || game_data->maze.g[(player_y_check) / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] == 3)
//         {
//             printf("game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / MINIMAP_SQUARE_SIDE_LEN] is %i\n", game_data->maze.g[player_y_check / MINIMAP_SQUARE_SIDE_LEN][player_x_check / PLAYER_STEP]);
//             printf("player_y_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_y_check / MINIMAP_SQUARE_SIDE_LEN);
//             printf("player_x_check / MINIMAP_SQUARE_SIDE_LEN is %i\n", player_x_check / MINIMAP_SQUARE_SIDE_LEN);
//             printf("player_y_check is %i\n", player_y_check);
//             printf("player_x_check is %i\n", player_x_check);

//             game_data->player->y = player_y_check;
//             game_data->player->x = player_x_check; 
//             printf("Valid mode to -> game_data->player->x and y in struct is %i and %i\n", game_data->player->x,  game_data->player->y);
//             return (0);
//         }
        
//         //     //player_x_check = 25; //in pixels
//         //     //player_y_check = 15; //in pixels
//         //     //game_data->player_init_loc[0] = 1;// 2nd row this is y
//         //     //game_data->player_init_loc[1] = 2;// 3rd pos from left this x
//         //     //
//         // }


//     }
//     printf("Invalid move try to ->  player_y_check %i and player_x_check %i \n", player_y_check, player_x_check);

//     return(1);   
// }

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

