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
	mlx_hook(vars->mlx_vars->win_ptr, 2, (1L<<13), &cub_dealkey, vars);
	// mlx_loop_hook(vars->mlx_vars->mlx_ptr, &update, vars); // memory consuming!
	mlx_loop(vars->mlx_vars->mlx_ptr);
	return (0);
}

// works also with pressed keys
int cub_dealkey(int keycode, t_vars *vars)
{
	int pace;
	pace = 2;
	double th_rot_speed = M_PI / 48;
	double diff = 0;
	if (keycode == key_a && vars->player->RW_x - pace >= 0 
		&& vars->map->nodes[vars->player->RW_y / RW_UNIT][(vars->player->RW_x - pace) / RW_UNIT] == '0')
		vars->player->RW_x -= pace;
	if (keycode == key_d && vars->player->RW_x + pace < (vars->map->max_width - 1) * RW_UNIT
		&& vars->map->nodes[vars->player->RW_y / RW_UNIT][(vars->player->RW_x + pace) / RW_UNIT] == '0')
		vars->player->RW_x += pace;
	if (keycode == key_w && vars->player->RW_y - pace >= 0
		&& vars->map->nodes[(vars->player->RW_y - pace) / RW_UNIT][vars->player->RW_x / RW_UNIT] == '0')
		vars->player->RW_y -= pace;
	if (keycode == key_s && vars->player->RW_y + pace < vars->map->n_lines * RW_UNIT
		&& vars->map->nodes[(vars->player->RW_y + pace) / RW_UNIT][vars->player->RW_x / RW_UNIT] == '0')
		vars->player->RW_y += pace;

	if (keycode == key_up)
		printf("a key pressed!\n");
	if (keycode == key_down)
		printf("d key pressed!\n");
	if (keycode == key_left)
	{
		if (vars->player->th + th_rot_speed < 2 * M_PI)
			vars->player->th += th_rot_speed;
		else
		{
			diff = M_PI * 2 - vars->player->th;
			vars->player->th = th_rot_speed - diff;
		}
		printf("%f %f\n", M_PI / 2, vars->player->th);
	}
	if (keycode == key_right)
	{
		if (vars->player->th - th_rot_speed > 0)
			vars->player->th -= th_rot_speed;
		else
		{
			diff = vars->player->th;
			vars->player->th = M_PI * 2 - th_rot_speed + diff;
		}
		printf("%f\n", vars->player->th);
	}

	if (keycode == key_esc)
		free_and_exit(vars);

	// no loop!
	update(vars);

	return (0);
}

/*
*Function that runs at the start of every mlx-loop
*/
int	update(t_vars *vars)
{
	mlx_clear_window(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr);
	if (vars->minimap->img)
	{
		mlx_destroy_image(vars->mlx_vars->mlx_ptr, vars->minimap->img->img_ptr);
		free(vars->minimap->img);
		vars->minimap = NULL;
	}
	if (vars->prjp)
	{
		mlx_destroy_image(vars->mlx_vars->mlx_ptr, vars->prjp->img_ptr);
		free(vars->prjp);
		vars->prjp = NULL;
	}
	// destroy imgs and free ptrs
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

/*
*Loads an image from path and returns MLX-Image as void pointer.
*Returns NULL Pointer if file invalid
*/
void	*loadimage(char *path, t_vars *vars)
{
	void	*img;
	int		fd;
	int		width;
	int		height;

	if (!path)
	{
		printf("Error: Empty image file name.\n");
		return(NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		return (NULL);
	}
	img = mlx_xpm_file_to_image(vars->mlx_vars->mlx_ptr, path, &width, &height);
	if (!img)
	{
		printf("Error: Image file could not be opened. Please make sure it exists and is in .xpm format.\n");
		return(NULL);
	}
	close (fd);
	return (img);
}
