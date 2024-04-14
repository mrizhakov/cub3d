
#include "../cub3d.h"

void free_to_null_string(char *str)
{
    if (str)
        free(str);
    str = NULL;
}

void free_to_null_char_arr(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
    {
        free(str[i]);
        i++;
    }
    if (str != NULL)
        free(str);
}

void initialise_to_null(t_game *game_data) 
{
    game_data->no_texture_filename = NULL;
    game_data->so_texture_filename = NULL;
    game_data->we_texture_filename = NULL;
    game_data->ea_texture_filename = NULL;
    game_data->no_texture_present = 0;
	game_data->so_texture_present = 0;
	game_data->we_texture_present = 0;
	game_data->ea_texture_present = 0;
    game_data->all_textures_present = 0;
    game_data->direction_count = 0;
    game_data->floor.color[0] = -1;


    game_data->floor.color[1] = -1;
    game_data->floor.color[2] = -1;
    game_data->floor.valid_rgb = -1;
    game_data->ceiling.color[0] = -1;
    game_data->ceiling.color[1] = -1;
    game_data->ceiling.color[2] = -1;
    game_data->ceiling.valid_rgb = -1;
}


void free_on_exit(t_game *game_data) 
{
    free_to_null_string(game_data->no_texture_filename);
    free_to_null_string(game_data->so_texture_filename);
    free_to_null_string(game_data->we_texture_filename);
    free_to_null_string(game_data->ea_texture_filename);
    free(game_data);
}
