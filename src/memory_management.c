/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:53:41 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/04 18:52:40 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

void    init_maze(t_game *game_maze)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            game_maze->maze.g[y][x] = 'Z';
            x++;
        }
        x = 0;
        y++;
    }
    game_maze->maze.valid_maze = -1;
}

t_maze  init_t_maze(t_maze maze)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            maze.g[y][x] = 'Z';
            x++;
        }
        x = 0;
        y++;
    }
    maze.valid_maze = -1;
    return(maze);
}


void initialise_to_null(t_game *game_data) 
{
    game_data->no_texture_filename = NULL;
    game_data->so_texture_filename = NULL;
    game_data->we_texture_filename = NULL;
    game_data->ea_texture_filename = NULL;
    game_data->no_texture_count = 0;
	game_data->so_texture_count = 0;
	game_data->we_texture_count = 0;
	game_data->ea_texture_count = 0;
    game_data->all_textures_ok = 0;
    game_data->direction_count = 0;
    game_data->floor.color[0] = -1;
    game_data->floor.color[1] = -1;
    game_data->floor.color[2] = -1;
    game_data->floor.valid_rgb = -1;
    game_data->ceiling.color[0] = -1;
    game_data->ceiling.color[1] = -1;
    game_data->ceiling.color[2] = -1;
    game_data->ceiling.valid_rgb = -1;
    game_data->floor_count = 0; 
	game_data->ceiling_count = 0;
	game_data->player_count = 0;
    game_data->player_init_loc[0] = 0;
    game_data->player_init_loc[1] = 0;
    game_data->player_init_dir = 1.0;
    game_data->player = malloc(sizeof(t_double_pixel));
    game_data->player->y = 0;
    game_data->player->x = 0;
    game_data->player->color = 0x00FF00FF;
    game_data->minimap = malloc(sizeof(t_double_pixel));
    game_data->minimap->y = 0;
    game_data->minimap->x = 0;
    game_data->redraw_minimap = 0;
    game_data->maze_start.y = 0;
    game_data->maze_start.x = 0;
    game_data->maze_end.y = 0;
    game_data->maze_end.x = 0;
    game_data->maze_closed = -1;

    // game_data->player_angle = 0.1; // set starting angle based on player init position

    // game_data->player_dir_x= cos(game_data->player_angle) * 5;
    // game_data->player_dir_y = sin(game_data->player_angle) * 5;
    game_data->player_angle = M_PI / 2;
    game_data->player_turn_dir = 0;
    game_data->player_walk_dir = 0;
    game_data->player_turn_speed = TURNING_SPEED * (M_PI / 180);
    game_data->fov_angle = FOV * (M_PI / 180);
    game_data->num_rays = WINDOW_WIDTH / 1;;

    init_maze(game_data);
}

void free_on_exit(t_game *game_data) 
{
    free_to_null_string(game_data->no_texture_filename);
    free_to_null_string(game_data->so_texture_filename);
    free_to_null_string(game_data->we_texture_filename);
    free_to_null_string(game_data->ea_texture_filename);
    free(game_data->minimap);
    free(game_data->player);
    free(game_data);
}


void init_wall(t_game *game_data) 
{
	game_data->wall = malloc(sizeof(t_wall));
	game_data->projection = malloc(sizeof(t_wall));
}
