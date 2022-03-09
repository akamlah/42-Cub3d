/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:10:06 by agebert           #+#    #+#             */
/*   Updated: 2022/03/09 01:23:13 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

static void	set_orientation_angle(t_vars *vars, int i, int j)
{
	if (vars->map->nodes[i][j] == 'N')
		vars->player.spawn_angle = M_PI_2;
	if (vars->map->nodes[i][j] == 'S')
		vars->player.spawn_angle = 3 * M_PI_2;
	if (vars->map->nodes[i][j] == 'E')
		vars->player.spawn_angle = 0;
	if (vars->map->nodes[i][j] == 'W')
		vars->player.spawn_angle = M_PI;
	vars->player.angle = vars->player.spawn_angle;
}

/*
*	Scans map and sets indicated spawnpoint and orientation,
*	Saves them and initialises player position to spawnpoint.
*	Sets player spawnpoint to 0 in map after that.
*/
int	get_player_spawn(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map->nodes[i] && i < vars->map->n_lines)
	{
		j = 0;
		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
		{
			if (ft_isalpha(vars->map->nodes[i][j]))
			{
				vars->player.spawn_pos.x = j * SCALE + SCALE / 2;
				vars->player.spawn_pos.y = i * SCALE + SCALE / 2;
				vars->player.pos.x = vars->player.spawn_pos.x;
				vars->player.pos.y = vars->player.spawn_pos.y;
				set_orientation_angle(vars, i, j);
				vars->map->nodes[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
