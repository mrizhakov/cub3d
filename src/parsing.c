/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:00:24 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/04/24 21:06:19 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char *parse_textures(char *map_line, char *direction)
{
    char *texture_line;
    char *texture_filename;
    int   texture_fd;
        
    texture_line =  ft_strnstr(map_line, direction, ft_strlen(map_line));
    if (texture_line == NULL)
    {
        free(map_line);
        return(NULL);
    }
    texture_line++;
    texture_line++;

    texture_filename = ft_strtrim(texture_line, " \n"); //malloc here
    texture_fd = valid_file(texture_filename);
    if (texture_fd == 0)
    {
        perror("Can't open texture files!");
        free(texture_filename);
        return(NULL);
    }
    if (check_file_extension(texture_filename, ".png") || check_read_file(texture_fd))
    {
        perror("Texture files are no bueno. Bring your nice .png's!");
        free(texture_filename);
        free(map_line);
        close(texture_fd);
        return(NULL);
    }
    printf("Texture %s opened!\n", texture_filename);
    return(texture_filename);
}

void check_textures_ok(t_game *game_data)
{
    if (game_data->no_texture_filename 
        && game_data->so_texture_filename 
        && game_data->we_texture_filename 
        && game_data->ea_texture_filename 
        && game_data->no_texture_count == 1
        && game_data->so_texture_count == 1
        && game_data->we_texture_count == 1
        && game_data->ea_texture_count == 1)
        game_data->all_textures_ok = 1;
    else
        game_data->all_textures_ok = 0;
    if (game_data->no_texture_count > 1
        && game_data->so_texture_count > 1
        && game_data->we_texture_count > 1
        && game_data->ea_texture_count > 1)
        game_data->all_textures_ok = 0;    
}


int parse_directions(t_game *game_data, char *map_line)
{
    if (ft_strnstr(map_line, "NO", ft_strlen(map_line)))
    {
        if (game_data->no_texture_filename == NULL)
            game_data->no_texture_filename = parse_textures(map_line, "NO");
        printf("Inside parse_directions game_data.no_texture_filename contains %s\n", game_data->no_texture_filename);
        game_data->no_texture_count++;
    }
    if (ft_strnstr(map_line, "SO", ft_strlen(map_line)))
    {
        if (game_data->so_texture_filename == NULL)
            game_data->so_texture_filename = parse_textures(map_line, "SO");
        printf("Inside parse_directions game_data.so_texture_filename contains %s\n", game_data->so_texture_filename);
        game_data->so_texture_count++;
    }
    if (ft_strnstr(map_line, "WE", ft_strlen(map_line)))
    {
        if (game_data->we_texture_filename == NULL)
            game_data->we_texture_filename = parse_textures(map_line, "WE");
        printf("Inside parse_directions game_data.we_texture_filename contains %s\n", game_data->we_texture_filename);
        game_data->we_texture_count++;
    }
    if (ft_strnstr(map_line, "EA", ft_strlen(map_line)))
    {
        if (game_data->ea_texture_filename == NULL)
            game_data->ea_texture_filename = parse_textures(map_line, "EA");
        printf("Inside parse_directions game_data.ea_texture_filename contains %s\n", game_data->ea_texture_filename);
        game_data->ea_texture_count++;
    }
    check_textures_ok(game_data);
    return(0);
}

t_rgb read_color(char *map_line, char *surface)
{
    t_rgb rgb;

    rgb.valid_rgb = -1;
    char *color_line;
    char *color_def;

    color_line =  ft_strnstr(map_line, surface, ft_strlen(map_line));
    if (color_line == NULL)
    {
        free(map_line);
        rgb.valid_rgb = -1;
        return(rgb);
    }
    color_line++;

    color_def = ft_strtrim(color_line, " \n"); //malloc here
    printf("Color line now is : |%s|\n", color_def);
    char **color_array = ft_split(color_def, ',');
    
    int i = 0;
    while (color_array [i] != NULL)
    {
        rgb.color[i] = ft_atoi(color_array[i]);
        printf("Array %i is : |%d|\n", i, rgb.color[i]);
        i++;
        if (i > 3)
        {
            perror("Invalid color");
            free_to_null_string(color_def);
            rgb.valid_rgb = -1;
            return(rgb);
        }
    }

    int y = 0;
    while (y != i && rgb.color[y] >= 0 && rgb.color[y] <= 255)
    {
        printf("Y is %i\n", y);
        y++;
    }
    rgb.valid_rgb = 1;
    if (y != 3)
    {
        rgb.valid_rgb = -1;
        printf("Y is %i, triggered unvalidity check\n", y);

    }
    printf("Is it a valid RGB? r : %i, g: %i. b: %i, validity: %i\n", rgb.color[0], rgb.color[1], rgb.color[2], rgb.valid_rgb);
    free_to_null_string(color_def);
    free_to_null_char_arr(color_array);
    return (rgb);
}

