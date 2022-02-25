#include "../header/cub3d.h"

int	ray_dist(t_vars *vars, double ray_angle)
{
	double	range_rounding = 0.000001;
	int		color = 0x83d0c9;

	double	hor_dx = RW_UNIT / tan(ray_angle);
	double	hor_dy = RW_UNIT;
	double	hor_hit_RW_x = 0;
	double	hor_hit_RW_y = 0;

	double	hor_hit_player_dist_RW = 0;

	double	vert_dx = RW_UNIT;
	double	vert_dy = RW_UNIT * tan(ray_angle);
	double	vert_hit_RW_x = 0;
	double	vert_hit_RW_y = 0;

	double	vert_hit_player_dist_RW = 0;

	int		x_increment_sign = 1;
	int		y_increment_sign = 1;

	vars->facing_direction = 0;

	// HORIZONTAL INIT
	// // 1st quadrant && 2nd quadrant
	if (range_rounding < ray_angle && M_PI - range_rounding > ray_angle) // from 0+ to M_PI- | 90 edge case
	{
		if (ray_angle <= M_PI_2 + range_rounding && ray_angle >= M_PI_2 - range_rounding) // 90 degs edge case for tan
			hor_hit_RW_x = vars->player->RW_x;
		else
			hor_hit_RW_x = vars->player->RW_x + (vars->player->RW_y % RW_UNIT) / tan(ray_angle); // > 0 1st ioct, < 0 2nd oct
		hor_hit_RW_y = vars->player->RW_y - (vars->player->RW_y % RW_UNIT);
		hor_dy *= -1;
		y_increment_sign *= -1;
	}
	// 3rd quadrant && 4th quadrant: 180+ to 0- | 270 edge case
	if ((ray_angle > M_PI + range_rounding && ray_angle < (M_PI * 2) - range_rounding))
	{
		hor_hit_RW_x = vars->player->RW_x - ((RW_UNIT - vars->player->RW_y % RW_UNIT) / tan(ray_angle));
		if (ray_angle >= 3 * M_PI_2 - range_rounding && ray_angle <= 3 * M_PI_2 + range_rounding) // 270 edge case
			hor_hit_RW_x = vars->player->RW_x;
		hor_hit_RW_y = vars->player->RW_y + RW_UNIT - vars->player->RW_y % RW_UNIT;
		hor_dx *= -1;
	}

	// VERTICAL INIT
	// 1st octant && 4th octant + 0degs
	if (M_PI_2 - range_rounding > ray_angle || ray_angle > 3 * M_PI_2 + range_rounding)
	{
		vert_hit_RW_x = vars->player->RW_x + RW_UNIT - (vars->player->RW_x % RW_UNIT);
		vert_hit_RW_y = vars->player->RW_y - (RW_UNIT - (vars->player->RW_x % RW_UNIT)) * tan(ray_angle);
		if (ray_angle <= range_rounding || ray_angle >= (M_PI * 2) - range_rounding)
			vert_hit_RW_y = vars->player->RW_y;
		vert_dy *= -1;
	}
	// 2nd octant && 3rd octant + 180 degs
	if (M_PI_2 + range_rounding < ray_angle && ray_angle < 3 * M_PI_2 - range_rounding)
	{
		vert_hit_RW_x = vars->player->RW_x - (vars->player->RW_x % RW_UNIT);
		vert_hit_RW_y = vars->player->RW_y + (vars->player->RW_x % RW_UNIT) * tan(ray_angle);
		if (ray_angle >= M_PI - range_rounding && ray_angle <= M_PI + range_rounding)
			vert_hit_RW_y = vars->player->RW_y;
		x_increment_sign = -1;
		vert_dx *= -1;
	}

	// all
	if ((hor_hit_RW_x != 0 && hor_hit_RW_y != 0) || (vert_hit_RW_x != 0 && vert_hit_RW_y != 0))
	{
		while ((hor_hit_RW_y < vars->map->n_lines * RW_UNIT && hor_hit_RW_y > 0 && hor_hit_RW_x < (vars->map->max_width - 1) * RW_UNIT && hor_hit_RW_x > 0) // while lines in map basically
			|| (vert_hit_RW_y < vars->map->n_lines * RW_UNIT && vert_hit_RW_y > 0 && vert_hit_RW_x < (vars->map->max_width - 1) * RW_UNIT && vert_hit_RW_x > 0))
		{
			hor_hit_player_dist_RW = (vars->player->RW_y - hor_hit_RW_y) / sin(ray_angle);
			vert_hit_player_dist_RW = (vert_hit_RW_x - vars->player->RW_x) / cos(ray_angle);
			if (hor_hit_player_dist_RW < vert_hit_player_dist_RW)
			{
				if ((hor_hit_RW_y < vars->map->n_lines * RW_UNIT && hor_hit_RW_y > 0 && hor_hit_RW_x < (vars->map->max_width - 1) * RW_UNIT && hor_hit_RW_x > 0)
					&& (vars->map->nodes[((int)hor_hit_RW_y + y_increment_sign * (RW_UNIT / 2)) / RW_UNIT][(int)hor_hit_RW_x / RW_UNIT] == '1'))
				{
					draw_line(vars->minimap->img, \
						vars->player->RW_x * vars->minimap->scale / RW_UNIT, \
						vars->player->RW_y * vars->minimap->scale / RW_UNIT, \
						(int)hor_hit_RW_x * vars->minimap->scale / RW_UNIT, \
						(int)hor_hit_RW_y * vars->minimap->scale / RW_UNIT, color);
					draw_square_tlc(vars->minimap->img, vars->minimap->scale, vars->minimap->scale, \
					((int)hor_hit_RW_x / RW_UNIT) * vars->minimap->scale, \
					(((int)hor_hit_RW_y + y_increment_sign * (RW_UNIT / 2)) / RW_UNIT) * vars->minimap->scale, color);
					printf("HOR DIST: %f %d\n", hor_hit_player_dist_RW, (int)hor_hit_player_dist_RW);
					vars->facing_direction = 1;
					if (ray_angle > M_PI)
						vars->facing_direction = 3;
					return ((int)hor_hit_player_dist_RW);
				}
				hor_hit_RW_x += hor_dx;
				hor_hit_RW_y += hor_dy;
			}
			else
			{
				if ((vert_hit_RW_y < vars->map->n_lines * RW_UNIT && vert_hit_RW_y > 0 && vert_hit_RW_x < (vars->map->max_width - 1) * RW_UNIT && vert_hit_RW_x > 0)
					&& (vars->map->nodes[(int)vert_hit_RW_y / RW_UNIT][((int)vert_hit_RW_x  + x_increment_sign *  (RW_UNIT / 2)) / RW_UNIT] == '1'))
				{
					draw_line(vars->minimap->img, \
						vars->player->RW_x * vars->minimap->scale / RW_UNIT, \
						vars->player->RW_y * vars->minimap->scale / RW_UNIT, \
						(int)vert_hit_RW_x * vars->minimap->scale / RW_UNIT, \
						(int)vert_hit_RW_y * vars->minimap->scale / RW_UNIT, color);
					draw_square_tlc(vars->minimap->img, vars->minimap->scale, vars->minimap->scale, \
					(((int)vert_hit_RW_x  + x_increment_sign * (RW_UNIT / 2)) / RW_UNIT) * vars->minimap->scale, \
					(int)vert_hit_RW_y / RW_UNIT * vars->minimap->scale, color);
					printf("VERT DIST: %f %d\n", vert_hit_player_dist_RW, (int)vert_hit_player_dist_RW);
					vars->facing_direction = 2;
					if (ray_angle > M_PI_2 * 3)
						vars->facing_direction = 4;
					return ((int)vert_hit_player_dist_RW);
				}
				vert_hit_RW_x += vert_dx;
				vert_hit_RW_y += vert_dy;
			}
		}
	}
	// return ((int)hor_hit_player_dist_RW);
	return (1);
}


