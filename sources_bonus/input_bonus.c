/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:53:52 by agebert           #+#    #+#             */
/*   Updated: 2022/03/08 23:53:52 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

int	on_mouse_move(int x, int y, t_vars *vars)
{
	int	temp;

	temp = y;
	if (vars->player.mouse_last_x > MAIN_IMG_W)
		vars->player.mouse_last_x = MAIN_IMG_W;
	if (vars->player.mouse_last_x < 0)
		vars->player.mouse_last_x = 0;
	if (x < vars->player.mouse_last_x + 1)
		vars->player.angle += vars->player.rot_speed;
	if (x > vars->player.mouse_last_x - 1)
		vars->player.angle -= vars->player.rot_speed;
	vars->player.mouse_last_x = x;
	return (0);
}

int	on_key_down(int keycode, t_vars *vars)
{
	if (keycode == key_w)
		vars->player.move_forward = 1;
	else if (keycode == key_s)
		vars->player.move_backward = 1;
	else if (keycode == key_a)
		vars->player.move_left = 1;
	else if (keycode == key_d)
		vars->player.move_right = 1;
	else if (keycode == key_left)
		vars->player.rotate_left = 1;
	else if (keycode == key_right)
		vars->player.rotate_right = 1;
	else if (keycode == key_esc)
		free_and_exit(vars);
	else if (keycode == key_tab)
		vars->display_full_map = 1;
	else if (keycode == key_space)
		vars->player.speed = vars->player.sprinting_speed;
	else if (keycode == key_Lshift || keycode == key_Rshift)
		vars->player.rot_speed = vars->player.rot_fast_speed;
	if (keycode == key_f)
		vars->player.action_set = 1;
	return (0);
}

int	on_key_up(int keycode, t_vars *vars)
{
	if (keycode == key_w)
		vars->player.move_forward = 0;
	else if (keycode == key_s)
		vars->player.move_backward = 0;
	else if (keycode == key_a)
		vars->player.move_left = 0;
	else if (keycode == key_d)
		vars->player.move_right = 0;
	else if (keycode == key_left)
		vars->player.rotate_left = 0;
	else if (keycode == key_right)
		vars->player.rotate_right = 0;
	else if (keycode == key_tab)
		vars->display_full_map = 0;
	else if (keycode == key_space)
		vars->player.speed = vars->player.basic_speed;
	else if (keycode == key_Lshift || keycode == key_Rshift)
		vars->player.rot_speed = vars->player.rot_slow_speed;
	return (0);
}
