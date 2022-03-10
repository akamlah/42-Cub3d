/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_checkpos_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:33:33 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/09 00:03:04 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

int	player_check_x_pos(t_vars *vars, t_vector2 newpos)
{
	int	grid_pos_x_left;
	int	grid_pos_x_right;

	grid_pos_x_left = ceil((newpos.x - PLAYER_SIZE_RW) / SCALE) - 1;
	grid_pos_x_right = ceil((newpos.x + PLAYER_SIZE_RW) / SCALE) - 1;
	if (grid_pos_x_left <= player_prev_x_obj(vars)
		|| grid_pos_x_right >= player_next_x_obj(vars))
		return (0);
	return (1);
}

int	player_check_y_pos(t_vars *vars, t_vector2 newpos)
{
	int	grid_pos_y_top;
	int	grid_pos_y_bot;

	grid_pos_y_top = ceil((newpos.y - PLAYER_SIZE_RW) / SCALE) - 1;
	grid_pos_y_bot = ceil((newpos.y + PLAYER_SIZE_RW) / SCALE) - 1;
	if (grid_pos_y_top <= player_prev_y_obj(vars)
		|| grid_pos_y_bot >= player_next_y_obj(vars))
		return (0);
	return (1);
}
