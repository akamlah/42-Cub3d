#include "../header/cub3d.h"

// only exitpoint, easier check for leaks
void	exit_cub(t_vars *vars)
{
	// eventually call freeing functions?
/* 	if (vars->map->fd_cubfile)
		close(vars->map->fd_cubfile); */

/* 	if (vars->map)
	{
		if (vars->map->textr_n)
			free(vars->map->textr_n);
		if (vars->map->textr_s)
			free(vars->map->textr_s);
		if (vars->map->textr_w)
			free(vars->map->textr_w);
		if (vars->map->textr_e)
			free(vars->map->textr_e);
	} */
	if (vars->map)
		free(vars->map);
	system("leaks cub3D");
	exit(0);
}

void	vars_init(t_vars *vars)
{
	vars->map = NULL;
	// ...
}

int main(int argc, char **argv)
{
	t_vars	vars;

	vars_init(&vars);
	if (parse(&vars, argc, argv))
	{
		exit_cub(&vars);
	}


	init_mlx_vars(&vars);
	mlx_hooks(&vars);
	mlx_loop(vars.mlx_vars->mlx);

	return (0);
}
