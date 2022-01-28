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
	if (vars->mlx_vars->mainImg)
	{
		free(vars->mlx_vars->mainImg);
		vars->mlx_vars->mainImg = NULL;
	}
	draw(vars);
	return (0);
}


// works also with pressed keys
int cub_dealkey(int keycode, t_vars *vars)
{
	// t_vars *vars;
	if (keycode == key_a)
		vars->px--;
		// printf("Left key pressed!\n");
	if (keycode == key_d)
		vars->px++; // protect!
		// printf("Right key pressed!\n");
	if (keycode == key_w)
		vars->py--;
		// printf("Up key pressed!\n");
	if (keycode == key_s)
		vars->py++;
		// printf("Down key pressed!\n");
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
		draw(vars);
	return (0);
}
