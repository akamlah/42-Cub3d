#include "../header/cub3d.h"

int	point_is_in_map_RW(t_vars *vars, double RW_x, double RW_y)
{
	if (RW_y < vars->map->n_lines * vars->scale && RW_y > 0 
		&& RW_x < ((vars->map->max_width - 1) * vars->scale) && RW_x > 0)
		return (1);
	return (0);
}

int	is_wall_RW(t_vars *vars, double RW_x, double RW_y)
{
	if (vars->map->nodes[(int)RW_x / vars->scale][(int)RW_y / vars->scale] == '1')
		return (1);
	return (0);
}

void	ray_set_vars_to_start(t_vars *vars, t_ray *ray)
{
	ray->hor_dx = vars->scale / tan(ray->angle);
	ray->hor_dy = vars->scale;
	ray->vert_dx = vars->scale;
	ray->vert_dy = vars->scale * tan(ray->angle);
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
	ray_set_vars_to_start(vars, ray);
}



double	ray_dist(t_vars *vars, t_ray *ray)
{

	ray_set_vars_to_start(vars, ray);

	// HORIZONTAL INIT
	// // 1st quadrant && 2nd quadrant
	if (0 < ray->angle && M_PI > ray->angle) // from 0+ to M_PI- | 90 edge case
	{
		if (ray->angle <= M_PI_2 && ray->angle >= M_PI_2) // 90 degs edge case for tan
			ray->hor_hit.x = vars->player.pos.x;
		else
			ray->hor_hit.x = vars->player.pos.x + fmod(vars->player.pos.y, vars->scale) / tan(ray->angle); // > 0 1st ioct, < 0 2nd oct
		ray->hor_hit.y = vars->player.pos.y - fmod(vars->player.pos.y, vars->scale);
		ray->hor_dy *= -1;
		ray->y_increment_dir *= -1;
	}
	// 3rd quadrant && 4th quadrant: 180+ to 0- | 270 edge case
	if ((ray->angle > M_PI && ray->angle < (M_PI * 2)))
	{
		ray->hor_hit.x = vars->player.pos.x - ((vars->scale - fmod(vars->player.pos.y, vars->scale)) / tan(ray->angle));
		if (ray->angle >= 3 * M_PI_2 && ray->angle <= 3 * M_PI_2) // 270 edge case
			ray->hor_hit.x = vars->player.pos.x;
		ray->hor_hit.y = vars->player.pos.y + vars->scale - fmod(vars->player.pos.y, vars->scale);
		ray->hor_dx *= -1;
	}

	// VERTICAL INIT
	// 1st octant && 4th octantdegs
	if (M_PI_2 > ray->angle || ray->angle > 3 * M_PI_2)
	{
		ray->vert_hit.x = vars->player.pos.x + vars->scale - fmod(vars->player.pos.x, vars->scale);
		ray->vert_hit.y = vars->player.pos.y - (vars->scale - fmod(vars->player.pos.x, vars->scale)) * tan(ray->angle);
		if (ray->angle < 0 || ray->angle > (M_PI * 2))
			ray->vert_hit.y = vars->player.pos.y;
		ray->vert_dy *= -1;
	}
	// 2nd octant && 3rd octant + 180 degs
	if (M_PI_2 < ray->angle && ray->angle < 3 * M_PI_2)
	{
		ray->vert_hit.x = vars->player.pos.x - fmod(vars->player.pos.x, vars->scale);
		ray->vert_hit.y = vars->player.pos.y + fmod(vars->player.pos.x, vars->scale) * tan(ray->angle);
		if (ray->angle >= M_PI && ray->angle <= M_PI)
			ray->vert_hit.y = vars->player.pos.y;
		ray->x_increment_dir = -1;
		ray->vert_dx *= -1;
	}

	while (point_is_in_map_RW(vars, ray->hor_hit.x, ray->hor_hit.y)
		|| point_is_in_map_RW(vars, ray->vert_hit.x, ray->vert_hit.y))
	{
		ray->hor_hit_player_dist_RW = (vars->player.pos.y - ray->hor_hit.y) / sin(ray->angle);
		ray->vert_hit_player_dist_RW = (ray->vert_hit.x - vars->player.pos.x) / cos(ray->angle);
		if (ray->hor_hit_player_dist_RW < ray->vert_hit_player_dist_RW)
		{
			// shorter code:
			// hit == hor hit, else hit = vert hit and then perform checks and return only once for the found hit.
			if ((point_is_in_map_RW(vars, ray->hor_hit.x, ray->hor_hit.y))
				&& (is_wall_RW(vars, (ray->hor_hit.y + ray->y_increment_dir), ray->hor_hit.x)))
			{
				draw_line(vars->mlx_vars->minimap, \
					vars->player.pos.x * vars->minimap.scale / vars->scale, \
					vars->player.pos.y * vars->minimap.scale / vars->scale, \
					(int)ray->hor_hit.x * vars->minimap.scale / vars->scale, \
					(int)ray->hor_hit.y * vars->minimap.scale / vars->scale, ray->color_minimap);
				// draw_square_tlc(vars->mlx_vars->minimap, vars->minimap.scale, vars->minimap.scale, \
				// ((int)ray->hor_hit.x / vars->scale) * vars->minimap.scale, \
				// (((int)ray->hor_hit.y + ray->y_increment_dir * (vars->scale / 2)) / vars->scale) * vars->minimap.scale, 0x00ff00);

				ray->facing_direction = 1;
				if (ray->angle > M_PI)
					ray->facing_direction = 3;


				return (ray->hor_hit_player_dist_RW);
			}
			ray->hor_hit.x += ray->hor_dx;
			ray->hor_hit.y += ray->hor_dy;
		}
		else
		{
			if ((point_is_in_map_RW(vars, ray->vert_hit.x, ray->vert_hit.y))
				&& (is_wall_RW(vars, ray->vert_hit.y, ray->vert_hit.x + ray->x_increment_dir)))
			{
				draw_line(vars->mlx_vars->minimap, \
					vars->player.pos.x * vars->minimap.scale / vars->scale, \
					vars->player.pos.y * vars->minimap.scale / vars->scale, \
					(int)ray->vert_hit.x * vars->minimap.scale / vars->scale, \
					(int)ray->vert_hit.y * vars->minimap.scale / vars->scale, ray->color_minimap);
				// draw_square_tlc(vars->mlx_vars->minimap, vars->minimap.scale, vars->minimap.scale, \
				// (((int)ray->vert_hit.x  + ray->x_increment_dir * (vars->scale / 2)) / vars->scale) * vars->minimap.scale, \
				// (int)ray->vert_hit.y / vars->scale * vars->minimap.scale, 0xffff00);

				ray->facing_direction = 2;
				if (ray->angle > M_PI_2 * 3 || ray->angle < M_PI_2)
					ray->facing_direction = 4;
				return (ray->vert_hit_player_dist_RW);
			}
			ray->vert_hit.x += ray->vert_dx;
			ray->vert_hit.y += ray->vert_dy;
		}
	}


	return (0);
}


