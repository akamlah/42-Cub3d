/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:16:04 by agebert           #+#    #+#             */
/*   Updated: 2022/03/09 00:50:53 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

void	render_fullmap(t_vars *vars)
{
	if (vars->display_full_map == 0)
	{
		mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
			vars->mlx_vars->win_ptr, \
			vars->mlx_vars->minimap->img_ptr, \
			vars->mlx_vars->minimap->pos.x, \
			vars->mlx_vars->minimap->pos.y);
	}
	if (vars->display_full_map == 1)
	{
		mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
			vars->mlx_vars->win_ptr, \
			vars->full_map.img->img_ptr, \
			vars->full_map.img->pos.x, \
			vars->full_map.img->pos.y);
	}
}

void	render(t_vars *vars)
{
	anim_sprite(vars->door_sprites, 50000);
	draw_minimap(vars);
	draw_square_tlc(vars->main_img, \
				new_vector2(MAIN_IMG_W, MAIN_IMG_H / 2), \
				new_vector2(0, MAIN_IMG_H / 2), 0x5b5b5b);
	draw_square_tlc(vars->main_img, \
				new_vector2(MAIN_IMG_W, MAIN_IMG_H / 2), \
				new_vector2(0, 0), 0xb8dcfd);
	if (vars->display_full_map == 1)
		draw_full_map(vars);
	raycast(vars);
	draw_player_minimap(vars);
	draw_player_full_map(vars);
	display_data_sidebar(vars);
	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->main_img->img_ptr, \
		vars->main_img->pos.x, \
		vars->main_img->pos.y);
	render_fullmap(vars);
}
