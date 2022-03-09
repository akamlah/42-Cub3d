/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:46:16 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/09 14:24:46 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

void	render(t_vars *vars)
{
	t_vector2_int	pos;
	t_vector2_int	size;

	pos.x = 0;
	pos.y = MAIN_IMG_H / 2;
	size.x = MAIN_IMG_W;
	size.y = MAIN_IMG_H / 2;
	draw_square_tlc(vars->main_img, size, pos, vars->floor_color);
	pos.y = 0;
	draw_square_tlc(vars->main_img, size, pos, vars->ceiling_color);
	raycast(vars);
	display_data_sidebar(vars);
	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->main_img->img_ptr, \
		vars->main_img->pos.x, \
		vars->main_img->pos.y);
}

/*
*Function that runs at the start of every mlx-loop
*/
int	update(t_vars *vars)
{
	player_move(vars, &vars->player);
	render(vars);
	return (0);
}
