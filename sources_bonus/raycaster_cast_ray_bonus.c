/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_cast_ray_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:26:52 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/09 01:23:13 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

/*
	HORIZONTAL INIT
	1st if: 1st quadrant && 2nd quadrant
	2nd if: 3rd quadrant && 4th quadrant: 180+ to 0- | 270 edge case
*/
void	get_first_hor_grid_hit(t_vars *vars, t_ray *ray)
{
	if (0 < ray->angle && M_PI > ray->angle)
	{
		if (ray->angle <= M_PI_2 && ray->angle >= M_PI_2)
			ray->hor_hit.x = vars->player.pos.x;
		else
			ray->hor_hit.x = vars->player.pos.x \
				+ fmod(vars->player.pos.y, SCALE) / tan(ray->angle);
		ray->hor_hit.y = vars->player.pos.y - fmod(vars->player.pos.y, SCALE);
		ray->hor_dy *= -1;
		ray->y_increment_dir *= -1;
	}
	if ((ray->angle > M_PI && ray->angle < (M_PI * 2)))
	{
		ray->hor_hit.x = vars->player.pos.x - ((SCALE \
			- fmod(vars->player.pos.y, SCALE)) / tan(ray->angle));
		if (ray->angle >= 3 * M_PI_2 && ray->angle <= 3 * M_PI_2)
			ray->hor_hit.x = vars->player.pos.x;
		ray->hor_hit.y = vars->player.pos.y + SCALE \
			- fmod(vars->player.pos.y, SCALE);
		ray->hor_dx *= -1;
	}
}

/*
	VERTICAL INIT
	1st if: 1st quadrant && 4th quadrant
	2nd if: 2nd quadrant && 3rd quadrant + 180edge case
*/
void	get_first_vert_grid_hit(t_vars *vars, t_ray *ray)
{
	if (M_PI_2 > ray->angle || ray->angle > 3 * M_PI_2)
	{
		ray->vert_hit.x = vars->player.pos.x + SCALE \
			- fmod(vars->player.pos.x, SCALE);
		ray->vert_hit.y = vars->player.pos.y - (SCALE \
			- fmod(vars->player.pos.x, SCALE)) * tan(ray->angle);
		if (ray->angle < 0 || ray->angle > (M_PI * 2))
			ray->vert_hit.y = vars->player.pos.y;
		ray->vert_dy *= -1;
	}
	if (M_PI_2 < ray->angle && ray->angle < 3 * M_PI_2)
	{
		ray->vert_hit.x = vars->player.pos.x \
			- fmod(vars->player.pos.x, SCALE);
		ray->vert_hit.y = vars->player.pos.y \
			+ fmod(vars->player.pos.x, SCALE) * tan(ray->angle);
		if (ray->angle >= M_PI && ray->angle <= M_PI)
			ray->vert_hit.y = vars->player.pos.y;
		ray->x_increment_dir = -1;
		ray->vert_dx *= -1;
	}
}

int	hit_horizontal_wall(t_vars *vars, t_ray *ray)
{
	if ((is_point_in_map(vars, ray->hor_hit))
		&& (point_iswall(vars, (ray->hor_hit.y + ray->y_increment_dir), \
			ray->hor_hit.x, ray)))
	{
		ray->closest_hit = ray->hor_hit;
		ray->facing_direction = 1;
		if (ray->angle > M_PI)
			ray->facing_direction = 3;
		ray->distance = ray->hor_hit_player_dist;
		return (1);
	}
	return (0);
}

int	hit_vertical_wall(t_vars *vars, t_ray *ray)
{
	if ((is_point_in_map(vars, ray->vert_hit))
		&& (point_iswall(vars, ray->vert_hit.y, ray->vert_hit.x \
			+ ray->x_increment_dir, ray)))
	{
		ray->closest_hit = ray->vert_hit;
		ray->facing_direction = 2;
		if (ray->angle > M_PI_2 * 3 || ray->angle < M_PI_2)
			ray->facing_direction = 4;
		ray->distance = ray->vert_hit_player_dist;
		return (1);
	}
	return (0);
}

void	cast_ray(t_vars *vars, t_ray *ray)
{
	ray_set_vars_to_start(ray);
	get_first_hor_grid_hit(vars, ray);
	get_first_vert_grid_hit(vars, ray);
	while (is_point_in_map(vars, ray->hor_hit)
		|| is_point_in_map(vars, ray->vert_hit))
	{
		ray->hor_hit_player_dist = (vars->player.pos.y - ray->hor_hit.y) \
			/ sin(ray->angle);
		ray->vert_hit_player_dist = (ray->vert_hit.x - vars->player.pos.x) \
			/ cos(ray->angle);
		if (ray->hor_hit_player_dist < ray->vert_hit_player_dist)
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
