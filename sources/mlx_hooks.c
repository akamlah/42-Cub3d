#include "../header/cub3d.h"

/*
*Exits window when "x" is pressed
*/
int	exit_hook(t_vars *vars)
{
	free(vars->mlx_vars);
	system("leaks cub3D");
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
		printf("Left key pressed!\n");
	if (keycode == key_right)
		printf("Right key pressed!\n");
	if (keycode == key_up)
		printf("Up key pressed!\n");
	if (keycode == key_down)
		printf("Down key pressed!\n");
	if (keycode == key_a)
		printf("a key pressed!\n");
	if (keycode == key_d)
		printf("d key pressed!\n");
	if (keycode == key_w)
		printf("w key pressed!\n");
	if (keycode == key_s)
		printf("s key pressed!\n");

	// exit with esc
	if (keycode == key_esc)
		exit_hook(vars);
		
	return (0);
}
