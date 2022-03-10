/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:18:57 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/09 01:09:06 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

int	is_point_in_map(t_vars *vars, t_vector2	point)
{
	if (point.y < vars->map->n_lines * SCALE && point.y > 0
		&& point.x < ((vars->map->max_width - 1) * SCALE) && point.x > 0)
		return (1);
	return (0);
}

int	point_iswall(t_vars *vars, double RW_x, double RW_y, t_ray *ray)
{
	char	mapchar;

	mapchar = vars->map->nodes[(int)RW_x / SCALE][(int)RW_y / SCALE];
	if (mapchar > '0')
	{
		ray->hit_char = mapchar;
		if (vars->player.action_set == 1)
		{
			if (ray->hit_char == DOOR_OPEN)
				vars->map->nodes[(int)RW_x / SCALE]
				[(int)RW_y / SCALE] = DOOR_CLOSED;
			else if (ray->hit_char == DOOR_CLOSED)
				vars->map->nodes[(int)RW_x / SCALE]
				[(int)RW_y / SCALE] = DOOR_OPEN;
			vars->player.action_set = -1;
		}
		if (mapchar != DOOR_OPEN)
			return (1);
	}
	return (0);
}

void	draw_wall(t_vars *vars, t_ray *ray, int i)
{
	if (ray->facing_direction == 1)
		draw_tex_line(vars, ray, vars->tex_N, i);
	if (ray->facing_direction == 2)
		draw_tex_line(vars, ray, vars->tex_E, i);
	if (ray->facing_direction == 3)
		draw_tex_line(vars, ray, vars->tex_S, i);
	if (ray->facing_direction == 4)
		draw_tex_line(vars, ray, vars->tex_W, i);
}

void	draw_sun(t_vars *vars, t_ray *ray, int i)
{
	t_vector2		pos;
	t_vector2		size;
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
