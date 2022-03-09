/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:18:57 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/09 15:14:30 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

int	is_point_in_map(t_vars *vars, t_vector2	point)
{
	if (point.y < vars->map->n_lines * SCALE && point.y > 0
		&& point.x < ((vars->map->max_width - 1) * SCALE) && point.x > 0)
		return (1);
	return (0);
}

int	point_iswall(t_vars *vars, double RW_x, double RW_y, t_ray *ray)
{
	char	c;

	c = vars->map->nodes[(int)RW_x / SCALE][(int)RW_y / SCALE];
	if (c > '0')
	{
		ray->hit_char = c;
		return (1);
	}
	return (0);
}

void	draw_wall(t_vars *vars, t_ray *ray, int i)
{
	if (ray->facing_direction == 1)
		draw_tex_line(vars, ray, vars->tex_n, i);
	if (ray->facing_direction == 2)
		draw_tex_line(vars, ray, vars->tex_e, i);
	if (ray->facing_direction == 3)
		draw_tex_line(vars, ray, vars->tex_s, i);
	if (ray->facing_direction == 4)
		draw_tex_line(vars, ray, vars->tex_w, i);
}

void	draw_sun(t_vars *vars, t_ray *ray, int i)
{
	t_vector2_int	pos;
	t_vector2_int	size;
	int				lightest;
	int				middle;

	size.x = 1;
	pos.x = MAIN_IMG_W - i - 1;
	middle = 0xdbedfd;
	lightest = 0xc7e3fd;
	size.y = 115;
	pos.y = 10;
	if (ray->angle > 4.6687557 - ONE_DEG_RAD / 2 \
		&& ray->angle < 4.7560222 + ONE_DEG_RAD / 2)
		draw_square_tlc(vars->main_img, size, pos, lightest);
	size.y = 95;
	pos.y = 20;
	if (ray->angle > 4.6687557 && ray->angle < 4.7560222)
		draw_square_tlc(vars->main_img, size, pos, middle);
	size.y = 75;
	pos.y = 30;
	if (ray->angle > 4.6687557 + ONE_DEG_RAD / 2 \
		&& ray->angle < 4.7560222 - ONE_DEG_RAD / 2)
		draw_square_tlc(vars->main_img, size, pos, 0xffffff);
}
