/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:07:44 by agebert           #+#    #+#             */
/*   Updated: 2022/03/09 01:23:13 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

static int	get_pixel_color(t_image *img, double x, double y)
{
	char	*dst;

	dst = img->address + ((int)floor(y) * img->line_length + \
		(int)floor(x) * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static double	set_tex_x(t_ray *ray, t_image *src_img)
{
	double	tex_x;

	if (ray->facing_direction == 1 || ray->facing_direction == 3)
		tex_x = (fmod(ray->closest_hit.x, SCALE) / SCALE) * src_img->width ;
	else
		tex_x = (fmod(ray->closest_hit.y, SCALE) / SCALE) * src_img->width;
	return (tex_x);
}

void	draw_tex_line(t_vars *vars, t_ray *ray, t_image *src_img, int i)
{
	int		y;
	double	incr;
	double	tex_x;
	double	y_offs;
	int		img_addr_offs;

	img_addr_offs = (MAIN_IMG_W - i - 1) * (vars->main_img->bits_per_pixel / 8);
	y = 0;
	y_offs = (vars->main_img->height / 2) - ray->wall_height / 2;
	tex_x = set_tex_x(ray, src_img);
	incr = (double)src_img->height / ray->wall_height;
	if (ray->wall_height > MAIN_IMG_H)
		y = (ray->wall_height - MAIN_IMG_H) / 2;
	while (y < ray->wall_height)
	{
		if (y + y_offs >= 0 && y + y_offs < MAIN_IMG_H)
			*(unsigned int *)(vars->main_img->address + (int)((y + y_offs) \
				* vars->main_img->line_length + img_addr_offs)) \
				= get_pixel_color(src_img, tex_x, y * incr);
		y++;
	}
}
