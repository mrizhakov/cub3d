/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:00:24 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/04/14 00:56:23 by mrizakov         ###   ########.fr       */
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
    printf("Texture file for NO is |%s|\n", texture_filename);


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
    // direction = ft_strdup(texture_filename);
    // free(texture_filename);
    // game_data.so_texture_filename = NULL;

    
    //now texture file is open, dont forget to close
    //close(texture_fd)

    
    return(texture_filename);
}

int parse_directions(t_game *game_data, char *map_line)
{
    if (ft_strnstr(map_line, "NO", ft_strlen(map_line)))
    {
        game_data->no_texture_filename = parse_textures(map_line, "NO");
    	printf("Inside parse_directions game_data.no_texture_filename contains %s\n", game_data->no_texture_filename);

    }
    if (ft_strnstr(map_line, "SO", ft_strlen(map_line)))
    {
        game_data->so_texture_filename = parse_textures(map_line, "SO");
    	printf("Inside parse_directions game_data.so_texture_filename contains %s\n", game_data->so_texture_filename);
    }
    if (ft_strnstr(map_line, "WE", ft_strlen(map_line)))
    {
        game_data->we_texture_filename = parse_textures(map_line, "WE");
    	printf("Inside parse_directions game_data.we_texture_filename contains %s\n", game_data->we_texture_filename);

    }
    if (ft_strnstr(map_line, "EA", ft_strlen(map_line)))
    {
        game_data->ea_texture_filename = parse_textures(map_line, "EA");
    	printf("Inside parse_directions game_data.ea_texture_filename contains %s\n", game_data->ea_texture_filename);
    }
    return(0);

//     NO ./src/textures/DarkAbstractBackgrounds_03.png
// SO ./src/textures/DarkAbstractBackgrounds_06.png
// WE ./src/textures/DarkAbstractBackgrounds_09.png
// EA ./src/textures/DarkAbstractBackgrounds_10.png
}



int map_parsing(char *filename, t_game *game_data)
{
    int fd;
    char *map_line;
    //char *map_buf;
    (void)game_data;


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
    // map_line = get_next_line(fd);
    // printf("%s", map_line);

    // parse_textures(game_data, map_line);
    // printf("Map line is %s\n", map_line);
    // free(map_line);
    // map_line = ft_strdup("");
    
    // while (map_line != NULL)
    // {
    //     free(map_line);
    //     map_line = get_next_line(fd);
    //     parse_textures(game_data, map_line);
    //     printf("Map line is %s\n", map_line);
    //     // free(map_line);
    // }
    map_line = NULL;
    printf("Presto! Here is the map:\n");

    while (1)
    {
        map_line = get_next_line(fd);
        if (map_line == NULL)
        {
            printf("Map is finito!\n");
            close(fd);
            return(0);
        }
        parse_directions(game_data, map_line);
        printf("%s", map_line);
        free(map_line);
    }
    //free(map_line);

    close(fd);
    return (0);
}

int	iffile_cub(char *map_file_name)
{
	char	*find_ber;

	find_ber = ft_strrchr(map_file_name, '.');
	if (!find_ber || ft_strncmp(find_ber, ".cub", 5) != 0)
    {
        ft_printf("Error: Not a .cub file.\n");
		return (1);
    }
	return (0);
}

int			is_valid_char(char matrix_val)
{
	if (matrix_val && matrix_val != '1' && matrix_val != '0' && matrix_val != '2' && matrix_val
		!= 'N' && matrix_val != 'S' && matrix_val != 'W' && matrix_val != 'E' && matrix_val
		!= ' ')
		return (1);
	return (0);
}

int		no_of_players(char matrix_val)
{
	int i;

	i = 0;
	if (matrix_val == 'N' || matrix_val == 'S' || matrix_val == 'W' || matrix_val == 'E')
		i++;
	return (i);
}// just one player per map