void	raycast(t_vars *vars)
{
	double dist;
	int prjp_dist;
	int i;
	int height;
	int color;
	t_ray ray;

	// background:

	draw_square_tlc(vars->main_img, PRJP_W, PRJP_H / 2, 0, PRJP_H / 2, 0x1b2d0d); // floor
	draw_square_tlc(vars->main_img, PRJP_W, PRJP_H / 2, 0, 0, 0xb8dcfd);	// ceiling

	setup_first_ray(vars, &ray);


	double increment = FOV_RAD / PRJP_W;

	// double	ray->angle = vars->player.angle;
	// dist = ray_dist(vars, ray->angle);
	i = 0;
	while (i < PRJP_W)
	{
		// printf("%d: ", i);
		dist = ray_dist(vars, &ray);

	if (dist == 0)
		dist = 64;
		height = (PRJP_H * 30) / dist;
	if (height >= PRJP_H - 2)
		height = PRJP_H - 2;

		dist *= cos(((increment * i)));

		prjp_dist = (int)((PRJP_W / 2) / tan(FOV_RAD / 2));
		// printf ("PRJP DIST: %d\n", prjp_dist);
		// height = (PRJP_H / dist) * prjp_dist;
		if (ray.facing_direction == 1)
			color = 0x6bf3fc; // light blue -> from N
		if (ray.facing_direction == 2)
			color = 0x9a2462; // purple -> from W
		if (ray.facing_direction == 3)
			color = 0x0098ff; // darker blue -> from S
		if (ray.facing_direction == 4)
			color = 0xe0bb1b; // yellow -> from EASt
		// test 
		if (dist == 0)
		{
			height = 20;
			color = 0x00ff00;
		}
		draw_square_tlc(vars->main_img, 1, height, \
			PRJP_W - i -1, \
			PRJP_H / 2 - height / 2, color);
		// draw_line(vars->main_img, i, PRJP_H / 2 + height / 2, i, PRJP_H / 2 - height / 2, color); // SIGSEGs near walls!


		// TEXTURE
		


		if (ray.angle + increment > M_PI * 2)
			ray.angle = -1 * ((M_PI * 2) - ray.angle + increment);
		else 
			ray.angle += increment;
		i++;
		//printf("player: %f , ray: %f\n", vars->player.angle, ray.angle);
	}
	// printf("%d\n", i);
}

