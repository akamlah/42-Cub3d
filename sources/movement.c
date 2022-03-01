#include "../header/cub3d.h"

/*
*Calculates relative X and Y direction of an angle 
*Sets passed t_vector2 to these values
*/
void	set_dir(double angle, t_vector2 *dir)
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

/*
*Corrects angle if angle > 2 * PI or < 0
*Returns corrected angle
*/
double	correct_angle(double angle)
{
	if (angle <= 0)
		angle = 2 * M_PI - fabs(angle);
	if (angle >= 2 * M_PI)
		angle = angle - 2 * M_PI;
	return (angle);
}

void	player_set_speed_angle(t_player *player, int *speed_forward, double *angle_offs)
{
	if (player->move_forward && !player->move_backward)
		*speed_forward = player->speed;
	if (player->move_backward && !player->move_forward)
		*speed_forward = -player->speed;
	if (!player->move_left && player->move_right && !player->move_forward && !player->move_backward)
	{
		*angle_offs = -M_PI_2;
		*speed_forward = player->speed;
	}
	if (player->move_left && !player->move_right && !player->move_forward && !player->move_backward)
	{
		*angle_offs = M_PI_2;
		*speed_forward = player->speed;
	}
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

t_vector2	player_get_newpos(t_player *player, int speed_forward, double new_angle)
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

int	player_next_x_obj(t_vars *vars)
{
	int	p_grid_ypos;
	int p_grid_xpos;
	int	i;

	p_grid_xpos = ceil(vars->player.pos.x / vars->scale);
	p_grid_ypos = ceil(vars->player.pos.y / vars->scale) - 1;
	// printf("xpos: %d\n", p_grid_xpos);
	i = p_grid_xpos;
	while (vars->map->nodes[p_grid_ypos][i] && vars->map->nodes[p_grid_ypos][i] != '\n'
		&& vars->map->nodes[p_grid_ypos][i] < '1')
		i++;
	return (i);
}

int	player_next_y_obj(t_vars *vars)
{
	int	p_grid_ypos;
	int p_grid_xpos;
	int	i;

	p_grid_xpos = ceil(vars->player.pos.x / vars->scale) - 1;
	p_grid_ypos = ceil(vars->player.pos.y / vars->scale);
	// printf("xpos: %d\n", p_grid_xpos);
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
	int p_grid_xpos;
	int	i;

	p_grid_xpos = ceil(vars->player.pos.x / vars->scale) - 1;
	p_grid_ypos = ceil(vars->player.pos.y / vars->scale) - 1;
	// printf("xpos: %d\n", p_grid_xpos);
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
	int p_grid_xpos;
	int	i;

	p_grid_xpos = ceil(vars->player.pos.x / vars->scale) - 1;
	p_grid_ypos = ceil(vars->player.pos.y / vars->scale) - 1;
	// printf("xpos: %d\n", p_grid_xpos);
	i = p_grid_xpos;
	while (vars->map->nodes[p_grid_ypos][i] && i > 0
		&& vars->map->nodes[p_grid_ypos][i] == '0')
		i--;
	return (i);
}

int		player_check_x_pos(t_vars *vars, t_vector2 newpos)
{
	int	grid_pos_x;

	grid_pos_x = ceil(newpos.x / vars->scale) - 1;
	if (grid_pos_x <= player_prev_x_obj(vars)
		|| grid_pos_x >= player_next_x_obj(vars))
			return (0);
	return (1);
}

int		player_check_y_pos(t_vars *vars, t_vector2 newpos)
{
	int	grid_pos_y;

	grid_pos_y = ceil(newpos.y / vars->scale) - 1;
	if (grid_pos_y <= player_prev_y_obj(vars)
		|| grid_pos_y >= player_next_y_obj(vars))
			return (0);
	return (1);
}

void	player_move(t_vars *vars, t_player *player)
{
	int		speed_forward;
	double	angle_offs;
	double	new_angle;
	t_vector2	newpos;

	t_vars vars2;

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
	// printf("posx: %d, posy: %d\n", player->pos.x, player->pos.y);
	return ;
}
