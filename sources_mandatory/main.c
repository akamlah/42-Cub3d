/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:36:28 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/10 15:59:12 by agebert          ###   ########.fr       */
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
		exit_cub();
	if (!parse_colors(&vars))
		exit_cub();
	init_mlx_vars(&vars);
	get_player_spawn(&vars);
	draw_sidebar_start(&vars);
	render(&vars);
	mlx_hooks(&vars);
	return (0);
}

/*
*	ONLY EXITPOINT here.
*	Checks for any variable to be freed.
*/
void	exit_cub(void)
{
	exit(0);
}
