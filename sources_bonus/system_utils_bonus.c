/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:38:46 by agebert           #+#    #+#             */
/*   Updated: 2022/03/09 00:40:10 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

double	get_fps(t_vars *vars)
{
	struct timeval	curr_time;
	double			fps;

	gettimeofday(&curr_time, NULL);
	fps = (60 * 1000 * 1000)
		/ ((double)(((curr_time.tv_usec
						+ curr_time.tv_sec * 1000 * 1000
						- vars->last_time_ms))));
	vars->last_time_ms = curr_time.tv_usec + curr_time.tv_sec * 1000 * 1000;
	printf("fps: %f\n", fps);
	return (fps);
}
