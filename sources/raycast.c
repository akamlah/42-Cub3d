#include "../header/cub3d.h"

int	ray_dist(t_vars *vars, double ray_angle)
{
	double	range_rounding = 0.000001;
	int		color = 0x00ff00;

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
			if (hor_hit_RW_x != 0 && hor_hit_RW_y != 0)
				hor_hit_player_dist_RW = (vars->player->RW_y - hor_hit_RW_y) / sin(ray_angle); // sinus: no need for 90 deg edge case.
				// printf("HOR DIST: %f %d\n", hor_hit_player_dist_RW, (int)hor_hit_player_dist_RW);
			if (vert_hit_RW_x != 0 && vert_hit_RW_y != 0)
				vert_hit_player_dist_RW = (vert_hit_RW_x - vars->player->RW_x) / cos(ray_angle);
				// printf("VERT DIST: %f %d\n", vert_hit_player_dist_RW, (int)vert_hit_player_dist_RW);
			if (hor_hit_player_dist_RW < vert_hit_player_dist_RW && (hor_hit_RW_x != 0 && hor_hit_RW_y != 0))
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
					break ;
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
					break ;
				}
				vert_hit_RW_x += vert_dx;
				vert_hit_RW_y += vert_dy;
			}
		}
	}

	printf("\n");

	// return ((int)hor_hit_player_dist_RW);
	return (1);
}


