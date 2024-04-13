/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:01:00 by mrizhakov         #+#    #+#             */
/*   Updated: 2024/04/14 00:29:31 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int 	valid_file(char *filename) {
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file \n");
        return(0);
    }
    else
    {
        printf("File opened : %s \n", filename);
        return(fd);
    }
}

int check_read_file(int fd) {
    ssize_t bytes_read;
    char    *buf[FILE_READ_BUFFER];
    
    bytes_read = read(fd, buf, FILE_READ_BUFFER);

    while (bytes_read != 0) 
    {
        bytes_read = read(fd, buf, FILE_READ_BUFFER);
        if (bytes_read == -1) {
            perror("Error reading file\n");
            close(fd);
            return(1);
        }
    }
    close(fd);
    return(0);
}

int check_file_extension(char *filename, char *file_extension) {
    size_t filename_length;
    size_t file_extension_length;


    filename_length = ft_strlen(filename);
    file_extension_length= ft_strlen(file_extension);

    if (ft_strlen(filename) >= file_extension_length && ft_strncmp(filename + ft_strlen(filename) - file_extension_length, file_extension, file_extension_length) == 0)
    {
        printf("File extension for file %s is correct\n", filename);
        return(0);
    }
    else
    {
        perror("File extension incorrect");
        return(1);
    }
}


int error_handling(int argc, const char *argv[])
{
    (void)argv;
    int fd_map;
    if (argc != 2)
    {
        perror("Please provide a map\n");
        return (0);
    }
    fd_map = valid_file((char *)argv[1]);
    if (fd_map == -1 || fd_map == 0)
    {
        perror("Map file is no bueno!");
        exit(1);
    }
    if (check_file_extension((char *)argv[1], ".cub") || check_read_file(fd_map))
    {
        perror("Map file is no bueno!");
        close(fd_map);
        exit(1);
    }
    //now map file is open, dont forget to close
    
    return (0);
}



// You can compare the last 4 characters of a string using pointer arithmetic along with string comparison functions like strcmp or strncmp. Here's how you can do it:

// c
// Copy code
// #include <stdio.h>
// #include <string.h>

// int main() {
//     const char *filename1 = "map.cub";        free(map_line);

//     const char *filename2 = "other.cub";
//     const char *extension = ".cub";
//     size_t len = strlen(extension);

//     // Compare the last 'len' characters of filename1 with extension
//     if (strlen(filename1) >= len && strcmp(filename1 + strlen(filename1) - len, extension) == 0) {
//         printf("%s ends with %s\n", filename1, extension);
//     } else {
//         printf("%s does not end with %s\n", filename1, extension);
//     }

//     // Compare the last 'len' characters of filename2 with extension
//     if (strlen(filename2) >= len && strcmp(filename2 + strlen(filename2) - len, extension) == 0) {
//         printf("%s ends with %s\n", filename2, extension);
//     } else {
//         printf("%s does not end with %s\n", filename2, extension);
//     }

//     return 0;
// }