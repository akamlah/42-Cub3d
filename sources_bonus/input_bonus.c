/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:53:52 by agebert           #+#    #+#             */
/*   Updated: 2022/03/10 16:13:14 by agebert          ###   ########.fr       */
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
	else if (keycode == KEY_TAB)
		vars->display_full_map = 1;
	else if (keycode == KEY_SPACE)
		vars->player.speed = vars->player.sprinting_speed;
	else if (keycode == KEY_LSHIFT || keycode == KEY_RSHIFT)
		vars->player.rot_speed = vars->player.rot_fast_speed;
	if (keycode == KEY_F)
		vars->player.action_set = 1;
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
	else if (keycode == KEY_TAB)
		vars->display_full_map = 0;
	else if (keycode == KEY_SPACE)
		vars->player.speed = vars->player.basic_speed;
	else if (keycode == KEY_LSHIFT || keycode == KEY_RSHIFT)
		vars->player.rot_speed = vars->player.rot_slow_speed;
	return (0);
}
