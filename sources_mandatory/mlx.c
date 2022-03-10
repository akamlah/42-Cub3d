/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:35:46 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/10 15:57:53 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

/*
*Calls all mlx-hooks (keyhooks, loophooks, etc)
*/
int	mlx_hooks(t_vars *vars)
{
	mlx_hook(vars->mlx_vars->win_ptr, 17, 0, &exit_hook, vars);
	mlx_hook(vars->mlx_vars->win_ptr, 2, 0, &on_key_down, vars);
	mlx_hook(vars->mlx_vars->win_ptr, 3, 0, &on_key_up, vars);
	mlx_loop_hook(vars->mlx_vars->mlx_ptr, &update, vars);
	mlx_loop(vars->mlx_vars->mlx_ptr);
	return (0);
}

/*
*Exits window when "x" is pressed
*/
int	exit_hook(void)
{
	exit_cub();
	return (0);
}

int	on_key_down(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->player.move_forward = 1;
	else if (keycode == KEY_S)
		vars->player.move_backward = 1;
	else if (keycode == KEY_A)
		vars->player.move_left = 1;
	else if (keycode == KEY_D)
		vars->player.move_right = 1;
	else if (keycode == KEY_LEFT)
		vars->player.rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		vars->player.rotate_right = 1;
	else if (keycode == KEY_ESC)
		exit_cub();
	else if (keycode == KEY_SPACE)
		vars->player.speed = vars->player.sprinting_speed;
	else if (keycode == KEY_LSHIFT || keycode == KEY_RSHIFT)
		vars->player.rot_speed = vars->player.rot_fast_speed;
	return (0);
}

int	on_key_up(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->player.move_forward = 0;
	else if (keycode == KEY_S)
		vars->player.move_backward = 0;
	else if (keycode == KEY_A)
		vars->player.move_left = 0;
	else if (keycode == KEY_D)
		vars->player.move_right = 0;
	else if (keycode == KEY_LEFT)
		vars->player.rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		vars->player.rotate_right = 0;
	else if (keycode == KEY_SPACE)
		vars->player.speed = vars->player.basic_speed;
	else if (keycode == KEY_LSHIFT || keycode == KEY_RSHIFT)
		vars->player.rot_speed = vars->player.rot_slow_speed;
	return (0);
}
