#include "../header/cub3d.h"


/*
*Calls all mlx-hooks (keyhooks, loophooks, etc)
*/
int	mlx_hooks(t_vars *vars)
{
	mlx_hook(vars->mlx_vars->window, 17, 0, &exit_hook, vars);
	mlx_loop_hook(vars->mlx_vars->mlx, &update, vars);
	mlx_key_hook(vars->mlx_vars->window, &key_hook, vars);
	return (0);
}

/*
*Initializes MLX variables
*/
int	init_mlx_vars(t_vars *vars)
{
	vars->mlx_vars = malloc(sizeof(t_mlx_vars));
	if (!vars->mlx_vars)
	{
		printf("Failed to allocate mlx_vars memory.\n");
		return (1);
	}
	vars->mlx_vars->mlx = mlx_init();
	if (!vars->mlx_vars->mlx)
	{
		printf("Failed to initialize mlx\n");
		return (2);
	}
	vars->mlx_vars->window
		= mlx_new_window(vars->mlx_vars->mlx, WW, WH, "cub3d");
	if (!vars->mlx_vars->window)
	{
		printf("Failed to initialize mlx window\n");
		return (3);
	}
	return (0);
}

