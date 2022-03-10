/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:19:20 by agebert           #+#    #+#             */
/*   Updated: 2022/03/10 16:58:23 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

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

void	free_image(t_vars *vars, t_image *image)
{
	if (image)
	{
		mlx_destroy_image(vars->mlx_vars->mlx_ptr, image->img_ptr);
		free(image);
	}
}

void	free_map_nodes(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->map)
	{
		if (vars->map->nodes)
		{
			while (vars->map->nodes[i])
			{
				free(vars->map->nodes[i]);
				i++;
			}
			free(vars->map->nodes);
		}
		free(vars->map);
	}
}

void	free_map_textures(t_vars *vars)
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
	}
	free_image(vars, vars->tex_n);
	free_image(vars, vars->tex_s);
	free_image(vars, vars->tex_e);
	free_image(vars, vars->tex_w);
}

/*
*	ONLY EXITPOINT here.
*	Checks for any variable to be freed.
*/
void	exit_cub(void)
{
	exit(0);
}
