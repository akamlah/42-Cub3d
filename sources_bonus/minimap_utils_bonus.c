/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:47:56 by agebert           #+#    #+#             */
/*   Updated: 2022/03/09 01:23:13 by agebert          ###   ########.fr       */
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
