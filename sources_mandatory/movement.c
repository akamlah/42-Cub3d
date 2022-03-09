/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:34:06 by akamlah           #+#    #+#             */
/*   Updated: 2022/03/08 23:35:21 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_mandatory/cub3d_mandatory.h"

/*
*Corrects angle if angle > 2 * PI or < 0
*Returns corrected angle
*/
static double	correct_angle(double angle)
{
	if (angle <= 0)
		angle = 2 * M_PI - fabs(angle);
	if (angle >= 2 * M_PI)
		angle = angle - 2 * M_PI;
	return (angle);
}

static void	player_set_speed_angle2(t_player *player, double *angle_offs)
{
	if (player->move_right && !player->move_left && (player->move_forward))
		*angle_offs = -0.785398;
	if (!player->move_right && player->move_left && (player->move_forward))
		*angle_offs = 0.785398;
	if (player->move_right && !player->move_left && (player->move_backward))
		*angle_offs = 0.785398;
	if (!player->move_right && player->move_left && (player->move_backward))
		*angle_offs = -0.785398;
	if (player->rotate_left && !player->rotate_right)
		player->angle += player->rot_speed;
	if (!player->rotate_left && player->rotate_right)
		player->angle -= player->rot_speed;
}

static void	player_set_speed_angle(t_player *player, int *speed_forward, \
	double *angle_offs)
{
	if (player->move_forward && !player->move_backward)
		*speed_forward = player->speed;
	if (player->move_backward && !player->move_forward)
		*speed_forward = -player->speed;
	if (!player->move_left && player->move_right && !player->move_forward
		&& !player->move_backward)
	{
		*angle_offs = -M_PI_2;
		*speed_forward = player->speed;
	}
	if (player->move_left && !player->move_right && !player->move_forward
		&& !player->move_backward)
	{
		*angle_offs = M_PI_2;
		*speed_forward = player->speed;
	}
	player_set_speed_angle2(player, angle_offs);
}

/*
*Calculates relative X and Y direction of an angle 
*Sets passed t_vector2 to these values
*/
static void	set_dir(double angle, t_vector2 *dir)
{
	if (M_PI - angle >= M_PI_2 && M_PI - angle > 0)
	{
		dir->x = 1;
		dir->y = -1;
	}
	else if ((M_PI) - angle < M_PI_2 && M_PI - angle > 0)
	{
		dir->x = -1;
		dir->y = -1;
	}
	else if ((M_PI) - angle < 0 && M_PI - angle > (M_PI * -0.5))
	{
		dir->x = -1;
		dir->y = 1;
	}
	else
	{
		dir->x = 1;
		dir->y = 1;
	}
	return ;
}

void	player_move(t_vars *vars, t_player *player)
{
	int			speed_forward;
	double		angle_offs;
	double		new_angle;
	t_vector2	newpos;
	t_vars		vars2;

	vars2 = *vars;
	speed_forward = 0;
	angle_offs = 0;
	new_angle = 0;
	set_dir(new_angle, &player->dir);
	player_set_speed_angle(player, &speed_forward, &angle_offs);
	new_angle = correct_angle(player->angle + angle_offs);
	newpos = player_get_newpos(player, speed_forward, new_angle);
	player->angle = correct_angle(player->angle);
	if (player_check_x_pos(vars, newpos))
		player->pos.x = newpos.x;
	if (player_check_y_pos(vars, newpos))
		player->pos.y = newpos.y;
	return ;
}
