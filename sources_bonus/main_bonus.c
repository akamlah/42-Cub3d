#include "../header_bonus/cub3d_bonus.h"

int main(int argc, char **argv)
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
		free_and_exit(&vars);
	
	init_mlx_vars(&vars);
	// mlx_mouse_hide();
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
void	free_and_exit(t_vars *vars)
{
	// free map vars:
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
		free(vars->map);
	}
	if (vars->mario_dance)
	{
		if (vars->mario_dance->frames)
			free(vars->mario_dance->frames);
		free(vars->mario_dance);
	}
	// free mlx vars:
	if (vars->mlx_vars)
		free(vars->mlx_vars);
	

		// NOW ON STACK
		// player vars:
		// if (vars->player)
		// 	free(vars->player);

		// minimap vars:
		// if (vars->minimap)
		// {
		if (vars->mlx_vars)
			if (vars->mlx_vars->minimap)
				free(vars->mlx_vars->minimap);
		// 	free(vars->minimap);
		// }
			if (vars->full_map.img)
				free(vars->full_map.img);

			if (vars->main_img)
				free(vars->main_img);
	system("leaks cub3D");
	exit(0);
}
