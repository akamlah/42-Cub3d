/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:40:51 by agebert           #+#    #+#             */
/*   Updated: 2022/03/09 01:23:13 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

void	draw_line_init(t_vector2_int begin,
				t_vector2_int end, t_bresenheim *bres_vars)
{
	bres_vars->dx = abs(end.x - begin.x);
	if (begin.x < end.x)
		bres_vars->sx = 1;
	else
		bres_vars->sx = -1;
	bres_vars->dy = -abs(end.y - begin.y);
	if (begin.y < end.y)
		bres_vars->sy = 1;
	else
		bres_vars->sy = -1;
	bres_vars->err = bres_vars->dx + bres_vars->dy;
}

/*
	Draws a line with Bresenham algorithm from point o to point end
*/
void	draw_line(t_image *img, t_vector2_int begin,
				t_vector2_int end, int color)
{
	t_bresenheim	bres_vars;

	draw_line_init(begin, end, &bres_vars);
	while (1)
	{
		if ((begin.x >= 0 && begin.x < img->width)
			&& (begin.y >= 0 && begin.y < img->height))
			cub_pixel_put(img, begin.x, begin.y, color);
		if (begin.x == end.x && begin.y == end.y)
			break ;
		bres_vars.e2 = 2 * bres_vars.err;
		if (bres_vars.e2 > bres_vars.dy)
		{
			bres_vars.err += bres_vars.dy;
			begin.x += bres_vars.sx;
		}
		if (bres_vars.e2 < bres_vars.dx)
		{
			bres_vars.err += bres_vars.dx;
			begin.y += bres_vars.sy;
		}
	}
}
