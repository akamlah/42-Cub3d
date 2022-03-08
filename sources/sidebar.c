#include "../header/cub3d.h"

void	draw_sidebar_start(t_vars *vars)
{
	int	distance_lines;
	int	pos_first_line;
	int		color;

	distance_lines = 30;
	pos_first_line = WH / 2;
	color = 0x66b2b2;
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line, color, "Press TAB to desplay full map");
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines, color, "Move head with R/L arrows");
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 2, color, "Walk with W-A-S-D keys");
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 3, color, "Hold SPACEBAR to move faster");
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 4, color, "Hold SHIFT to rotate faster");
}


void	display_data_sidebar(t_vars *vars)
{
	int		distance_lines;
	int		pos_first_line;
	char	output[50];
	char	*tmp;
	int		color;

	distance_lines = 30;
	pos_first_line = 80;
	color = 0xfffb96;
	mlx_clear_window(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr);
	draw_sidebar_start(vars);
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line, 0xffffff, "FOV [deg]: 60");
	snprintf(output, 50, "%.3f", vars->player.angle * 180 / M_PI);
	tmp = ft_strjoin("Angle from E [deg]: ", output);
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 2, color, tmp);
	free(tmp);
	snprintf(output, 50, "%.0f", vars->player.pos.x);
	tmp = ft_strjoin("X pos: ", output);
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 3, color, tmp);
	free(tmp);
	snprintf(output, 50, "%.0f", vars->player.pos.y);
	tmp = ft_strjoin("Y pos: ", output);
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 4, color, tmp);
	free(tmp);
}