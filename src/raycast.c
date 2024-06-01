#include "../cub3d.h"

void	ray_orientation(t_raycast *ray, float ray_angle)
{
	ray->is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

void	ray_horiz_calc(t_game *game_data, t_raycast *ray, float ray_angle)
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

int	cast_type(char c, t_casttype type)
{
	if (c == '1' && type == W_WALL)
		return (W_WALL);
	else if (c == 'D' && type == W_DOOR)
		return (W_DOOR);
	else if (c == 'M' && type == W_SPRITE)
		return (W_SPRITE);
	else
		return (W_NONE);
}

void ray_horiz_loop(t_game *game_data, t_raycast *ray, t_casttype type)
{
	int	ray_type;
	int	y;
	int	x;

	while(ray->next_hor_touch_x >= 0 && ray->next_hor_touch_y >= 0
		&& ray->next_hor_touch_y /  game_data->texture_width < MAZE_DIMENSION
		&& ray->next_hor_touch_x /  game_data->texture_width < MAZE_DIMENSION)
	{
		y = (int)ray->next_hor_touch_y / game_data->texture_width;
		x = (int)ray->next_hor_touch_x / game_data->texture_width;
		ray_type = cast_type(game_data->maze.g[y][x], type);
		if (ray_type)
		{
			if (ray_type == W_DOOR)
				ray->door[HOR] = which_door(game_data, y, x);
			if (!(ray_type == W_DOOR && ray->door[HOR]->isopen))
			{
				ray->found_hor_hit = 1;
				ray->hor_wall_hit_x = ray->next_hor_touch_x;
				ray->hor_wall_hit_y = ray->next_hor_touch_y;
			}
			break;
		}
		else
		{
			ray->next_hor_touch_x += ray->xstep;
			ray->next_hor_touch_y += ray->ystep;
		}
	}
}

void ray_vert_calc(t_game *game_data, t_raycast *ray, float ray_angle)
{
	ray->xintercept = floor(game_data->player->x / game_data->texture_width) * game_data->texture_width;
	if (game_data->psycho)
		ray->xintercept = (game_data->player->x / MINIMAP_SQUARE_SIDE_LEN) * MINIMAP_SQUARE_SIDE_LEN;
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

void ray_vert_loop(t_game *game_data, t_raycast *ray, t_casttype type)
{
	int	ray_type;
	int	y;
	int	x;

	while(ray->next_vert_touch_x >= 0 && ray->next_vert_touch_y >= 0
		&& ray->next_vert_touch_y /  game_data->texture_width <= MAZE_DIMENSION
		&& ray->next_vert_touch_x /  game_data->texture_width <= MAZE_DIMENSION)
	{
		y = (int)ray->next_vert_touch_y / game_data->texture_width;
		x = (int)ray->next_vert_touch_x  / game_data->texture_width;
		ray_type = cast_type(game_data->maze.g[y][x], type);
		if (ray_type)
		{
			if (ray_type == W_DOOR)
				ray->door[VERT] = which_door(game_data, y, x);
			if (!(ray_type == W_DOOR && ray->door[VERT]->isopen))
			{
				ray->found_vert_hit = 1;
				ray->vert_wall_hit_x = ray->next_vert_touch_x;
				ray->vert_wall_hit_y = ray->next_vert_touch_y;
			}
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
		ray->distance_hor = FLT_MAX;
	if (ray->found_vert_hit)
		ray->distance_vert = distance_between_points(game_data->player->x, game_data->player->y, ray->vert_wall_hit_x, ray->vert_wall_hit_y);
	else
		ray->distance_vert = FLT_MAX;
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
		ray->door[0] = ray->door[VERT];
	}
	if (ray->distance_vert < ray->distance_hor)
		ray->was_hit_vertical = 1;
}

void	draw_minimap_fov(t_game *game_data, t_raycast ray, t_raycast ray_door)
{
	if (ray.distance > ray_door.distance && ray_door.door[0] && !ray_door.door[0]->isopen)
		drawLine(init_slope_data((uint32_t)game_data->player->x * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)game_data->player->y * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)ray_door.shortest_wall_hit_x * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)ray_door.shortest_wall_hit_y * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width, game_data->img),
				game_data->player->color);
	else
		drawLine(init_slope_data((uint32_t)game_data->player->x * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)game_data->player->y * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)ray.shortest_wall_hit_x * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width,
				(uint32_t)ray.shortest_wall_hit_y * MINIMAP_SQUARE_SIDE_LEN / game_data->texture_width, game_data->img),
				game_data->player->color);
}

