/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:36:56 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/09 15:14:30 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

void	init_textures(t_vars *vars)
{
	vars->main_img = new_image(vars, MAIN_IMG_W, MAIN_IMG_H, \
		new_vector2(20, 20));
	vars->tex_n = new_image_tex(vars, vars->map->textr_n);
	vars->tex_s = new_image_tex(vars, vars->map->textr_s);
	vars->tex_e = new_image_tex(vars, vars->map->textr_e);
	vars->tex_w = new_image_tex(vars, vars->map->textr_w);
}

/*
*	Initializes MLX variables: connection to server, window.
*/
int	init_mlx_vars(t_vars *vars)
{
	vars->mlx_vars = malloc(sizeof(t_mlx_vars));
	if (!vars->mlx_vars)
	{
		printf("Failed to allocate mlx_vars memory.\n");
		return (1);
	}
	vars->mlx_vars->mlx_ptr = mlx_init();
	if (!vars->mlx_vars->mlx_ptr)
	{
		printf("Failed to initialize mlx\n");
		return (2);
	}
	vars->mlx_vars->win_ptr = mlx_new_window(vars->mlx_vars->mlx_ptr, \
		vars->winw, vars->winh, "cub3d");
	if (!vars->mlx_vars->win_ptr)
	{
		printf("Failed to initialize mlx window\n");
		return (3);
	}
	init_textures(vars);
	return (0);
}

int	init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->angle = 0;
	player->basic_speed = 6;
	player->sprinting_speed = 10;
	player->speed = player->basic_speed;
	player->angle = 0;
	player->rot_slow_speed = 0.04;
	player->rot_fast_speed = 0.08;
	player->rot_speed = player->rot_slow_speed;
	player->move_backward = 0;
	player->move_forward = 0;
	player->move_left = 0;
	player->move_right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->mouse_last_x = 0;
	player->size = SCALE / 10;
	return (0);
}

/*
	Set all pointers in main struct to null or allocate memory for them
	before using them
*/
int	init_vars(t_vars *vars)
{
	init_player(&vars->player);
	vars->last_time_ms = 100;
	vars->prj_pane_dist = (MAIN_IMG_W / 2 / tan(FOV_RAD / 2));
	vars->move_forward = 0;
	vars->map = NULL;
	vars->mlx_vars = NULL;
	vars->main_img = NULL;
	vars->winw = (MAIN_IMG_W + SIDEBAR_W + MAIN_IMG_WIN_OFFSET * 2);
	vars->winh = (MAIN_IMG_H + MAIN_IMG_WIN_OFFSET * 2);
	vars->ray_ang_incr = (FOV_RAD / MAIN_IMG_W);
	return (0);
}
