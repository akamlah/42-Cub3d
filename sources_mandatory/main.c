/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:36:28 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/09 14:50:16 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		error;

	if (argc != 2)
	{
		print_usage_message(1);
		return (1);
	}
	init_vars(&vars);
	error = parse(&vars, argv);
	if (error)
		free_and_exit(&vars);
	if (!parse_colors(&vars))
		free_and_exit(&vars);
	init_mlx_vars(&vars);
	get_player_spawn(&vars);
	draw_sidebar_start(&vars);
	render(&vars);
	mlx_hooks(&vars);
	return (0);
}

/*
	Frees nodes in map.
*/
static void	free_mapnodes(t_vars *vars)
{
	int	i;

	if (vars->map->nodes)
	{
		i = 0;
		while (vars->map->nodes[i])
		{
			free(vars->map->nodes[i]);
			i++;
		}
		free(vars->map->nodes);
	}
}

/*
*	ONLY EXITPOINT here.
*	Checks for any variable to be freed.
*/
void	free_and_exit(t_vars *vars)
{
	if (vars->map)
	{
		if (vars->map->fd_cubfile)
			close(vars->map->fd_cubfile);
		if (vars->map->textr_n)
			free(vars->map->textr_n);
		if (vars->map->textr_s)
			free(vars->map->textr_s);
		if (vars->map->textr_w)
			free(vars->map->textr_w);
		if (vars->map->textr_e)
			free(vars->map->textr_e);
		if (vars->map->floor_color)
			free(vars->map->floor_color);
		if (vars->map->ceiling_color)
			free(vars->map->ceiling_color);
		free_mapnodes(vars);
		free(vars->map);
	}
	if (vars->mlx_vars)
		free(vars->mlx_vars);
	if (vars->main_img)
		free(vars->main_img);
	exit(0);
}
