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
    ray->yintercept = floor(game_data->player->y / game_data->texture_width) * game_data->texture_width;
    // swap this to get pshycodelic effect
    // ray->yintercept = (game_data->player->y / MINIMAP_SQUARE_SIDE_LEN) * MINIMAP_SQUARE_SIDE_LEN;
    if (ray->is_ray_facing_down)
        ray->yintercept += ray->is_ray_facing_down * game_data->texture_width;
    ray->xintercept = game_data->player->x + (ray->yintercept - game_data->player->y) / tan(ray_angle);
    //Ystep
    ray->ystep = game_data->texture_width;

    if (ray->is_ray_facing_up)   //invert if facing up
        ray->ystep *= ray->is_ray_facing_up * -1;
    //Xstep
    ray->xstep = game_data->texture_width / tan(ray_angle);
    if (ray->is_ray_facing_right)
        ray->xstep = game_data->texture_width / tan(ray_angle);
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

int	is_wall(char c, bool wall)
{
	if (c == '1' && wall == true)
		return (W_WALL);
	else if (c == 'D' && wall == false)
		return (W_DOOR);
	else
		return (W_NONE);
}

void ray_horiz_loop(t_game *game_data, t_raycast *ray, bool wall)
{
	int	wall_type;
	int	y;
	int	x;

    while(ray->next_hor_touch_x >= 0 && ray->next_hor_touch_y >= 0
        && ray->next_hor_touch_y /  game_data->texture_width < MAZE_DIMENSION
        && ray->next_hor_touch_x /  game_data->texture_width < MAZE_DIMENSION)
    {
		y = (int)ray->next_hor_touch_y / game_data->texture_width;
		x = (int)ray->next_hor_touch_x / game_data->texture_width;
		wall_type = is_wall(game_data->maze.g[y][x], wall);
        if (wall_type)
        {
            ray->found_hor_hit = 1;
            ray->hor_wall_hit_x = ray->next_hor_touch_x;
            ray->hor_wall_hit_y = ray->next_hor_touch_y;
			if (wall_type == W_DOOR)
				ray->door = which_door(game_data, y, x);
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
    ray->xintercept = floor(game_data->player->x / game_data->texture_width) * game_data->texture_width;
    // swap this to get pshycodelic effect
    // ray->xintercept = (game_data->player->x / MINIMAP_SQUARE_SIDE_LEN) * MINIMAP_SQUARE_SIDE_LEN;
    if (ray->is_ray_facing_right)
        ray->xintercept += ray->is_ray_facing_right * game_data->texture_width; // add 1 extra square if ray is pointing down

    ray->yintercept = game_data->player->y + (ray->xintercept - game_data->player->x) * tan(ray_angle);
    //Xstep
    ray->xstep = game_data->texture_width;
    if (ray->is_ray_facing_left)
        ray->xstep *= ray->is_ray_facing_left * -1;
    //Ystep
    ray->ystep = game_data->texture_width * tan(ray_angle);
    if (ray->is_ray_facing_up && ray->ystep > 0)
        ray->ystep *= -1;
    if (ray->is_ray_facing_down && ray->ystep < 0)
        ray->ystep *= -1;

    ray->next_vert_touch_x = ray->xintercept;
    ray->next_vert_touch_y = ray->yintercept;
    if (ray->is_ray_facing_left)
        ray->next_vert_touch_x--;
}

void ray_vert_loop(t_game *game_data, t_raycast *ray, bool wall)
{
	int	wall_type;
	int	y;
	int	x;

    while(ray->next_vert_touch_x >= 0 && ray->next_vert_touch_y >= 0
        && ray->next_vert_touch_y /  game_data->texture_width <= MAZE_DIMENSION
        && ray->next_vert_touch_x /  game_data->texture_width <= MAZE_DIMENSION)
    {
		y = (int)ray->next_vert_touch_y / game_data->texture_width;
		x = (int)ray->next_vert_touch_x  / game_data->texture_width;
		wall_type = is_wall(game_data->maze.g[y][x], wall);
        if (wall_type)
        {
            ray->found_vert_hit = 1;
            ray->vert_wall_hit_x = ray->next_vert_touch_x;
            ray->vert_wall_hit_y = ray->next_vert_touch_y;
			if (wall_type == W_DOOR)
				ray->door = which_door(game_data, y, x);
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
    if (ray->distance_vert <= ray->distance_hor)
        ray->was_hit_vertical = 1;
}

// TODO: needs to be split up in logical norminette-sized functions
// TODO: potential bug with x and y offset (diagonal lines are empty) - need to check if this affects 3d game projection
void    draw_minimap_fov(t_game *game_data, t_raycast *ray)
{
    drawLine((uint32_t)game_data->player->x * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
            (uint32_t)game_data->player->y * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
            (uint32_t)ray->shortest_wall_hit_x * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
            (uint32_t)ray->shortest_wall_hit_y * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
            game_data->player->color);
}

void    draw_3d_door(t_game *game_data, int column_id, t_raycast ray, double ray_angle, t_raycast ray_wall)
{
    double wall_strip_height;
    double wall_top_pixel;
    double perp_distance;
	double wall_bott_pixel;

    perp_distance = ray.distance * cos((ray_angle - game_data->player_angle));
    wall_strip_height  = (game_data->texture_width / perp_distance) * game_data->dist_proj_plane;
    wall_top_pixel = (WINDOW_HEIGHT / 2)  - (wall_strip_height / 2);
    wall_bott_pixel = (WINDOW_HEIGHT / 2)  + (wall_strip_height / 2);
    int texture_offset_x;
	mlx_texture_t	*texture;
	texture = game_data->textures[ray.door->texture];
	if (texture == game_data->textures[TEX_DOOR_OP])
		return ;
    if (ray.was_hit_vertical)
		texture_offset_x = (int)ray.vert_wall_hit_y % game_data->texture_width;
	else
		texture_offset_x = (int)ray.hor_wall_hit_x % game_data->texture_width;
	if (ray.distance < ray_wall.distance)
	{
		draw_textures(texture, column_id, wall_top_pixel,
						wall_bott_pixel, texture_offset_x);
		if (!ray.door->isopen)
			game_data->z_buffer[column_id] = ray.distance;
	}
}

void    draw_3d_projection(t_game *game_data, int column_id, t_raycast *ray, double ray_angle)
{
    double wall_strip_height;
    double wall_top_pixel;
    double perp_distance;
	double wall_bott_pixel;

    // game_data->dist_proj_plane = (WINDOW_WIDTH / 2)/ tan(game_data->fov_angle / 2);
    perp_distance = ray->distance * cos((ray_angle - game_data->player_angle)); // calculate ray.angle
    wall_strip_height  = (game_data->texture_width / perp_distance) * game_data->dist_proj_plane;
    wall_top_pixel = (WINDOW_HEIGHT / 2)  - (wall_strip_height / 2);
    // if (wall_top_pixel < 0)
    //     wall_top_pixel = 0; // ??
    wall_bott_pixel = (WINDOW_HEIGHT / 2)  + (wall_strip_height / 2);
    // if (wall_bott_pixel > WINDOW_HEIGHT)
    //     wall_bott_pixel = WINDOW_HEIGHT - 1; // ??

    // X offset for finding where on the cube you should start drawing a texture
    // each square is MINIMAP_SQUARE_SIDE_LEN long, texture_offset_X tells you how many pixels
    // you have to offset on each particular tile tto start drawing textures
    // texture_offset_x is NOT column_id, column_id is a value of FOV
    // FOV has column_id * WINDOW_WIDTH, this is all the visible range in X
    //
	/* Texture calculation for every colon: texture can be for the wall oder
		for the door */
    int texture_offset_x;
	mlx_texture_t	*texture_wall;
	texture_wall = game_data->textures[TEX_DOOR_OP];
    if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_left)
			texture_wall = game_data->textures[WE]; //temp
		else if (ray->is_ray_facing_right)
			texture_wall = game_data->textures[EA];
        texture_offset_x = (int)ray->vert_wall_hit_y % game_data->texture_width;
	}
    else
	{
		if (ray->is_ray_facing_up)
			texture_wall = game_data->textures[NO]; //temp
		else if (ray->is_ray_facing_down)
			texture_wall = game_data->textures[SO];
        texture_offset_x = (int)ray->hor_wall_hit_x % game_data->texture_width;
	}
	//draw walls
    draw_textures(texture_wall, column_id, wall_top_pixel,
					wall_bott_pixel, texture_offset_x);
	//draw floor
    drawLine((uint32_t)column_id, (uint32_t)wall_bott_pixel,
            (uint32_t)column_id, (uint32_t)WINDOW_HEIGHT-1,
            game_data->color[F].rgb_color);
    //draw celing
    drawLine((uint32_t)column_id, (uint32_t)wall_top_pixel,
            (uint32_t)column_id, (uint32_t)0,
            game_data->color[C].rgb_color);
	//drawing sprites
	// draw_sprites(game_data);
}

void	ray_calculations(t_raycast *ray, t_game *game_data, double ray_angle, bool wall)
{
	ft_bzero(ray, sizeof(*ray));
	ray_orientation(ray, ray_angle);
	ray_horiz_calc(game_data, ray, ray_angle);
	ray_horiz_loop(game_data, ray, wall);
	ray_vert_calc(game_data, ray, ray_angle);
	ray_vert_loop(game_data, ray, wall);
	ray_shortest_distance(ray, game_data);
}

void    cast_ray(t_game *game_data, double ray_angle, int column_id)
{
    t_raycast ray;
	t_raycast ray_door;

	ray_calculations(&ray, game_data, ray_angle, true);
	ray_calculations(&ray_door, game_data, ray_angle, false);
	draw_minimap_fov(game_data, &ray);
	draw_3d_projection(game_data, column_id, &ray, ray_angle);
	game_data->z_buffer[column_id] = ray.distance;
	if (ray_door.door)
		draw_3d_door(game_data,column_id,ray_door, ray_angle, ray);
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
    // unsigned int    column_id;
    double          ray_angle;
    int             column_id;
    // double          dist_proj_plane;

    // dist_proj_plane = (WINDOW_WIDTH / 2) / tan(game_data->fov_angle / 2);
    // uncomment this line to get a psychodelic effect
    // dist_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);


    // i = 0;
    column_id = 0;

    ray_angle = game_data->player_angle - (game_data->fov_angle/2);


    while(column_id < game_data->num_rays)
    {
        game_data->redraw_minimap = 0;
        ray_angle += game_data->fov_angle / game_data->num_rays;
        // ray_angle = game_data->player_angle + atan(((column_id - game_data->num_rays) / 2) / game_data->dist_proj_plane);

        ray_angle = game_data->player_angle + atan((column_id - game_data->num_rays / 2) / game_data->dist_proj_plane);

        ray_angle = check_angle_overflow(game_data, ray_angle);
		if (column_id < game_data->num_rays)
       		cast_ray(game_data, ray_angle, column_id);
        column_id++;
    }
    game_data->redraw_minimap = 1;
}