void	raycast(t_vars *vars)
{
	vars->prjp = new_image(vars, PRJP_W, PRJP_H, 20, 20);

	// double	ray_angle = vars->player->th;
	// ray_dist(vars, ray_angle);

	double	ray_angle = vars->player->th - (FOV_RAD / 2);
	int i = 0;
	while (ray_angle < vars->player->th + (FOV_RAD / 2))
	{
		ray_dist(vars, ray_angle);
		ray_angle += FOV_RAD / FOV_DEG;
		i++;
	}
	printf("%d\n", i);

	draw_square_tlc(vars->prjp, \
	PRJP_W, \
	PRJP_H, \
	0, \
	0, \
	0x808080);

}



	// double first_hor_grid_coll_RW_x = 0;
	// double first_hor_grid_coll_RW_y = 0;
	// edge cases... excluded from drawing
	// around 0
	// if (ray_angle <= range_rounding || ray_angle >= (M_PI * 2) - range_rounding)
	// {
	// 	first_hor_grid_coll_RW_x = (vars->map->max_width - 1) * RW_UNIT;
	// 	first_hor_grid_coll_RW_y = vars->player->RW_y;
	// }

	// // around 180
	// if (ray_angle >= M_PI - range_rounding && ray_angle <= M_PI + range_rounding)
	// {
	// 	first_hor_grid_coll_RW_x = 0;
	// 	first_hor_grid_coll_RW_y = vars->player->RW_y;
	// }


	// if (!(ray_angle >= M_PI - range_rounding && ray_angle <= M_PI + range_rounding) // 180
	// 	&& !(ray_angle <= range_rounding || ray_angle >= (M_PI * 2) - range_rounding)) //0
	// if (hor_side_dx != 0 && hor_side_dy != 0)
	// {
	// 	hor_hit_RW_x = vars->player->RW_x + hor_side_dx;
	// 	hor_hit_RW_y = vars->player->RW_y + hor_side_dy;
	// 	while (hor_hit_RW_y < vars->map->n_lines * RW_UNIT && hor_hit_RW_y > 0 && hor_hit_RW_x < (vars->map->max_width - 1) * RW_UNIT && hor_hit_RW_x > 0) // while lines in map basically
	// 	{
	// 		// draw_line(vars->minimap->img, \
	// 		// 	vars->player->RW_x * vars->minimap->scale / RW_UNIT, \
	// 		// 	vars->player->RW_y * vars->minimap->scale / RW_UNIT, \
	// 		// 	(int)hor_hit_RW_x * vars->minimap->scale / RW_UNIT, \
	// 		// 	(int)hor_hit_RW_y * vars->minimap->scale / RW_UNIT, color);

	// 		// 	printf("%f %f %d %d\n", hor_hit_RW_x / RW_UNIT, \
	// 		// 		(hor_hit_RW_y + y_increment_sign * (RW_UNIT / 2)) / RW_UNIT, \
	// 		// 		(int)hor_hit_RW_x / RW_UNIT, \
	// 		// 		((int)hor_hit_RW_y + y_increment_sign * (RW_UNIT / 2)) / RW_UNIT);

	// 		if (vars->map->nodes[((int)hor_hit_RW_y + y_increment_sign * (RW_UNIT / 2)) / RW_UNIT][(int)hor_hit_RW_x / RW_UNIT] == '1')
	// 		{

	// 			draw_square_tlc(vars->minimap->img, vars->minimap->scale, vars->minimap->scale, \
	// 			((int)hor_hit_RW_x / RW_UNIT) * vars->minimap->scale, \
	// 			(((int)hor_hit_RW_y + y_increment_sign * (RW_UNIT / 2)) / RW_UNIT) * vars->minimap->scale, color);
	// 			// find hit distance.
	// 			hor_hit_player_dist_RW = (vars->player->RW_y - hor_hit_RW_y) / sin(ray_angle); // sinus: no need for 90 deg edge case.
	// 				printf("HOR DIST: %f %d\n", hor_hit_player_dist_RW, (int)hor_hit_player_dist_RW);
	// 			break ;
	// 		}
	// 		hor_hit_RW_x += hor_dx;
	// 		hor_hit_RW_y += hor_dy;
	// 	}
	// }

	// if (vert_side_dx != 0 && vert_side_dy != 0)
	// {
	// 	vert_hit_RW_x = vars->player->RW_x + vert_side_dx;
	// 	vert_hit_RW_y = vars->player->RW_y + vert_side_dy;
	// 	while (vert_hit_RW_y < vars->map->n_lines * RW_UNIT && vert_hit_RW_y > 0 && vert_hit_RW_x < (vars->map->max_width - 1) * RW_UNIT && vert_hit_RW_x > 0)
	// 	{
	// 		// draw_line(vars->minimap->img, \
	// 		// 	vars->player->RW_x * vars->minimap->scale / RW_UNIT, \
	// 		// 	vars->player->RW_y * vars->minimap->scale / RW_UNIT, \
	// 		// 	(int)vert_hit_RW_x * vars->minimap->scale / RW_UNIT, \
	// 		// 	(int)vert_hit_RW_y * vars->minimap->scale / RW_UNIT, color);

	// 		// printf("%f %f %d %d\n", (vert_hit_RW_x + (RW_UNIT / 2)) / RW_UNIT, \
	// 		// 	vert_hit_RW_y / RW_UNIT, \
	// 		// 	(int)((int)vert_hit_RW_x + x_increment_sign * (RW_UNIT / 2)) / RW_UNIT, \
	// 		// 	(int)vert_hit_RW_y / RW_UNIT);

	// 		if (vars->map->nodes[(int)vert_hit_RW_y / RW_UNIT][((int)vert_hit_RW_x  + x_increment_sign *  (RW_UNIT / 2)) / RW_UNIT] == '1')
	// 		{

	// 			draw_square_tlc(vars->minimap->img, vars->minimap->scale, vars->minimap->scale, \
	// 			(((int)vert_hit_RW_x  + x_increment_sign * (RW_UNIT / 2)) / RW_UNIT) * vars->minimap->scale, \
	// 			(int)vert_hit_RW_y / RW_UNIT * vars->minimap->scale, color);

	// 			vert_hit_player_dist_RW = (vert_hit_RW_x - vars->player->RW_x) / cos(ray_angle);
	// 				printf("VERT DIST: %f %d\n", vert_hit_player_dist_RW, (int)vert_hit_player_dist_RW);
	// 			break ;
	// 		}
	// 		vert_hit_RW_x += vert_dx;
	// 		vert_hit_RW_y += vert_dy;
	// 	}
	// }