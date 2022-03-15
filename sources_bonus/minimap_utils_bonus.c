/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:47:56 by agebert           #+#    #+#             */
/*   Updated: 2022/03/15 12:25:45 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

/*
* Draws Walls or empty spaces in minimap
* t_vector2_int iter: norm-related fix (iter.x == i, iter.y == j)
*/
void	draw_blocks(t_vars *vars, t_image *map_img, \
					int blocksize, t_vector2_int iter)
{
	if (vars->map->nodes[iter.x + vars->minimap.h_offs] \
						[iter.y + vars->minimap.w_offs] == '1')
		draw_square_tlc(map_img,
			new_vector2(blocksize - 1, blocksize - 1),
			new_vector2((iter.y * blocksize), (iter.x * blocksize)),
			vars->minimap.wall_color);
	if (vars->map->nodes[iter.x + vars->minimap.h_offs] \
								[iter.y + vars->minimap.w_offs] == '0')
		draw_square_tlc(map_img, \
			new_vector2(blocksize - 1, blocksize - 1), \
			new_vector2((iter.y * blocksize), (iter.x * blocksize)),
			vars->minimap.floor_color);
}

/*
*	Draw the blocks of the 2d world in the minimap
*/
void	draw_blocks_minimap(t_vars *vars, t_image *map_img, int blocksize)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map->nodes[i + vars->minimap.h_offs] \
		&& i + vars->minimap.h_offs < vars->map->n_lines
		&& i * vars->minimap.scale < vars->minimap.height)
	{
		j = 0;
		while (vars->map->nodes[i + vars->minimap.h_offs] \
								[j + vars->minimap.w_offs] \
			&& vars->map->nodes[i + vars->minimap.h_offs] \
								[j + vars->minimap.w_offs] != '\n' \
			&& j * vars->minimap.scale < vars->minimap.width)
		{
			draw_blocks(vars, map_img, blocksize, new_vector2_int(i, j));
			j++;
		}
		i++;
	}
}

void	adjust_minimap_size(t_vars *vars)
{
	vars->minimap.width = vars->minimap.width \
		/ vars->minimap.scale * vars->minimap.scale;
	vars->minimap.height = vars->minimap.height \
		/ vars->minimap.scale * vars->minimap.scale;
	vars->minimap.total_width = \
		(vars->map->max_width - 1) * vars->minimap.scale;
	vars->minimap.total_height = \
		vars->map->n_lines * vars->minimap.scale;
	if (vars->minimap.total_height < vars->minimap.height)
		vars->minimap.height = vars->minimap.total_height;
	if (vars->minimap.total_width < vars->minimap.width)
		vars->minimap.width = vars->minimap.total_width;
}
