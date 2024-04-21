
#include "../cub3d.h"


int prevent_wall_collisions(t_game *game_data, int player_y_check, int player_x_check)
{
    (void)game_data;
    printf("game_data->player->y and x in struct is %i and %i\n", game_data->player->y,  game_data->player->x);
    if (player_x_check >= 0 && player_y_check >= 0 && player_x_check <= WINDOW_WIDTH - 1 && player_y_check <= WINDOW_HEIGHT - 1)
    {
        game_data->player->y = player_y_check;
        game_data->player->x = player_x_check; 
        printf("Valid mode to -> game_data->player->y and x in struct is %i and %i\n", game_data->player->y,  game_data->player->x);
        return (0);
    }
    printf("Invalid move try to ->  player_y_check %i and player_x_check %i \n", player_y_check, player_x_check);

    return(1);   
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

