#include "../cub3d.h"

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2-x1) * (x2 - x1) + (y2-y1) * (y2 - y1)));
}

int is_ray_facing_down(float ray_angle)
{
	return (ray_angle > 0 && ray_angle < M_PI);
}

int is_ray_facing_right(float ray_angle)
{
	return (ray_angle < M_PI * 0.5 || ray_angle > M_PI * 1.5);
}

int is_ray_facing_up(float ray_angle)
{
	return (!is_ray_facing_down(ray_angle));
}

int is_ray_facing_left(float ray_angle)
{
	return (!is_ray_facing_right(ray_angle));
}
