#include "../header/cub3d.h"

// only exitpoint, easier check for leaks
void	exit_cub(int exitcode, t_vars *vars)
{
	// eventually call freeing functions?
	if (vars->map->fd_cubfile)
		close(vars->map->fd_cubfile);
	// system("leaks cub3D");
	exit(exitcode);
}

void	vars_init(t_vars *vars)
{
	vars->exitcode = 0;
	vars->map = NULL;
	// ...
}

int main(int argc, char **argv)
{
	t_vars	vars;

	vars_init(&vars);
	vars.exitcode = parse(&vars, argc, argv);
	if (vars.exitcode)
		exit_cub(vars.exitcode, &vars);

/* 	init_mlx_vars(&vars);
	mlx_hooks(&vars);
	mlx_loop(vars.mlx_vars->mlx); */

	return (0);
}
