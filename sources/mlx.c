#include "../header/cub3d.h"

/*
*	Initializes MLX variables: connection to server, window.
*/
int	init_mlx_vars(t_vars *vars)
{
	vars->mlx_vars = malloc(sizeof(t_mlx_vars));
	if (!vars->mlx_vars)
	{
		printf("Failed to allocate mlx_vars memory.\n");
		return (1);
	}
	vars->mlx_vars->mlx_ptr = mlx_init();
	if (!vars->mlx_vars->mlx_ptr)
	{
		printf("Failed to initialize mlx\n");
		return (2);
	}
	vars->mlx_vars->win_ptr
		= mlx_new_window(vars->mlx_vars->mlx_ptr, WW, WH, "cub3d");
	if (!vars->mlx_vars->win_ptr)
	{
		printf("Failed to initialize mlx window\n");
		return (3);
	}
	return (0);
}

/*
*Calls all mlx-hooks (keyhooks, loophooks, etc)
*/
int	mlx_hooks(t_vars *vars)
{
	mlx_hook(vars->mlx_vars->win_ptr, 17, 0, &exit_hook, vars);
	// mlx_hook(vars->mlx_vars->win_ptr, 2, (1L<<13), &cub_dealkey, vars);

	mlx_hook(vars->mlx_vars->win_ptr, 2, 0, &on_key_down, vars);
	mlx_hook(vars->mlx_vars->win_ptr, 3, 0, &on_key_up, vars);

	mlx_loop_hook(vars->mlx_vars->mlx_ptr, &update, vars); 
	// if we put update only in key hooks framesonly get regenerated when pressing
	// but it's not as smooth

	mlx_loop(vars->mlx_vars->mlx_ptr);
	return (0);
}

int	on_key_down(int keycode, t_vars *vars)
{
	if (keycode == key_w)
		vars->player.move_forward = 1;
	else if (keycode == key_s)
		vars->player.move_backward = 1;
	else if (keycode == key_a)
		vars->player.move_left = 1;
	else if (keycode == key_d)
		vars->player.move_right = 1;
	else if (keycode == key_left)
		vars->player.rotate_left = 1;
	else if (keycode == key_right)
		vars->player.rotate_right = 1;
	else if (keycode == key_esc)
		free_and_exit(vars);
	// update(vars);
	return (0);
}

int	on_key_up(int keycode, t_vars *vars)
{
	if (keycode == key_w)
		vars->player.move_forward = 0;
	else if (keycode == key_s)
		vars->player.move_backward = 0;
	else if (keycode == key_a)
		vars->player.move_left = 0;
	else if (keycode == key_d)
		vars->player.move_right = 0;
	else if (keycode == key_left)
		vars->player.rotate_left = 0;
	else if (keycode == key_right)
		vars->player.rotate_right = 0;
	// update(vars);
	return (0);
}

/*
*Function that runs at the start of every mlx-loop
*/
int	update(t_vars *vars)
{
	player_move(vars, &vars->player);
	//get_fps(vars);
	draw_all(vars);
	return (0);
}

/*
*Exits window when "x" is pressed
*/
int	exit_hook(t_vars *vars)
{
	free_and_exit(vars);
	return (0);
}
