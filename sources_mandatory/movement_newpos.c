/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_newpos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:32:30 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/09 14:51:47 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

int	player_next_x_obj(t_vars *vars)
{
	int	p_grid_ypos;
	int	p_grid_xpos;
	int	i;

	p_grid_xpos = ceil(vars->player.pos.x / SCALE);
	p_grid_ypos = ceil(vars->player.pos.y / SCALE) - 1;
	i = p_grid_xpos;
	while (vars->map->nodes[p_grid_ypos][i]
		&& vars->map->nodes[p_grid_ypos][i] != '\n'
		&& vars->map->nodes[p_grid_ypos][i] < '1')
		i++;
	return (i);
}

int	player_next_y_obj(t_vars *vars)
{
	int	p_grid_ypos;
	int	p_grid_xpos;
	int	i;

	p_grid_xpos = ceil(vars->player.pos.x / SCALE) - 1;
	p_grid_ypos = ceil(vars->player.pos.y / SCALE);
	i = p_grid_ypos;
	while (vars->map->nodes[i][p_grid_xpos] && i < vars->map->n_lines - 1
		&& (int)ft_strlen(vars->map->nodes[i + 1]) >= p_grid_xpos
		&& vars->map->nodes[i][p_grid_xpos] != '\n'
		&& vars->map->nodes[i][p_grid_xpos] < '1')
		i++;
	return (i);
}

int	player_prev_y_obj(t_vars *vars)
{
	int	p_grid_ypos;
	int	p_grid_xpos;
	int	i;

	p_grid_xpos = ceil(vars->player.pos.x / SCALE) - 1;
	p_grid_ypos = ceil(vars->player.pos.y / SCALE) - 1;
	i = p_grid_ypos;
	while (vars->map->nodes[i][p_grid_xpos] && i > 0
		&& (int)ft_strlen(vars->map->nodes[i - 1]) >= p_grid_xpos
		&& vars->map->nodes[i][p_grid_xpos] != '\n'
		&& vars->map->nodes[i][p_grid_xpos] == '0')
			i--;
	return (i);
}

int	player_prev_x_obj(t_vars *vars)
{
	int	p_grid_ypos;
	int	p_grid_xpos;
	int	i;

	p_grid_xpos = ceil(vars->player.pos.x / SCALE) - 1;
	p_grid_ypos = ceil(vars->player.pos.y / SCALE) - 1;
	i = p_grid_xpos;
	while (vars->map->nodes[p_grid_ypos][i] && i > 0
		&& vars->map->nodes[p_grid_ypos][i] == '0')
		i--;
	return (i);
}

t_vector2	player_get_newpos(t_player *player, int speed_forward, \
	double new_angle)
{
	t_vector2	newpos;

	if (player->dir.x > 0 && player->dir.y < 0)
	{
		newpos.x = player->pos.x - cos(M_PI - new_angle) * speed_forward;
		newpos.y = player->pos.y - sin(M_PI - new_angle) * speed_forward;
	}
	else if (player->dir.x > 0 && player->dir.y > 0)
	{
		newpos.x = player->pos.x - cos(M_PI - new_angle) * speed_forward;
		newpos.y = player->pos.y - sin(M_PI - new_angle) * speed_forward;
	}
	else if (player->dir.x < 0 && player->dir.y > 0)
	{
		newpos.x = player->pos.x - cos(M_PI - new_angle) * speed_forward;
		newpos.y = player->pos.y - sin(M_PI - new_angle) * speed_forward;
	}
	else
	{
		newpos.x = player->pos.x - cos(M_PI - new_angle) * speed_forward;
		newpos.y = player->pos.y - sin(M_PI - new_angle) * speed_forward;
	}
	return (newpos);
}
