/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:58:52 by mrizakov          #+#    #+#             */
/*   Updated: 2024/05/03 22:09:19 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_ray(t_game *game_data, double ray_angle)
{
    // printf("game_data->redraw_minimap is %i\n", game_data->redraw_minimap), 

    // printf("Ray drawn --->> Player x : %f Player y: %f Line x : %f Line y : %f\n", 
            // game_data->player->x, 
            // game_data->player->y, 
            // game_data->player->x + cos(game_data->player_angle) * 30, 
            // game_data->player->y + sin(game_data->player_angle) * 30);
    drawLine(game_data->player->x, 
            game_data->player->y, 
            game_data->player->x + cos(ray_angle) * 30 + 0.00001, 
            game_data->player->y + sin(ray_angle) * 30 + 0.00001, 
            game_data->player->color); //why y + 2?
    // drawLine(game_data->player->x + 1, game_data->player->y + 1, game_data->player->x + game_data->player_dir_x * 5, game_data->player->y + game_data->player_dir_y * 5, game_data->player->color); //why y + 2?
    // game_data->redraw_minimap = 1;

}

double  distance_between_points(double x1, double y1, double x2, double y2)
{

    return (sqrt((x2-x1) * (x2 - x1) + (y2-y1) * (y2 - y1)));
}

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



    found_hor_hit = -1;
    hor_wall_hit_x = 0;
    hor_wall_hit_y = 0;





    wallHitX = 0;
    wallHitY = 0;
    
 

    
    is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI; // is_ray_facing_down and right are booleans 0
    is_ray_facing_up = !is_ray_facing_down;
    
    is_ray_facing_right = ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5;
    is_ray_facing_left = !is_ray_facing_right;

    printf("is ray facing up? up %d down %d\n", is_ray_facing_up, is_ray_facing_down);
    printf("is ray facing right or left? right %d left %d\n", is_ray_facing_right, is_ray_facing_left);
    

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
    
    if (is_ray_facing_up)
        next_hor_touch_y--;


        
    // increment xstep and ystep until we find a wall
    while(next_hor_touch_x >= 0 && next_hor_touch_x <= WINDOW_WIDTH 
        && next_hor_touch_y >= 0 && next_hor_touch_y <= WINDOW_HEIGHT
        && next_hor_touch_y /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION
        && next_hor_touch_x /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION)
    {
        printf("Looking for a wall -> Raycast endpoint x %f, y %f\n", next_hor_touch_x, next_hor_touch_y);

        if (game_data->maze.g[(int)(next_hor_touch_y / MINIMAP_SQUARE_SIDE_LEN)][(int)(next_hor_touch_x / MINIMAP_SQUARE_SIDE_LEN)] == '1')
        {
            //found a wall
            found_hor_hit = 1;
            hor_wall_hit_x = next_hor_touch_x;
            hor_wall_hit_y = next_hor_touch_y;
            printf("Found a wall!!! -> Raycast endpoint x %f, y %f, square y %f, square x %f\n", hor_wall_hit_x, hor_wall_hit_y, next_hor_touch_y / MINIMAP_SQUARE_SIDE_LEN, next_hor_touch_x / MINIMAP_SQUARE_SIDE_LEN);
            // drawLine(game_data->player->x, game_data->player->y, hor_wall_hit_x, hor_wall_hit_y, game_data->player->color);
            break;
        }
        else
        {
            next_hor_touch_x += xstep;
            next_hor_touch_y += ystep;
        }
    }
 //////////////////////////////////////////////

    // vertical ray intersection logic
    int found_vert_hit;
    double vert_wall_hit_x;
    double vert_wall_hit_y;
    double next_vert_touch_x;
    double next_vert_touch_y;
    
    found_vert_hit = -1;
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
    
    if (is_ray_facing_left)
        next_vert_touch_x--;

    while(next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH 
        && next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT
        && next_vert_touch_y /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION
        && next_vert_touch_x /  MINIMAP_SQUARE_SIDE_LEN <= MAZE_DIMENSION)
    {
        printf("Looking for a wall -> Raycast endpoint x %f, y %f\n", next_vert_touch_x, next_vert_touch_y);

        if (game_data->maze.g[(int)(next_vert_touch_y / MINIMAP_SQUARE_SIDE_LEN)][(int)(next_vert_touch_x / MINIMAP_SQUARE_SIDE_LEN)] == '1')
        {
            //found a wall
            found_vert_hit = 1;
            vert_wall_hit_x = next_vert_touch_x;
            vert_wall_hit_y = next_vert_touch_y;
            printf("Found a wall!!! -> Raycast endpoint x %f, y %f, square y %f, square x %f\n", vert_wall_hit_x, vert_wall_hit_y, next_vert_touch_y / MINIMAP_SQUARE_SIDE_LEN, next_vert_touch_x / MINIMAP_SQUARE_SIDE_LEN);
            // drawLine(game_data->player->x, game_data->player->y, vert_wall_hit_x, vert_wall_hit_y, game_data->player->color);
            break;
        }
        else
        {
            next_vert_touch_x += xstep;
            next_vert_touch_y += ystep;
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

    double shortest_wall_hit_x;
    double shortest_wall_hit_y;    
    distance = 0;   

    double distance_hor;
    double distance_vert;


    if (found_hor_hit)
        distance_hor = distance_between_points(game_data->player->x, game_data->player->y, hor_wall_hit_x, hor_wall_hit_y);
    else
        distance_hor = INT_MAX;

    if (found_vert_hit)
        distance_vert = distance_between_points(game_data->player->x, game_data->player->y, vert_wall_hit_x, vert_wall_hit_y);
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
        
    drawLine(game_data->player->x, game_data->player->y, shortest_wall_hit_x, shortest_wall_hit_y, game_data->player->color);

    

    
}

void    draw_fov(t_game *game_data)
{
    unsigned int    column_id;
    double          ray_angle;
    int             i;
    
    i = 0;
    column_id = 0;
    
    ray_angle = game_data->player_angle - (game_data->fov_angle/2);
    // while(i < game_data->num_rays)
    while(i < WINDOW_WIDTH)
    {
        game_data->redraw_minimap = 0;
        // printf("Drawing ray with angle %f is %i \n", game_data->fov_angle, i);
        // printf("FOV/ WINDOW_WIDTH is %f\n", game_data->fov_angle / WINDOW_WIDTH);

        // draw_ray(game_data, ray_angle);
        // cast_ray(game_data, ray_angle, column_id);

        cast_ray(game_data, ray_angle, i);

        // TODO : cast ray
        // TODO : add ray to array of rays
        ray_angle += game_data->fov_angle / game_data->num_rays;
        // printf("Drawing ray with angle %f\n", ray_angle);

        i++;
    }
    game_data->redraw_minimap = 1;

    // drawLine(game_data->player->x + 1, game_data->player->y + 1, game_data->player->x + game_data->player_dir_x * 5, game_data->player->y + game_data->player_dir_y * 5, game_data->player->color); //why y + 2?
}

//super fast raycasting in tiled worlds using DDA
// void draw_rays(t_game *game_data)
// {
//     float vRayUnitStepSize = sqrt(1+(game_data->player_dir_y /game_data->player_dir_x)) * (game_data->player_dir_y /game_data->player_dir_x);
// }

// void draw_rays(t_game *game_data)
// {
//     int r, mx, my, mp, depth_of_field;
//     float rx, ry, ra, xo, yo, a_tan;

//     ra = game_data->player_angle;
//     r = 0;
//     while(r < 1)
//     {
//         //Check horizontal lines
//         depth_of_field = 0;
//         a_tan = -1/tan(ra);
//         if(ra > M_PI) //looking up
//         {
//             ry = (int)game_data->player->y / MINIMAP_SQUARE_SIDE_LEN;
//             rx = (game_data->player->y - ry) * a_tan + game_data->player->x;
//             yo = - MINIMAP_SQUARE_SIDE_LEN;
//             xo = -yo * a_tan;
//         }
//         if(ra < M_PI) //looking down
//         {
//             ry = (int)game_data->player->y / MINIMAP_SQUARE_SIDE_LEN + MINIMAP_SQUARE_SIDE_LEN;
//             rx = (game_data->player->y - ry) * a_tan + game_data->player->x;
//             yo = MINIMAP_SQUARE_SIDE_LEN;
//             xo = -yo * a_tan;
//         }
//         if(ra == 0 || ra == M_PI) //looking on the horizontal plane 
//         {
//             rx = game_data->player->x;
//             ry = game_data->player->y;
//             depth_of_field = MAX_DEPTH_OF_FIELD;
//         }
//         while (depth_of_field < MAX_DEPTH_OF_FIELD)
//         {
//             mx = (int)rx / MINIMAP_SQUARE_SIDE_LEN;
//             my = (int)ry / MINIMAP_SQUARE_SIDE_LEN;
//             mp = my * MAZE_DIMENSION + mx;
//             if (mp < MAZE_DIMENSION * MAZE_DIMENSION && map[mp] == '1') 
//                 depth_of_field = MAX_DEPTH_OF_FIELD; //Hit the wall
//             else // next line
//             {
//                 rx += xo;
//                 ry += yo;
//                 depth_of_field += 1;
//             }
//         drawLine(game_data->player->x, game_data->player->y, rx, ry, game_data->player->color+100);
//         }
//         r++;
//     }
// }

void raycast(t_game *game_data)
{
    // int direction;
    t_double_pixel *wall;
    wall = NULL;

    uint32_t y = game_data->player->y;
    uint32_t x = game_data->player->x;


    while(game_data->maze.g[y / MINIMAP_SQUARE_SIDE_LEN][x/ MINIMAP_SQUARE_SIDE_LEN] != '1')
    {
        printf("Wall y is %i, wall x is %i\n", y, x);
        y--;
    }
    drawLine(game_data->player->x+1, game_data->player->y, x + 1, y + 2, game_data->player->color); //why y + 2?
    


    // draw vertical and horizontal rays without optimization
    
    // while(game_data->maze.g[y / MINIMAP_SQUARE_SIDE_LEN][x/ MINIMAP_SQUARE_SIDE_LEN] != '1')
    // {
    //     printf("Wall y is %i, wall x is %i\n", y, x);
    //     y--;
    // }
    // drawLine(game_data->player->x+1, game_data->player->y, x + 1, y + 2, game_data->player->color); //why y + 2?
    // y++; //get out of the wall
    // while(game_data->maze.g[y / MINIMAP_SQUARE_SIDE_LEN][x/ MINIMAP_SQUARE_SIDE_LEN] != '1')
    // {
    //     printf("Wall y is %i, wall x is %i\n", y, x);
    //     y++;
    // }
    // drawLine(game_data->player->x+1, game_data->player->y, x + 1, y - 1, game_data->player->color); //why y - 3?
    // y = game_data->player->y; //reset to player
    // while(game_data->maze.g[y / MINIMAP_SQUARE_SIDE_LEN][x/ MINIMAP_SQUARE_SIDE_LEN] != '1')
    // {
    //     printf("Wall y is %i, wall x is %i\n", y, x);
    //     x--;
    // }
    // drawLine(game_data->player->x+1, game_data->player->y+1, x + 1, y+1, game_data->player->color);
    // x = game_data->player->x; //reset to player
    // while(game_data->maze.g[y / MINIMAP_SQUARE_SIDE_LEN][x/ MINIMAP_SQUARE_SIDE_LEN] != '1')
    // {
    //     printf("Wall y is %i, wall x is %i\n", y, x);
    //     x++;
    // }
    // drawLine(game_data->player->x+1, game_data->player->y+1, x -1, y+1, game_data->player->color);
    

}


// void raycast(t_game *game_data)
// {
//     double posX = 22, posY = 12;  //x and y start position
//     double dirX = -1, dirY = 0; //initial direction vector
//     double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

//     double time = 0; //time of current frame
//     double oldTime = 0; //time of previous frame

//     while (1)
//     {
//         for(int x = 0; x < WINDOW_WIDTH; x++)
//         {
//             //calculate ray position and direction
//             double cameraX = 2 * x / (double)WINDOW_WIDTH - 1; //x-coordinate in camera space
//             double rayDirX = dirX + planeX * cameraX;
//             double rayDirY = dirY + planeY * cameraX;
//             //which box of the map we're in
//             int mapX = (int)posX;
//             int mapY = (int)posY;
//              //length of ray from current position to next x or y-side
//             double sideDistX;
//             double sideDistY;

//             //length of ray from one x or y-side to next x or y-side
//             //these are derived as:
//             //deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
//             //deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
//             //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
//             //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
//             //unlike (dirX, dirY) is not 1, however this does not matter, only the
//             //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
//             //stepping further below works. So the values can be computed as below.
//             // Division through zero is prevented, even though technically that's not
//             // needed in C++ with IEEE 754 floating point values.
//             double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//             double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

//             double perpWallDist;
//             //what direction to step in x or y-direction (either +1 or -1)
//             int stepX;
//             int stepY;

//             int hit = 0; //was there a wall hit?
//             int side; //was a NS or a EW wall hit?
//             //calculate step and initial sideDist
//             if(rayDirX < 0)
//             {
//                 stepX = -1;
//                 sideDistX = (posX - mapX) * deltaDistX;
//             }
//             else
//             {
//                 stepX = 1;
//                 sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//             }
//             if(rayDirY < 0)
//             {
//                 stepY = -1;
//                 sideDistY = (posY - mapY) * deltaDistY;
//             }
//             else
//             {
//                 stepY = 1;
//                 sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//             }
//             //perform DDA
//             while(hit == 0)
//             {
//                 //jump to next map square, either in x-direction, or in y-direction
//                 if(sideDistX < sideDistY)
//                 {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//                 }
//                 else
//                 {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//                 }
//                 //Check if ray has hit a wall
//                 if(game_data->maze.g[mapX][mapY] > 0)
//                     hit = 1;
//             }
//              //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
//       //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
//       //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
//       //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
//       //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
//       //steps, but we subtract deltaDist once because one step more into the wall was taken above.
//       if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//       else          perpWallDist = (sideDistY - deltaDistY);

//       //Calculate height of line to draw on screen
//       int lineHeight = (int)(h / perpWallDist);

//       //calculate lowest and highest pixel to fill in current stripe
//       int drawStart = -lineHeight / 2 + h / 2;
//       if(drawStart < 0) drawStart = 0;
//       int drawEnd = lineHeight / 2 + h / 2;
//       if(drawEnd >= h) drawEnd = h - 1;

//       //choose wall color
//       uint32_t color;
//       switch(game_data->maze.g[mapX][mapY])
//       {
//         case 1:  color = 0xFF000000;    break; //red
//         case 2:  color = 0x00FF0000;  break; //green
//         case 3:  color = 0x0000FF00;   break; //blue
//         case 4:  color = 0xFFFFFFFF;  break; //white
//         default: color = 0xFFFF0000; break; //yellow
//       }

//       //give x and y sides different brightness
//       if(side == 1) {color = color / 2;}

//       //draw the pixels of the stripe as a vertical line
//       verLine(x, drawStart, drawEnd, color);
//     }

             
//         }
//     }
// }

// static void raycasting_init(int x, t_game *game_data, t_raycast *ray_data)
// {
//     ray_data->cam = 2 * x / (double)WINDOW_WIDTH - 1;
//     ray_data->ray_x = game_data->player_dir_x + game_data->cam_plane_x * ray_data->cam;
//     ray_data->ray_y = game_data->player_dir_y + game_data->cam_plane_y * ray_data->cam;
//     ray_data->map_x = game_data->pl_pos_x;
//     ray_data->map_y = game_data->pl_pos_y;
//     ray_data->grid_step_dist_x = fabs(1 / ray_data->ray_x);
//     ray_data->grid_step_dist_y = fabs(1 / ray_data->ray_y);

//     if (ray_data->ray_x < 0)
//     {
//         ray_data->step_x = -1;
//         ray_data->side_dist_x = (game_data->pl_pos_x - ray_data->map_x) * ray_data->grid_step_dist_x;
//     }
//     else
//     {
//         ray_data->step_x = 1;
//         ray_data->side_dist_x = (ray_data->map_x + 1.0 - game_data->pl_pos_x) * ray_data->grid_step_dist_x;
//     }

//     if (ray_data->ray_y < 0)
//     {
//         ray_data->step_y = -1;
//         ray_data->side_dist_y = (game_data->pl_pos_y - ray_data->map_y) * ray_data->grid_step_dist_y;
//     }
//     else
//     {
//         ray_data->step_y = 1;
//         ray_data->side_dist_y = (ray_data->map_y + 1.0 - game_data->pl_pos_y) * ray_data->grid_step_dist_y;
//     }
// }

// void	init_structs(t_raycast *ray_data, t_game *game_data)
// {
//     ray_data->cam = 0;
//     ray_data->ray_x = 0;
//     ray_data->ray_y = 0;
//     ray_data->first_intersection_x = 0;
//     ray_data->first_intersection_y = 0;
//     ray_data->grid_step_dist_x = 0;
//     ray_data->grid_step_dist_y = 0;
//     ray_data->map_x = 0;
//     ray_data->map_y = 0;
//     game_data->pl_pos_x = 0;
//     game_data->pl_pos_y = 0;
//     game_data->cam_plane_x = 0;
//     game_data->cam_plane_y = 0;
//     game_data->player_dir_x = 0;
//     game_data->player_dir_y = 0;

// }