void	fill_ray_data(t_game *game_data, int column_id, t_raycast *ray, float ray_angle)
{
	float wall_strip_height;
	float perp_distance;

	perp_distance = ray->distance * cos((ray_angle - game_data->player_angle));
	wall_strip_height  = (game_data->texture_width / perp_distance) * game_data->dist_proj_plane;
	ray->top = (WINDOW_HEIGHT / 2)  - (wall_strip_height / 2);
	ray->bott = (WINDOW_HEIGHT / 2)  + (wall_strip_height / 2);
	ray->height = ray->bott - ray->top;
	ray->img = game_data->img;
	ray->err = ray->height / ray->texture->height;
	ray->column = column_id;
}

void	draw_3d_surface(t_game *game_data, int column_id, t_raycast ray)
{
	drawLine(init_slope_data((uint32_t)column_id, (uint32_t)ray.bott,
			(uint32_t)column_id, (uint32_t)WINDOW_HEIGHT - 1, game_data->img),
			game_data->color[F].rgb_color);
}

static void	wall_texture_calc(t_raycast *ray, t_game *game_data)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_left)
			ray->texture = game_data->textures[WE];
		else if (ray->is_ray_facing_right)
			ray->texture = game_data->textures[EA];
		ray->offSet = (int)ray->vert_wall_hit_y % game_data->texture_width;
	}
	else
	{
		if (ray->is_ray_facing_up)
			ray->texture = game_data->textures[NO];
		else if (ray->is_ray_facing_down)
			ray->texture = game_data->textures[SO];
		ray->offSet = (int)ray->hor_wall_hit_x % game_data->texture_width;
	}
}

void	draw_3d_door(t_game *game_data, int column_id, t_raycast ray, float ray_angle)
{
	ray.texture = game_data->textures[ray.door[0]->texture];
	if (ray.texture == game_data->textures[TEX_DOOR_OP])
		return ;
	if (ray.was_hit_vertical)
		ray.offSet = (int)ray.vert_wall_hit_y % game_data->texture_width;
	else
		ray.offSet = (int)ray.hor_wall_hit_x % game_data->texture_width;
	fill_ray_data(game_data, column_id, &ray, ray_angle);
	if (game_data->psycho)
	{
		ray.offSet = rand() % 1000;
		ray.texture = game_data->textures[TEX_PSY_2];
	}
	if (ray.distance < game_data->z_buffer[column_id])
	{
		draw_textures(ray);
		if (!ray.door[0]->isopen)
			game_data->z_buffer[column_id] = ray.distance;
	}
}

void	draw_3d_projection(t_game *game_data, int column_id, t_raycast ray, float ray_angle)
{
	ray.texture = game_data->textures[TEX_DOOR_OP];
	wall_texture_calc(&ray, game_data);
	fill_ray_data(game_data, column_id, &ray, ray_angle);
	if (game_data->psycho)
	{
		ray.offSet = rand() % 1000;
		ray.texture = game_data->textures[TEX_PSY_1];
		game_data->color[C].rgb_color = ft_float_pixel(227, 61, 148, 255);
		game_data->color[F].rgb_color = ft_float_pixel(130, 94, 9, 255);
	}
	draw_textures(ray);
	draw_3d_surface(game_data, column_id, ray);
}

void	ray_calculations(t_raycast *ray, t_game *game_data, float ray_angle, t_casttype type)
{
	ft_bzero(ray, sizeof(*ray));
	ray_orientation(ray, ray_angle);
	ray_horiz_calc(game_data, ray, ray_angle);
	ray_horiz_loop(game_data, ray, type);
	ray_vert_calc(game_data, ray, ray_angle);
	ray_vert_loop(game_data, ray, type);
	ray_shortest_distance(ray, game_data);
}

void	cast_ray(t_game *game_data, float ray_angle, int column_id)
{
	t_raycast ray;
	t_raycast ray_door;

	ray_calculations(&ray, game_data, ray_angle, W_WALL);
	ray_calculations(&ray_door, game_data, ray_angle, W_DOOR);
	draw_3d_projection(game_data, column_id, ray, ray_angle);
	game_data->z_buffer[column_id] = ray.distance;
	if (ray_door.door[0])
		draw_3d_door(game_data, column_id, ray_door, ray_angle);
	draw_minimap_fov(game_data, ray, ray_door);
}

void	draw_fov(t_game *game_data)
{
	float	ray_angle;
	int		column_id;

	column_id = 0;
	while(column_id < game_data->num_rays)
	{
		game_data->redraw_minimap = 0;
		ray_angle = game_data->player_angle + atan((column_id - game_data->num_rays / 2)
				/ game_data->dist_proj_plane);
		ray_angle = check_angle_overflow(game_data, ray_angle);
		if (column_id < game_data->num_rays)
			cast_ray(game_data, ray_angle, column_id);
		column_id++;
	}
	game_data->redraw_minimap = 1;
}
