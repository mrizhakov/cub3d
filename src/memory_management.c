
#include "../cub3d.h"

void free_to_null_string(char *str)
{
    if (str)
        free(str);
    str = NULL;
}

void initialise_to_null(t_game *game_data) 
{
    game_data->no_texture_filename = NULL;
    game_data->so_texture_filename = NULL;
    game_data->we_texture_filename = NULL;
    game_data->ea_texture_filename = NULL;
    game_data = NULL;
}


void free_on_exit(t_game *game_data) 
{
    free_to_null_string(game_data->no_texture_filename);
    free_to_null_string(game_data->so_texture_filename);
    free_to_null_string(game_data->we_texture_filename);
    free_to_null_string(game_data->ea_texture_filename);
    free(game_data);
}