void	raycast(t_vars *vars)
{
	// double	ray_angle = vars->player->th;
	// ray_dist(vars, ray_angle);
	int dist;
	int prjp_dist;
	double	ray_angle = vars->player->th - (FOV_RAD / 2);
	int i;
	int height;
	int color;

	// background:
	vars->prjp = new_image(vars, PRJP_W, PRJP_H, 20, 20);
	draw_square_tlc(vars->prjp, PRJP_W, PRJP_H, 0, 0, 0x1b2d0d);
	// ceiling
	draw_square_tlc(vars->prjp, PRJP_W, PRJP_H / 2, 0, 0, 0xb8dcfd);

	i = 0;
	while (ray_angle < vars->player->th + (FOV_RAD / 2))
	{
		printf("%d: ", i);
		dist = ray_dist(vars, ray_angle);

		prjp_dist = (int)((PRJP_W / 2) / tan(FOV_RAD / 2));
		printf ("PRJP DIST: %d\n", prjp_dist);
		height = (PRJP_H * 30) / dist;
		// height = (PRJP_H / dist) * prjp_dist;
		if (vars->facing_direction == 1)
			color = 0xc0c5ce;
		if (vars->facing_direction == 2)
			color = 0xa7adba;
		if (vars->facing_direction == 3)
			color = 0x65737e;
		if (vars->facing_direction == 4)
			color = 0xa7adba;
		draw_square_tlc(vars->prjp, ceil(PRJP_W / FOV_DEG), height, \
			i * ceil(PRJP_W / FOV_DEG) , \
			PRJP_H / 2 - height / 2, color);

		ray_angle += FOV_RAD / FOV_DEG;
		i++;
	}
	printf("%d\n", i);
}

