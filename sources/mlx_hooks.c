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
	vars->mlx_vars->mlx = vars->mlx_vars->mlx; //silence flags, can be deleted
	return (0);
}

/*
*Handles all neccessary keyboard interaction
*/
int	key_hook(int keycode, t_vars *vars)
{
	vars->mlx_vars->mlx = vars->mlx_vars->mlx; //silence flags, can be deleted
	if (keycode == key_left)
		vars->px--;
		// printf("Left key pressed!\n");
	if (keycode == key_right)
		vars->px++; // protect!
		// printf("Right key pressed!\n");
	if (keycode == key_up)
		vars->py--;
		// printf("Up key pressed!\n");
	if (keycode == key_down)
		vars->py++;
		// printf("Down key pressed!\n");
	if (keycode == key_a)
		printf("a key pressed!\n");
	if (keycode == key_d)
		printf("d key pressed!\n");
	if (keycode == key_w)
		printf("w key pressed!\n");
	if (keycode == key_s)
	{
		// printf("s key pressed!\n");
		// test for img:
		vars->mlx_vars->test *= -1;
	}

	// exit with esc
	if (keycode == key_esc)
		exit_hook(vars);
	// redraw when finished:
	draw(vars);
	return (0);
}