int parse_color(t_game *game_data, char *map_line)
{
    if (ft_strnstr(map_line, "F", ft_strlen(map_line)))
    {
        game_data->floor_count++;
        if (game_data->floor.valid_rgb == -1)
            game_data->floor = read_color(map_line, "F");
        printf("Inside parse_color game_data->floor.color[0] contains %i\n", game_data->floor.color[0]);
        printf("Inside parse_color game_data->floor.color[1] contains %i\n", game_data->floor.color[1]);
        printf("Inside parse_color game_data->floor.color[2] contains %i\n", game_data->floor.color[2]);
        printf("Inside parse_color game_data->floor.valid_rgb contains %i\n", game_data->floor.valid_rgb);
    }
    if (ft_strnstr(map_line, "C", ft_strlen(map_line)))
    {
        game_data->ceiling_count++;
        if (game_data->ceiling.valid_rgb == -1)
            game_data->ceiling = read_color(map_line, "C");
        printf("Inside parse_color game_data->ceiling.color[0] contains %i\n", game_data->ceiling.color[0]);
        printf("Inside parse_color game_data->ceiling.color[1] contains %i\n", game_data->ceiling.color[1]);
        printf("Inside parse_color game_data->ceiling.color[2] contains %i\n", game_data->ceiling.color[2]);
        printf("Inside parse_color game_data->ceiling.valid_rgb contains %i\n", game_data->ceiling.valid_rgb);
    }
    return(0);
}

int check_colors_ok(t_game *game_data)
{
    if (game_data->floor_count == 1 
        && game_data->ceiling_count == 1
        && game_data->floor.valid_rgb == 1
        && game_data->ceiling.valid_rgb == 1)
        return (1);
    else
        return (0);
}

void print_maze(t_game *game_data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    printf("Printing out maze for educational purposes: \n\n");
    while (y != MAZE_DIMENSION - 1)
    {
        while (x != MAZE_DIMENSION - 1)
        {
            printf("%i", game_data->maze.g[y][x]);
            x++;
        }
        printf("\n");
        x = 0;
        y++;
    }
    printf("\nIs the maze valid? %i\n", game_data->maze.valid_maze);
}

int skip_empty_line(char *map_line)
{
    while((*map_line) && (*map_line == ' ' || *map_line == '\n'))
    {
        if (*map_line == '\n')
            return (1);
        map_line++;
    }
    return (0);
}


int maze_parse(t_game *game_data, char *map_line)
{
    int i;
    int x_axis;
    static int y_axis = 1;

    i = 0;
    x_axis = 1;
    //y_axis = 0;
    //if (is)
    printf("entered maze_parse\n");
    printf("y_axis is %i\n", y_axis);


    // if (skip_empty_line(map_line))
    // {
    //     //y_axis++;
    //     printf("skiping empty line\n");
    //     return(0);
    // }
    while (is_valid_char(map_line[i]))
    {
        printf("Entered loop\n");
        printf("map_line[i] is %c, index %i\n", map_line[i], i);
        


        if (skip_empty_line(map_line))
        {
            //y_axis++;
            printf("skiping empty line\n");
            return(0);
        }
        printf("map_line[i] is %c, index %i\n", map_line[i], i);

        printf("not an empty line\n");
        printf("finding valid characters\n");

        if (map_line[i] == '\n' || map_line[i] == '\r')
        {
            printf("NEWLINE\n");

            printf("\n");

            y_axis++;
            //game_data->maze.g[y][i] = 0;
            
            return (0);
        }
        //printf("map_line is :%c\n", map_line[i]);
        if (map_line[i] == '\t')
        {
            printf("tab\n");
            
            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            i++;
        }
        if (map_line[i] == '0')
        {
            printf("Empty space\n");

            game_data->maze.g[y_axis][x_axis] = 0;
            x_axis++;
            i++;
        }
        if (map_line[i] == ' ')
        {
            printf("Empty space\n");

            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            i++;
        }
        if (map_line[i] == '1')
        {
            printf("One\n");

            game_data->maze.g[y_axis][x_axis] = 1;
            x_axis++;
            i++;
        }
        if (map_line[i] == '2')
        {
            printf("tTo\n");

            game_data->maze.g[y_axis][x_axis] = 2;
            x_axis++;
            i++;
        }
        if (map_line[i] == 'N' || map_line[i] == 'E' || map_line[i] == 'W' || map_line[i] == 'S')
        {
            printf("Found player\n");
            game_data->player_init_loc[0] = x_axis;
            game_data->player_init_loc[1] = y_axis;

            

            game_data->maze.g[y_axis][x_axis] = 3;
            game_data->player->y = y_axis * game_data->minimap_side_len + game_data->minimap_side_len/2;
            game_data->player->x = x_axis * game_data->minimap_side_len + game_data->minimap_side_len/2;

            if (map_line[i] == 'N')
                game_data->player_init_dir = 1;
            if (map_line[i] == 'E')
                game_data->player_init_dir = 2;
            if (map_line[i] == 'W')
                game_data->player_init_dir = 3;
            if (map_line[i] == 'S')
                game_data->player_init_dir = 4;
            x_axis++;
            i++;
        }
    }
    game_data->maze_end.y = y_axis;
    game_data->maze_end.x = x_axis - 1;
    return (1);
}




