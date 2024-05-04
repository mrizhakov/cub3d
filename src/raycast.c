/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:58:52 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/05 01:56:11 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_ray(t_game *game_data, double ray_angle)
{
    drawLine(game_data->player->x, 
            game_data->player->y, 
            game_data->player->x + cos(ray_angle) * 30 + 0.00001, 
            game_data->player->y + sin(ray_angle) * 30 + 0.00001, 
            game_data->player->color);
}

double  distance_between_points(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2-x1) * (x2 - x1) + (y2-y1) * (y2 - y1)));
}

// TODO: needs to be split up in logical norminette-sized functions
// TODO: potential bug with x and y offset (diagonal lines are empty) - need to check if this affects 3d game projection

void    cast_ray(t_game *game_data, double ray_angle, int column_id)
{
    (void)column_id;
    double wallHitX;
    double wallHitY;
    double xstep;
    double ystep;
    double distance;
    double xintercept;
    double yintercept;
    int is_ray_facing_down;
    int is_ray_facing_right;
    int is_ray_facing_up;
    int is_ray_facing_left;
    double next_hor_touch_x;
    double next_hor_touch_y;
    int found_hor_hit;
    double hor_wall_hit_x;
    double hor_wall_hit_y;
    
    found_hor_hit = 0;
    hor_wall_hit_x = 0;
    hor_wall_hit_y = 0;


    wallHitX = 0;
    wallHitY = 0;
    
 

    // ray direction logic
    
    is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI; // is_ray_facing_down and right are booleans 0
    is_ray_facing_up = !is_ray_facing_down;
    
    is_ray_facing_right = ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5;
    is_ray_facing_left = !is_ray_facing_right;

    // printf("is ray facing up? up %d down %d\n", is_ray_facing_up, is_ray_facing_down);
    // printf("is ray facing right or left? right %d left %d\n", is_ray_facing_right, is_ray_facing_left);
    

    

    // horizontal ray intersection logic
    yintercept = floor(game_data->player->y / MINIMAP_SQUARE_SIDE_LEN) * MINIMAP_SQUARE_SIDE_LEN;
    if (is_ray_facing_down)
        yintercept += is_ray_facing_down * MINIMAP_SQUARE_SIDE_LEN; // add 1 extra square if ray is pointing down
    
    xintercept = game_data->player->x + (yintercept - game_data->player->y) / tan(ray_angle);
    
    //Ystep
    ystep = MINIMAP_SQUARE_SIDE_LEN;
    
    if (is_ray_facing_up)//invert if facing up
        ystep *= is_ray_facing_up * -1;

    
    //Xstep
    xstep = MINIMAP_SQUARE_SIDE_LEN / tan(ray_angle);
    if (is_ray_facing_right)
        xstep = MINIMAP_SQUARE_SIDE_LEN / tan(ray_angle);
    if (is_ray_facing_left && xstep > 0)
        xstep *= -1;
    if (is_ray_facing_right && xstep < 0)
        xstep *= -1;

    next_hor_touch_x = xintercept;
    next_hor_touch_y = yintercept;
    

    // replace this decrement with a subtraction in the if condition for wall hit
    if (is_ray_facing_up)
        next_hor_touch_y--;

    // double mod_next_hor_touch_y;

    // mod_next_hor_touch_y = next_hor_touch_y;
    
    // if (is_ray_facing_up)
    //     mod_next_hor_touch_y = next_hor_touch_y--;
    
        
    // increment xstep and ystep until we find a wall
    while(next_hor_touch_x >= 0 && next_hor_touch_y >= 0 
        && next_hor_touch_y /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION
        && next_hor_touch_x /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION)
    // while(next_hor_touch_x >= 0 && next_hor_touch_x <= WINDOW_WIDTH 
    //     && next_hor_touch_y >= 0 && next_hor_touch_y <= WINDOW_HEIGHT
    //     && next_hor_touch_y /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION
    //     && next_hor_touch_x /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION)
    {
        // printf("Looking for a wall -> Raycast endpoint x %f, y %f\n", next_hor_touch_x, next_hor_touch_y);
    
        if (game_data->maze.g[(int)(next_hor_touch_y / MINIMAP_SQUARE_SIDE_LEN)][(int)(next_hor_touch_x / MINIMAP_SQUARE_SIDE_LEN)] == '1')
        {
            //found a wall
            found_hor_hit = 1;
            hor_wall_hit_x = next_hor_touch_x;
            hor_wall_hit_y = next_hor_touch_y;
            printf("Found horizontal wall hit!!! -> Player at x %f, y %f, Raycast endpoint x %f, y %f, square y %f, square x %f\n", game_data->player->x, game_data->player->y, hor_wall_hit_x, hor_wall_hit_y, next_hor_touch_y / MINIMAP_SQUARE_SIDE_LEN, next_hor_touch_x / MINIMAP_SQUARE_SIDE_LEN);
            // drawLine(game_data->player->x, game_data->player->y, hor_wall_hit_x, hor_wall_hit_y, game_data->player->color);
            break;
        }
        else
        {
            next_hor_touch_x += xstep;
            next_hor_touch_y += ystep;
            //drawLine(next_hor_touch_x, next_hor_touch_y, next_hor_touch_x, next_hor_touch_y, 0xFF00FFFF);
            
            printf("Didnt find horizontal wall -> Player at x %f, y %f, Raycast endpoint x %f, y %f, square y %f, square x %f\n", game_data->player->x, game_data->player->y, next_hor_touch_x, next_hor_touch_y, next_hor_touch_y / MINIMAP_SQUARE_SIDE_LEN, next_hor_touch_x / MINIMAP_SQUARE_SIDE_LEN);

            // mod_next_hor_touch_y += ystep;
        }
    }
 //////////////////////////////////////////////

    // vertical ray intersection logic
    int found_vert_hit;
    double vert_wall_hit_x;
    double vert_wall_hit_y;
    double next_vert_touch_x;
    double next_vert_touch_y;
    
    found_vert_hit = 0;
    vert_wall_hit_x = 0;
    vert_wall_hit_y = 0;
    
    xintercept = floor(game_data->player->x / MINIMAP_SQUARE_SIDE_LEN) * MINIMAP_SQUARE_SIDE_LEN;
    if (is_ray_facing_right)
        xintercept += is_ray_facing_right * MINIMAP_SQUARE_SIDE_LEN; // add 1 extra square if ray is pointing down
    
    yintercept = game_data->player->y + (xintercept - game_data->player->x) * tan(ray_angle);
    
    //Xstep
    xstep = MINIMAP_SQUARE_SIDE_LEN;
    
    if (is_ray_facing_left)//invert if facing up
        xstep *= is_ray_facing_left * -1;

    
    //Ystep
    ystep = MINIMAP_SQUARE_SIDE_LEN * tan(ray_angle);
    // if (is_ray_facing_up)
    //     ystep = MINIMAP_SQUARE_SIDE_LEN / tan(ray_angle);
    if (is_ray_facing_up && ystep > 0)
        ystep *= -1;
    if (is_ray_facing_down && ystep < 0)
        ystep *= -1;

    next_vert_touch_x = xintercept;
    next_vert_touch_y = yintercept;

    
    // double mod_next_vert_touch_x;

    // mod_next_vert_touch_x = next_vert_touch_x;
    
    // if (is_ray_facing_left)
    //     mod_next_vert_touch_x--;
    
    if (is_ray_facing_left)
        next_vert_touch_x--;

    // while(next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH 
    //     && next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT
    //     && next_vert_touch_y /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION
    //     && next_vert_touch_x /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION)
    while(next_vert_touch_x >= 0 && next_vert_touch_y >= 0
        && next_vert_touch_y /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION
        && next_vert_touch_x /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION)
    {
        // printf("Looking for a wall -> Raycast endpoint x %f, y %f\n", next_vert_touch_x, next_vert_touch_y);

        if (game_data->maze.g[(int)(next_vert_touch_y / MINIMAP_SQUARE_SIDE_LEN)][(int)(next_vert_touch_x / MINIMAP_SQUARE_SIDE_LEN)] == '1')
        {
            //found a wall
            found_vert_hit = 1;
            vert_wall_hit_x = next_vert_touch_x;
            vert_wall_hit_y = next_vert_touch_y;
            printf("Found vertical wall hit!!! -> Player at x %f, y %f, Raycast endpoint x %f, y %f, square y %f, square x %f\n", game_data->player->x, game_data->player->y, vert_wall_hit_x, vert_wall_hit_y, next_vert_touch_y / MINIMAP_SQUARE_SIDE_LEN, next_vert_touch_x / MINIMAP_SQUARE_SIDE_LEN);
            // drawLine(game_data->player->x, game_data->playernext_hor_touch_x->y, vert_wall_hit_x, vert_wall_hit_y, game_data->player->color);
            break;
        }
        else
        {
            next_vert_touch_x += xstep;
            next_vert_touch_y += ystep;
            // mod_next_vert_touch_x += xstep;
        }
    }
        // printf("Looking for a wall -> Raycast endpoint x %f, y %f\n", next_vert_touch_x, next_vert_touch_y);
// 
        // if (game_data->maze.g[(int)(next_vert_touch_y / MINIMAP_SQUARE_SIDE_LEN)][(int)(next_vert_touch_x / MINIMAP_SQUARE_SIDE_LEN)] == '1')
        // {
        //     //found a wall
        //     found_vert_hit = 1;
        //     vert_wall_hit_x = next_vert_touch_x;
        //     vert_wall_hit_y = next_vert_touch_y;
        //     printf("Found a wall!!! -> Raycast endpoint x %f, y %f, square y %f, square x %f\n", vert_wall_hit_x, wall_hit_y, next_vert_touch_y / MINIMAP_SQUARE_SIDE_LEN, next_vert_touch_x / MINIMAP_SQUARE_SIDE_LEN);
        //     // drawLine(game_data->player->x, game_data->player->y, vert_wall_hit_x, vert_wall_hit_y, game_data->player->color);
        //     break;
        // }
        // else
        // {
        //     next_vert_touch_x += xstep;
        //     next_vert_touch_y += ystep;
        // }
    // }

    //calculate both distances, and choose the smallest value


    double  shortest_wall_hit_x;
    double  shortest_wall_hit_y; 
    int     was_hit_vertical;
    
    was_hit_vertical = 0;   
    distance = 0;   

    double distance_hor;
    double distance_vert;



    if (found_hor_hit)
    {
        distance_hor = distance_between_points(game_data->player->x, game_data->player->y, hor_wall_hit_x, hor_wall_hit_y);
        printf("found_hor_hit true\n");
    }
    else
        distance_hor = INT_MAX;

    if (found_vert_hit)
    {
        distance_vert = distance_between_points(game_data->player->x, game_data->player->y, vert_wall_hit_x, vert_wall_hit_y);
        printf("found_vert_hit true\n");

    }
    else
        distance_vert = INT_MAX;

    if (distance_hor < distance_vert)
    {
        shortest_wall_hit_x = hor_wall_hit_x;
        shortest_wall_hit_y = hor_wall_hit_y;
        distance = distance_hor;
    }
    else
    {
        shortest_wall_hit_x = vert_wall_hit_x;
        shortest_wall_hit_y = vert_wall_hit_y;
        distance = distance_vert;
    }
    if (distance_vert < distance_hor)
        was_hit_vertical = 1;
    printf("hor_wall_hit_x %f hor_wall_hit_y %f \n", hor_wall_hit_x, hor_wall_hit_y);
    printf("vert_wall_hit_x %f vert_wall_hit_y %f \n", vert_wall_hit_x, vert_wall_hit_y);


    printf("distance_hor is %f, distance_vert is %f \n", distance_hor, distance_vert);
    
    printf("Shortest distance is -> Player at x %u, y %u, Raycast endpoint x %u, y %u, square y %f, square x %f\n\n\n", 
    (uint32_t)game_data->player->x, (uint32_t)game_data->player->y, 
    (uint32_t)shortest_wall_hit_x, (uint32_t)shortest_wall_hit_y, 
    next_vert_touch_y / MINIMAP_SQUARE_SIDE_LEN, next_vert_touch_x / MINIMAP_SQUARE_SIDE_LEN);

    drawLine((uint32_t)game_data->player->x, (uint32_t)game_data->player->y, 
            (uint32_t)shortest_wall_hit_x, (uint32_t)shortest_wall_hit_y, 
            game_data->player->color);
}

void    draw_fov(t_game *game_data)
{
    unsigned int    column_id;
    double          ray_angle;
    int             i;
    
    i = 0;
    column_id = 0;
    
    ray_angle = game_data->player_angle - (game_data->fov_angle/2);
    
    while(i < 1)
    {
        game_data->redraw_minimap = 0;
        ray_angle += game_data->fov_angle / 1;
        ray_angle = check_angle_overflow(game_data, ray_angle);
        cast_ray(game_data, ray_angle, i);
        i++;
    }
    game_data->redraw_minimap = 1;
}