#include "../header/cub3d.h"

void	draw_sidebar_start(t_vars *vars)
{
	int	distance_lines;
	int	pos_first_line;

	distance_lines = 30;
	pos_first_line = WH / 2;
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line, 0xffffff, "Press TAB to desplay full map");
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines, 0xffffff, "Move head with R/L arrows");
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 2, 0xffffff, "Walk with W-A-S-D keys");
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 3, 0xffffff, "Hold SPACEBAR to move faster");
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 3, 0xffffff, "Hold SHIFT to rotate faster");
}


void	display_data_sidebar(t_vars *vars)
{
	int		distance_lines;
	int		pos_first_line;
	char	output[50];
	char	*tmp;

	distance_lines = 30;
	pos_first_line = 80;
	mlx_clear_window(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr);
	draw_sidebar_start(vars);
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line, 0xffffff, "FOV [deg]: 60");

	snprintf(output, 50, "%.3f", vars->player.angle);
	tmp = ft_strjoin("angle from E [rad]: ", output);
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 2, 0xffffff, tmp);
	free(tmp);

	snprintf(output, 50, "%.0f", vars->player.pos.x);
	tmp = ft_strjoin("X pos: ", output);
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 3, 0xffffff, tmp);
	free(tmp);

	snprintf(output, 50, "%.0f", vars->player.pos.y);
	tmp = ft_strjoin("Y pos: ", output);
	mlx_string_put(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr, WW - SIDEBAR_W, \
		pos_first_line + distance_lines * 4, 0xffffff, tmp);
	free(tmp);

	// coordinates (x, y): (x, y);
}