int map_parsing(char *filename, t_game *game_data)
{
    int fd;
    char *map_line;
    printf("Parsing map\n");
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening map\n");
        //close(fd);
        exit(EXIT_FAILURE);
    }
    if (fd != -1)
    {
        printf("File : %s \n", filename);
        printf("Map opened\n");
        printf("Logging out map for debugging purposes\n");
    }
    
    map_line = NULL;
    printf("Presto! Here is the map:\n");

    while (1)
    {
        map_line = get_next_line(fd);
        if (map_line == NULL)
        {
            printf("-------------------------------------\n");
            printf("Map is finito!\n");
            printf("Final check!\n");

            check_textures_ok(game_data);
            if (game_data->all_textures_ok == 1)
                printf("Textures are ok!\n");
            else
                printf("Colors arent good!\n");
            if (check_colors_ok(game_data))
                printf("Colors are ok!\n");
            else
                printf("Colors arent good!\n");
            close(fd);
            return(0);
        }
        parse_directions(game_data, map_line);
        parse_color(game_data, map_line);
        if (game_data->all_textures_ok == 1 && check_colors_ok(game_data))
        {
            printf("Textures are ok!\n");
            printf("Colors are good!\n");
            printf("Time to parse the map!\n");
            maze_parse(game_data, map_line);
            print_maze(game_data);
            // maze_check_closed(game_data);
            // print_maze(game_data);
            // printf("done!\n");
            // exit(0);
        }
        if (!(game_data->all_textures_ok == 1 && check_colors_ok(game_data)))
        {
            printf("Textures are ok!\n");
            printf("Colors arent good!\n");
            printf("Dont even think about parsing the map!\n");
        }
        printf("Map line in main is %s", map_line);
        free(map_line);
    }

    close(fd);
    return (0);
}

int	iffile_cub(char *map_file_name)
{
	char	*find_ber;

	find_ber = ft_strrchr(map_file_name, '.');
	if (!find_ber || ft_strncmp(find_ber, ".cub", 5) != 0)
    {
        printf("Error: Not a .cub file.\n");
		return (1);
    }
	return (0);
}

int			is_valid_char(char matrix_val)
{
	if (matrix_val 
        && (matrix_val == '1' || matrix_val == '0' || matrix_val == '2' 
        || matrix_val == 'N' || matrix_val == 'E' || matrix_val == 'W' 
        || matrix_val == 'S' || matrix_val == ' ' || matrix_val == '\n' || matrix_val == '\t'))
		return (1);
    else
	    return (0);
}

int			is_valid_int(int matrix_val)
{
    if (matrix_val == 1 || matrix_val == 0 || matrix_val == 3)
	// if (matrix_val 
    //     && (matrix_val == 1 || matrix_val == 0 || matrix_val == 2 
    //     || matrix_val == 3 || matrix_val == 'E' || matrix_val == 'W' 
    //     || matrix_val == 'S' || matrix_val == ' ' || matrix_val == '\n' || matrix_val == '\t'))
		return (1);
    else
	    return (0);
}

int		no_of_players(t_game *game_data, char matrix_val)
{
	int i;

	i = 0;
	if (matrix_val == 'N' || matrix_val == 'S' 
        || matrix_val == 'W' || matrix_val == 'E')
    {
        i++;
		game_data->player_count++;
    }
	return (i);
}// just one player per map

