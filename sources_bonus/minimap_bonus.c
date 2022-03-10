/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:24:05 by agebert           #+#    #+#             */
/*   Updated: 2022/03/10 14:14:02 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

int	create_minimap(t_vars *vars)
{
	if (vars->minimap.height >= vars->minimap.width)
		vars->minimap.scale = vars->minimap.height / 12;
	else
		vars->minimap.scale = vars->full_map.max_width / 12;
	if (vars->minimap.scale > 20)
		vars->minimap.scale = 20;
	else if (vars->minimap.scale < 5)
		vars->minimap.scale = 5;
	vars->minimap.width = vars->minimap.width \
		/ vars->minimap.scale * vars->minimap.scale;
	vars->minimap.height = vars->minimap.height \
		/ vars->minimap.scale * vars->minimap.scale;
	vars->minimap.total_width = \
		(vars->map->max_width - 1) * vars->minimap.scale;
	vars->minimap.total_height = \
		vars->map->n_lines * vars->minimap.scale;
	vars->minimap.p_pos.y = vars->wh - vars->minimap.height - 25;
	vars->minimap.p_pos.x = 25;
	vars->mlx_vars->minimap = new_image(vars, vars->minimap.width, \
	vars->minimap.height, vars->minimap.p_pos);
	if (!vars->mlx_vars->minimap)
		return (0);
	return (1);
}

void	draw_player_minimap(t_vars *vars)
{
	draw_square_tlc(vars->mlx_vars->minimap, \
		new_vector2(vars->minimap.player_size, vars->minimap.player_size), \
		new_vector2((vars->player.pos.x * vars->minimap.scale / SCALE \
					- vars->minimap.player_size / 2) \
					- vars->minimap.w_offs * vars->minimap.scale, \
			(vars->player.pos.y * vars->minimap.scale / SCALE \
			- vars->minimap.player_size / 2) \
			- vars->minimap.h_offs * vars->minimap.scale), \
			vars->minimap.player_color);
}

void	minimap_set_offsets(t_vars *vars)
{
	vars->minimap.h_offs = vars->player.pos.y / SCALE \
							- (vars->minimap.height / 2 / vars->minimap.scale);
	if (vars->minimap.h_offs < 0)
		vars->minimap.h_offs = 0;
	if (vars->minimap.h_offs > \
			(vars->minimap.total_height - vars->minimap.height) \
			/ vars->minimap.scale)
		vars->minimap.h_offs = \
			(vars->minimap.total_height - vars->minimap.height) \
			/ vars->minimap.scale;
	vars->minimap.w_offs = \
		vars->player.pos.x / SCALE - \
		(vars->minimap.width / 2 / vars->minimap.scale);
	if (vars->minimap.w_offs < 0)
		vars->minimap.w_offs = 0;
	if (vars->minimap.w_offs > \
			(vars->minimap.total_width - vars->minimap.width) \
			/ vars->minimap.scale)
		vars->minimap.w_offs = \
			(vars->minimap.total_width - vars->minimap.width) \
			/ vars->minimap.scale;
}

void	draw_minimap(t_vars *vars)
{
	draw_square_tlc(vars->mlx_vars->minimap, \
		new_vector2(vars->mlx_vars->minimap->width, \
		vars->mlx_vars->minimap->height), new_vector2(0, 0), \
		vars->minimap.background_color);
	minimap_set_offsets(vars);
	draw_blocks_minimap(vars, vars->mlx_vars->minimap, vars->minimap.scale);
}

void	draw_ray_minimap(t_vars *vars, t_ray *ray)
{
	draw_line(vars->mlx_vars->minimap, \
		new_vector2_int(vars->player.pos.x * vars->minimap.scale / SCALE \
		- vars->minimap.w_offs * vars->minimap.scale, \
		vars->player.pos.y * vars->minimap.scale / SCALE \
		- vars->minimap.h_offs * vars->minimap.scale), \
		new_vector2_int((int)ray->closest_hit.x * vars->minimap.scale / SCALE \
		- vars->minimap.w_offs * vars->minimap.scale, \
		(int)ray->closest_hit.y * vars->minimap.scale / SCALE \
		- vars->minimap.h_offs * vars->minimap.scale), \
		vars->minimap.ray_color);
}
