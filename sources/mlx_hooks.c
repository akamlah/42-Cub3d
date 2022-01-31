#include "../header/cub3d.h"

/*
*Exits window when "x" is pressed
*/
int	exit_hook(t_vars *vars)
{
	free(vars->mlx_vars);
	// system("leaks cub3D");
	exit(0);
}

/*
*Function that runs at the start of every mlx-loop
*/
int	update(t_vars *vars)
{

	mlx_clear_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window);
	if (vars->mlx_vars->minimap)
	{
		free(vars->mlx_vars->minimap);
		vars->mlx_vars->minimap = NULL;
	}
	build_frame(vars);

	// (test)
	// 		int i, j;
	// 	// PRINT map->nodes (char ** with nls)
	// 	i = 0;
	// 	while (vars->map->nodes[i] && i < vars->map->n_lines)
	// 	{
	// 		j = 0;
	// 		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
	// 		{
	// 			printf("%c", vars->map->nodes[i][j]);
	// 			j++;
	// 		}
	// 		printf("\n");
	// 		i++;
	// 	}
	return (0);
}


/*
*Calls all mlx-hooks (keyhooks, loophooks, etc)
*/
int	mlx_hooks(t_vars *vars)
{
	mlx_hook(vars->mlx_vars->window, 17, 0, &exit_hook, vars);
	mlx_hook(vars->mlx_vars->window, 2, (1L<<13), &cub_dealkey, vars);
	mlx_loop_hook(vars->mlx_vars->mlx_ref, &update, vars);
	mlx_loop(vars->mlx_vars->mlx_ref);
	return (0);
}

// works also with pressed keys
int cub_dealkey(int keycode, t_vars *vars)
{

	if (keycode == key_a)
		vars->px-=2;
	if (keycode == key_d)
		vars->px+=2; // protect!
	if (keycode == key_w)
		vars->py-=2;
	if (keycode == key_s)
		vars->py+=2;
	if (keycode == key_up)
		printf("a key pressed!\n");
	if (keycode == key_down)
		printf("d key pressed!\n");
	if (keycode == key_left)
		printf("w key pressed!\n");
	if (keycode == key_right)
	{
		// printf("s key pressed!\n");
		// test for img:
		vars->mlx_vars->test *= -1;
	}

	if (keycode == key_esc)
		exit_cub(vars);
	// build_frame(vars);

	return (0);
}
