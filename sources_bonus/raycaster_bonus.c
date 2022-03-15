/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:29:56 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/15 11:53:56 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

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
	ray->hor_hit_player_dist = 0;
	ray->vert_hit_player_dist = 0;
	ray->hit_char = 0;
}

void	setup_first_ray(t_vars *vars, t_ray *ray)
{
	ray->angle = vars->player.angle - (FOV_RAD / 2);
	if (ray->angle < 0)
		ray->angle = (M_PI * 2) + ray->angle;
	ray_set_vars_to_start(ray);
}

void	increment_ray_angle(t_vars *vars, t_ray *ray)
{
	if (ray->angle + vars->ray_ang_incr > M_PI * 2)
		ray->angle = -1 * ((M_PI * 2) - ray->angle + vars->ray_ang_incr);
	else
		ray->angle += vars->ray_ang_incr;
}

/*
	calculates the height of the wall to be drawn
	consigering fisheye effect and player collision with wall.
*/
void	get_height(t_vars *vars, t_ray *ray, int i)
{
	double	fisheye_correction_factor;

	if (i < MAIN_IMG_W / 2)
		fisheye_correction_factor = cos(FOV_RAD / 2 - (i * vars->ray_ang_incr));
	else
		fisheye_correction_factor \
			= cos((i * vars->ray_ang_incr) - (FOV_RAD / 2));
	ray->wall_height = vars->prj_pane_dist * SCALE \
		/ (ray->distance * fisheye_correction_factor);
}

/*
	RAYCASTING LOOP
*/
void	raycast(t_vars *vars)
{
	t_ray	ray;
	int		i;

	i = 0;
	setup_first_ray(vars, &ray);
	while (i < MAIN_IMG_W)
	{
		cast_ray(vars, &ray);
		get_height(vars, &ray, i);
		draw_sun(vars, &ray, i);
		if (ray.hit_char == '1')
			draw_wall(vars, &ray, i);
		if (ray.hit_char == DOOR_CLOSED)
			draw_tex_line(vars, &ray, \
			vars->door_sprites->frames[vars->door_sprites->anim_count], i);
		draw_ray_minimap(vars, &ray);
		if (vars->display_full_map)
			draw_ray_fullmap(vars, &ray);
		increment_ray_angle(vars, &ray);
		i++;
	}
}
