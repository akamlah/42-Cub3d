#include "../header/cub3d.h"

int	is_point_in_map(t_vars *vars, t_vector2	point)
{
	if (point.y < vars->map->n_lines * SCALE && point.y > 0 
		&& point.x < ((vars->map->max_width - 1) * SCALE) && point.x > 0)
		return (1);
	return (0);
}

int	is_wall_RW(t_vars *vars, double RW_x, double RW_y)
{
	if (vars->map->nodes[(int)RW_x / SCALE][(int)RW_y / SCALE] == '1')
		return (1);
	return (0);
}

void	ray_set_vars_to_start(t_ray *ray)
{
	ray->hor_dx = SCALE / tan(ray->angle);
	ray->hor_dy = SCALE;
	ray->vert_dx = SCALE;
	ray->vert_dy = SCALE * tan(ray->angle);
	ray->hor_hit.x = 0;
	ray->hor_hit.y = 0;
	ray->vert_hit.x = 0;
	ray->vert_hit.y = 0;
	ray->x_increment_dir = 1;
	ray->y_increment_dir = 1;
	ray->facing_direction = 0;
	ray->hor_hit_player_dist_RW = 0;
	ray->vert_hit_player_dist_RW = 0;
}

void	setup_first_ray(t_vars *vars, t_ray *ray)
{
	// init angle:
	ray->angle = vars->player.angle - (FOV_RAD / 2);
	if (ray->angle < 0)
		ray->angle = (M_PI * 2) + ray->angle;
	ray->color_minimap = 0x83d0c9;
	ray_set_vars_to_start(ray);
}

// HORIZONTAL INIT
void	get_first_hor_grid_hit(t_vars *vars, t_ray *ray)
{
	// // 1st quadrant && 2nd quadrant
	if (0 < ray->angle && M_PI > ray->angle) // from 0+ to M_PI- | 90 edge case
	{
		if (ray->angle <= M_PI_2 && ray->angle >= M_PI_2) // 90 degs edge case for tan
			ray->hor_hit.x = vars->player.pos.x;
		else
			ray->hor_hit.x = vars->player.pos.x + fmod(vars->player.pos.y, SCALE) / tan(ray->angle); // > 0 1st ioct, < 0 2nd oct
		ray->hor_hit.y = vars->player.pos.y - fmod(vars->player.pos.y, SCALE);
		ray->hor_dy *= -1;
		ray->y_increment_dir *= -1;
	}
	// 3rd quadrant && 4th quadrant: 180+ to 0- | 270 edge case
	if ((ray->angle > M_PI && ray->angle < (M_PI * 2)))
	{
		ray->hor_hit.x = vars->player.pos.x - ((SCALE - fmod(vars->player.pos.y, SCALE)) / tan(ray->angle));
		if (ray->angle >= 3 * M_PI_2 && ray->angle <= 3 * M_PI_2) // 270 edge case
			ray->hor_hit.x = vars->player.pos.x;
		ray->hor_hit.y = vars->player.pos.y + SCALE - fmod(vars->player.pos.y, SCALE);
		ray->hor_dx *= -1;
	}
}

// VERTICAL INIT
void	get_first_vert_grid_hit(t_vars *vars, t_ray *ray)
{
	// 1st octant && 4th octantdegs
	if (M_PI_2 > ray->angle || ray->angle > 3 * M_PI_2)
	{
		ray->vert_hit.x = vars->player.pos.x + SCALE - fmod(vars->player.pos.x, SCALE);
		ray->vert_hit.y = vars->player.pos.y - (SCALE - fmod(vars->player.pos.x, SCALE)) * tan(ray->angle);
		if (ray->angle < 0 || ray->angle > (M_PI * 2))
			ray->vert_hit.y = vars->player.pos.y;
		ray->vert_dy *= -1;
	}
	// 2nd octant && 3rd octant + 180 degs
	if (M_PI_2 < ray->angle && ray->angle < 3 * M_PI_2)
	{
		ray->vert_hit.x = vars->player.pos.x - fmod(vars->player.pos.x, SCALE);
		ray->vert_hit.y = vars->player.pos.y + fmod(vars->player.pos.x, SCALE) * tan(ray->angle);
		if (ray->angle >= M_PI && ray->angle <= M_PI)
			ray->vert_hit.y = vars->player.pos.y;
		ray->x_increment_dir = -1;
		ray->vert_dx *= -1;
	}	
}

