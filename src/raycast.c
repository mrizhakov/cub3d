/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:58:52 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/11 19:23:14 by mrizakov         ###   ########.fr       */
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

int is_ray_facing_down(double ray_angle)
{
    return (ray_angle > 0 && ray_angle < M_PI);
}

int is_ray_facing_right(double ray_angle)
{
    return (ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5);
}

int is_ray_facing_up(double ray_angle)
{
    return (!is_ray_facing_down(ray_angle));
}

int is_ray_facing_left(double ray_angle)
{
    return (!is_ray_facing_right(ray_angle));
}

void ray_orientation(t_raycast *ray, double ray_angle)
{
    ray->is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
    ray->is_ray_facing_up = !ray->is_ray_facing_down;
    ray->is_ray_facing_right = ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5;
    ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

void ray_horiz_calc(t_game *game_data, t_raycast *ray, double ray_angle)
{
    ray->yintercept = floor(game_data->player->y / MINIMAP_SQUARE_SIDE_LEN) * MINIMAP_SQUARE_SIDE_LEN;
    if (ray->is_ray_facing_down)
        ray->yintercept += ray->is_ray_facing_down * MINIMAP_SQUARE_SIDE_LEN;
    ray->xintercept = game_data->player->x + (ray->yintercept - game_data->player->y) / tan(ray_angle);
    //Ystep
    ray->ystep = MINIMAP_SQUARE_SIDE_LEN;
    
    if (ray->is_ray_facing_up)   //invert if facing up
        ray->ystep *= ray->is_ray_facing_up * -1;
    //Xstep
    ray->xstep = MINIMAP_SQUARE_SIDE_LEN / tan(ray_angle);
    if (ray->is_ray_facing_right)
        ray->xstep = MINIMAP_SQUARE_SIDE_LEN / tan(ray_angle);
    if (ray->is_ray_facing_left && ray->xstep > 0)
        ray->xstep *= -1;
    if (ray->is_ray_facing_right && ray->xstep < 0)
        ray->xstep *= -1;
    ray->next_hor_touch_x = ray->xintercept;
    ray->next_hor_touch_y = ray->yintercept;
        // replace this decrement with a subtraction in the if condition for wall hit
    if (ray->is_ray_facing_up)
        ray->next_hor_touch_y--;
}

void ray_horiz_loop(t_game *game_data, t_raycast *ray)
{
    // increment xstep and ystep until we find a wall
    while(ray->next_hor_touch_x >= 0 && ray->next_hor_touch_y >= 0 
        && ray->next_hor_touch_y /  MINIMAP_SQUARE_SIDE_LEN < MAZE_DIMENSION - 1
        && ray->next_hor_touch_x /  MINIMAP_SQUARE_SIDE_LEN < MAZE_DIMENSION - 1)
    {
        // printf("Looking for a wall -> Raycast endpoint x %f, y %f\n", next_hor_touch_x, next_hor_touch_y);
        if (game_data->maze.g[(int)(ray->next_hor_touch_y / MINIMAP_SQUARE_SIDE_LEN)][(int)(ray->next_hor_touch_x / MINIMAP_SQUARE_SIDE_LEN)] == '1')
        {
            //found a wall
            ray->found_hor_hit = 1;
            ray->hor_wall_hit_x = ray->next_hor_touch_x;
            ray->hor_wall_hit_y = ray->next_hor_touch_y;
            break;
        }
        else
        {
            ray->next_hor_touch_x += ray->xstep;
            ray->next_hor_touch_y += ray->ystep;
        }
    }
}


void ray_vert_calc(t_game *game_data, t_raycast *ray, double ray_angle)
{
    ray->xintercept = floor(game_data->player->x / MINIMAP_SQUARE_SIDE_LEN) * MINIMAP_SQUARE_SIDE_LEN;
    if (ray->is_ray_facing_right)
        ray->xintercept += ray->is_ray_facing_right * MINIMAP_SQUARE_SIDE_LEN; // add 1 extra square if ray is pointing down
    
    ray->yintercept = game_data->player->y + (ray->xintercept - game_data->player->x) * tan(ray_angle);
    //Xstep
    ray->xstep = MINIMAP_SQUARE_SIDE_LEN;
    if (ray->is_ray_facing_left)
        ray->xstep *= ray->is_ray_facing_left * -1;
    //Ystep
    ray->ystep = MINIMAP_SQUARE_SIDE_LEN * tan(ray_angle);
    if (ray->is_ray_facing_up && ray->ystep > 0)
        ray->ystep *= -1;
    if (ray->is_ray_facing_down && ray->ystep < 0)
        ray->ystep *= -1;

    ray->next_vert_touch_x = ray->xintercept;
    ray->next_vert_touch_y = ray->yintercept;
    if (ray->is_ray_facing_left)
        ray->next_vert_touch_x--;
}

void ray_vert_loop(t_game *game_data, t_raycast *ray)
{
    while(ray->next_vert_touch_x >= 0 && ray->next_vert_touch_y >= 0
        && ray->next_vert_touch_y /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION - 1
        && ray->next_vert_touch_x /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION - 1)
    {
        if (game_data->maze.g[(int)(ray->next_vert_touch_y / MINIMAP_SQUARE_SIDE_LEN)][(int)(ray->next_vert_touch_x / MINIMAP_SQUARE_SIDE_LEN)] == '1')
        {
            ray->found_vert_hit = 1;
            ray->vert_wall_hit_x = ray->next_vert_touch_x;
            ray->vert_wall_hit_y = ray->next_vert_touch_y;
            break;
        }
        else
        {
            ray->next_vert_touch_x += ray->xstep;
            ray->next_vert_touch_y += ray->ystep;
        }
    }
}

void ray_shortest_distance(t_raycast *ray, t_game *game_data)
{
    if (ray->found_hor_hit)
        ray->distance_hor = distance_between_points(game_data->player->x, game_data->player->y, ray->hor_wall_hit_x, ray->hor_wall_hit_y);
    else
        ray->distance_hor = INT_MAX;
    if (ray->found_vert_hit)
        ray->distance_vert = distance_between_points(game_data->player->x, game_data->player->y, ray->vert_wall_hit_x, ray->vert_wall_hit_y);
    else
        ray->distance_vert = INT_MAX;
    if (ray->distance_hor < ray->distance_vert)
    {
        ray->shortest_wall_hit_x = ray->hor_wall_hit_x;
        ray->shortest_wall_hit_y = ray->hor_wall_hit_y;
        ray->distance = ray->distance_hor;
    }
    else
    {
        ray->shortest_wall_hit_x = ray->vert_wall_hit_x;
        ray->shortest_wall_hit_y = ray->vert_wall_hit_y;
        ray->distance = ray->distance_vert;
    }
    if (ray->distance_vert < ray->distance_hor)
        ray->was_hit_vertical = 1;
}


void ray_init_data(t_raycast *ray)
{
    ray->found_hor_hit = 0;
    ray->hor_wall_hit_x = 0;
    ray->hor_wall_hit_y = 0;
    ray->wallHitX = 0;
    ray->wallHitY = 0;
    ray->found_vert_hit = 0;
    ray->vert_wall_hit_x = 0;
    ray->vert_wall_hit_y = 0;
    ray->was_hit_vertical = 0;   
    ray->distance = 0;   
}



// TODO: needs to be split up in logical norminette-sized functions
// TODO: potential bug with x and y offset (diagonal lines are empty) - need to check if this affects 3d game projection
void    draw_minimap_fov(t_game *game_data, t_raycast *ray)
{
    drawLine((uint32_t)game_data->player->x, (uint32_t)game_data->player->y, 
            (uint32_t)ray->shortest_wall_hit_x, (uint32_t)ray->shortest_wall_hit_y, 
            game_data->player->color);
}


void    draw_3d_projection(t_game *game_data, int column_id, t_raycast *ray)
{
    double distance_proj_plane;
    double projected_wall_height;
    double wall_strip_height;
    double wall_top_pixel;

    distance_proj_plane = (WINDOW_WIDTH / 2)/ tan(game_data->fov_angle / 2);
    projected_wall_height  = (MINIMAP_SQUARE_SIDE_LEN / ray->distance) * distance_proj_plane;
    wall_strip_height = projected_wall_height;
    wall_top_pixel = (WINDOW_HEIGHT / 2)  - (wall_strip_height / 2);
    if (wall_top_pixel < 0)
        wall_top_pixel = 0;
    double wall_bottom_pixel = (WINDOW_HEIGHT / 2)  + (wall_strip_height / 2);
    if (wall_bottom_pixel > WINDOW_HEIGHT)
        wall_bottom_pixel = WINDOW_HEIGHT - 1;
    //draw wall projections
    drawLine((uint32_t)column_id, (uint32_t)wall_top_pixel, 
            (uint32_t)column_id, (uint32_t)wall_bottom_pixel, 
            game_data->player->color);
    //draw floor
    
    
    drawLine((uint32_t)column_id, (uint32_t)wall_bottom_pixel, 
            (uint32_t)column_id, (uint32_t)WINDOW_HEIGHT-1, 
            game_data->floor.rgb_color);
    //draw celing
    drawLine((uint32_t)column_id, (uint32_t)wall_top_pixel, 
            (uint32_t)column_id, (uint32_t)0, 
            game_data->ceiling.rgb_color);

    
            
}



void    cast_ray(t_game *game_data, double ray_angle, int column_id)
{
    t_raycast ray;

    (void)column_id;
    ray_init_data(&ray);
    ray_orientation(&ray, ray_angle);
    ray_horiz_calc(game_data, &ray, ray_angle);
    ray_horiz_loop(game_data, &ray);
    ray_vert_calc(game_data, &ray, ray_angle);
    ray_vert_loop(game_data, &ray);
    ray_shortest_distance(&ray, game_data);
    draw_minimap_fov(game_data, &ray);
    // drawLine((uint32_t)game_data->player->x, (uint32_t)game_data->player->y, 
    //         (uint32_t)ray.shortest_wall_hit_x, (uint32_t)ray.shortest_wall_hit_y, 
    //         game_data->player->color);
    draw_3d_projection(game_data, column_id, &ray);

    // double distance_proj_plane = (WINDOW_WIDTH / 2)/ tan(game_data->fov_angle / 2);
    // double projected_wall_height  = (MINIMAP_SQUARE_SIDE_LEN / ray.distance) * distance_proj_plane;
    // double wallstripheight = projected_wall_height;
    // double wall_top_pixel = (WINDOW_HEIGHT / 2)  - (wallstripheight / 2);
    // if (wall_top_pixel < 0)
    //     wall_top_pixel = 0;
    // double wall_bottom_pixel = (WINDOW_HEIGHT / 2)  + (wallstripheight / 2);
    // if (wall_bottom_pixel > WINDOW_HEIGHT)
    //     wall_bottom_pixel = WINDOW_HEIGHT;
    // drawLine((uint32_t)column_id, (uint32_t)wall_top_pixel, 
    //         (uint32_t)column_id, (uint32_t)wall_bottom_pixel, 
    //         game_data->player->color);
    

        
        
}


// void    draw_walls(t_game *game_data)
// {
//     unsigned int    column_id;
//     double          ray_angle;
//     int             i;
    
//     i = 0;
//     column_id = 0;
    
    
//     while(i < game_data->num_rays)
//     {
//         game_data->redraw_minimap = 0;
//         cast_ray(game_data, ray_angle, i);
//         i++;
//     }
//     game_data->redraw_minimap = 1;
// }

void    draw_fov(t_game *game_data)
{
    unsigned int    column_id;
    double          ray_angle;
    int             i;
    
    i = 0;
    column_id = 0;
    
    ray_angle = game_data->player_angle - (game_data->fov_angle/2);
    
    while(i < game_data->num_rays)
    {
        game_data->redraw_minimap = 0;
        ray_angle += game_data->fov_angle / game_data->num_rays;
        ray_angle = check_angle_overflow(game_data, ray_angle);
        cast_ray(game_data, ray_angle, i);
        i++;
    }
    game_data->redraw_minimap = 1;
}