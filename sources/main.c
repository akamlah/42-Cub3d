#include "../header/cub3d.h"

int main(int argc, char **argv)
{
	t_vars vars;

	if (parse(&vars, argc, argv))
		return (1);
	init_mlx_vars(&vars);
	mlx_hooks(&vars);
	mlx_loop(vars.mlx_vars->mlx);

	return (0);
}