void	draw_ray_minimap(t_vars *vars, t_ray *ray)
{
	draw_line(vars->mlx_vars->minimap, \
		vars->player.pos.x * vars->minimap.scale / SCALE, \
		vars->player.pos.y * vars->minimap.scale / SCALE, \
		(int)ray->closest_hit.x * vars->minimap.scale / SCALE, \
		(int)ray->closest_hit.y * vars->minimap.scale / SCALE, ray->color_minimap);
}
int	hit_horizontal_wall(t_vars *vars, t_ray *ray)
{
	if ((is_point_in_map(vars, ray->hor_hit))
		&& (is_wall_RW(vars, (ray->hor_hit.y + ray->y_increment_dir), ray->hor_hit.x)))
	{
		ray->closest_hit = ray->hor_hit;
		draw_ray_minimap(vars, ray);
		ray->facing_direction = 1;
		if (ray->angle > M_PI)
			ray->facing_direction = 3;
		ray->distance = ray->hor_hit_player_dist_RW;
		return (1);
	}
	return (0);
}

int	hit_vertical_wall(t_vars *vars, t_ray *ray)
{
	if ((is_point_in_map(vars, ray->vert_hit)) 
		&& (is_wall_RW(vars, ray->vert_hit.y, ray->vert_hit.x + ray->x_increment_dir)))
	{
		ray->closest_hit = ray->vert_hit;
		draw_ray_minimap(vars, ray);
		ray->facing_direction = 2;
		if (ray->angle > M_PI_2 * 3 || ray->angle < M_PI_2)
			ray->facing_direction = 4;
		ray->distance = ray->vert_hit_player_dist_RW;
		return (1);
	}
	return (0);
}

void	cast_ray(t_vars *vars, t_ray *ray)
{
	ray_set_vars_to_start(ray);
	get_first_hor_grid_hit(vars, ray);
	get_first_vert_grid_hit(vars, ray);
	while (is_point_in_map(vars, ray->hor_hit) || is_point_in_map(vars, ray->vert_hit))
	{
		ray->hor_hit_player_dist_RW = (vars->player.pos.y - ray->hor_hit.y) / sin(ray->angle);
		ray->vert_hit_player_dist_RW = (ray->vert_hit.x - vars->player.pos.x) / cos(ray->angle);
		if (ray->hor_hit_player_dist_RW < ray->vert_hit_player_dist_RW)
		{
			if (hit_horizontal_wall(vars, ray))
				return ;
			ray->hor_hit.x += ray->hor_dx;
			ray->hor_hit.y += ray->hor_dy;
		}
		else
		{
			if (hit_vertical_wall(vars, ray))
				return ;
			ray->vert_hit.x += ray->vert_dx;
			ray->vert_hit.y += ray->vert_dy;
		}
	}
}

/*
	calculates the height of the wall to be drawn
	consigering fisheye effect and player collision with wall.
*/
void	get_height(t_vars *vars, t_ray *ray)
{
	// silence warnings
	t_vars *yo = vars;
	yo = NULL;

	if (ray->distance == 0)
		ray->distance = 64;
		ray->wall_height = (MAIN_IMG_H * 30) / ray->distance;
	if (ray->wall_height >= MAIN_IMG_H - 2)
		ray->wall_height = MAIN_IMG_H - 2;

	// ray->distance *= cos(((RAY_ANG_INCREMENT * i)));
}


void	increment_ray_angle(t_vars *vars, t_ray *ray)
{
	// silence warnings
	t_vars *yo = vars;
	yo = NULL;

	if (ray->angle + RAY_ANG_INCREMENT > M_PI * 2)
		ray->angle = -1 * ((M_PI * 2) - ray->angle + RAY_ANG_INCREMENT);
	else 
		ray->angle += RAY_ANG_INCREMENT;
}

void	draw_wall(t_vars *vars, t_ray *ray, int i)
{
	// int color;
	// if (ray->facing_direction == 1)
	// 	color = 0x6bf3fc; // light blue -> from N
	// if (ray->facing_direction == 2)
	// 	color = 0x9a2462; // purple -> from W
	// if (ray->facing_direction == 3)
	// 	color = 0x0098ff; // darker blue -> from S
	// if (ray->facing_direction == 4)
	// 	color = 0xe0bb1b; // yellow -> from EASt
	// color = 0xffffff;

	draw_tex_line(vars, ray, ray->wall_height, vars->tex_N, i);
	// draw_square_tlc(vars->main_img, 1, ray->wall_height, \
	// 	MAIN_IMG_W - i -1, \
	// 	MAIN_IMG_H / 2 - ray->wall_height / 2, color);
	// draw_line(vars->main_img, i, MAIN_IMG_H / 2 + ray->wall_height / 2, i, MAIN_IMG_H / 2 - ray->wall_height / 2, color); // SIGSEGs near walls!
}


void	raycast(t_vars *vars)
{
	t_ray ray;
	int i;

	i = 0;
	setup_first_ray(vars, &ray);
	while (i < MAIN_IMG_W)
	{
		cast_ray(vars, &ray);
		get_height(vars, &ray);
		draw_wall(vars, &ray, i);
		increment_ray_angle(vars, &ray);
		// i += 2;
		i++;
		// i += 4;
	}
}

