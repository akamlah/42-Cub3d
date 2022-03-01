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

	// when splitting, use new_image functon.
	vars->main_img = malloc(sizeof(t_image));
	if (!vars->main_img)
	{
		printf("Failed to initialize mlx main image\n");
		return (4);
	}
	vars->main_img->height = PRJP_H ;
	vars->main_img->width = PRJP_W;
	vars->main_img->pos.x = 20; // replace with vector
	vars->main_img->pos.y = 20;
	vars->main_img->img_ptr = mlx_new_image(vars->mlx_vars->mlx_ptr, vars->main_img->width, vars->main_img->height);
	vars->main_img->address = mlx_get_data_addr(vars->main_img->img_ptr, \
	&vars->main_img->bits_per_pixel, &vars->main_img->line_length, \
	&vars->main_img->endian);

	vars->mlx_vars->minimap = malloc(sizeof(t_image));
	if (!vars->mlx_vars->minimap)
	{
		printf("Failed to initialize mlx main image\n");
		return (5);
	}
	// vars->mlx_vars->minimap->height = vars->minimap.scale * vars->map->n_lines;
	// vars->minimap.width = vars->minimap.scale * vars->map->max_width;
	// printf("size: %d\n", vars->minimap.width);
	vars->mlx_vars->minimap->height = vars->map->n_lines * vars->minimap.scale;
	vars->mlx_vars->minimap->width = (vars->map->max_width - 1) * vars->minimap.scale;
	vars->minimap.p_pos.y = WH - vars->mlx_vars->minimap->height - 10;

	vars->mlx_vars->minimap->pos = vars->minimap.p_pos;

		// vars->mlx_vars->minimap = new_image(vars, \
		// 	vars->mlx_vars->minimap->width, \
		// 	vars->mlx_vars->minimap->height, \
		// 	vars->minimap->p_pos.x, \
		// 	vars->minimap->p_pos.y);
	vars->mlx_vars->minimap->height = vars->mlx_vars->minimap->height;
	vars->mlx_vars->minimap->width = vars->mlx_vars->minimap->width;
	vars->mlx_vars->minimap->img_ptr = mlx_new_image(vars->mlx_vars->mlx_ptr, vars->mlx_vars->minimap->width, vars->mlx_vars->minimap->height);
	vars->mlx_vars->minimap->address = mlx_get_data_addr(vars->mlx_vars->minimap->img_ptr, \
	&vars->mlx_vars->minimap->bits_per_pixel, &vars->mlx_vars->minimap->line_length, \
	&vars->mlx_vars->minimap->endian);

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


// works also with pressed keys
// int cub_dealkey(int keycode, t_vars *vars)
// {
// 	int pace;
// 	pace = 2;
// 	double th_rot_speed = M_PI / 48;
// 	// double th_rot_speed = FOV_RAD / FOV_DEG;
// 	double diff = 0;
// 	if (keycode == key_a && vars->player.pos.x - pace >= 0 
// 		&& vars->map->nodes[vars->player.pos.y / vars->scale][(vars->player.pos.x - pace) / vars->scale] == '0')
// 		vars->player.pos.x -= pace;
// 	if (keycode == key_d && vars->player.pos.x + pace < (vars->map->max_width - 1) * vars->scale
// 		&& vars->map->nodes[vars->player.pos.y / vars->scale][(vars->player.pos.x + pace) / vars->scale] == '0')
// 		vars->player.pos.x += pace;
// 	if (keycode == key_w && vars->player.pos.y - pace >= 0
// 		&& vars->map->nodes[(vars->player.pos.y - pace) / vars->scale][vars->player.pos.x / vars->scale] == '0')
// 		vars->player.pos.y -= pace;
// 	if (keycode == key_s && vars->player.pos.y + pace < vars->map->n_lines * vars->scale
// 		&& vars->map->nodes[(vars->player.pos.y + pace) / vars->scale][vars->player.pos.x / vars->scale] == '0')
// 		vars->player.pos.y += pace;

// 	if (keycode == key_up)
// 		printf("a key pressed!\n");
// 	if (keycode == key_down)
// 		printf("d key pressed!\n");
// 	if (keycode == key_left)
// 	{
// 		if (vars->player.angle + th_rot_speed < 2 * M_PI)
// 			vars->player.angle += th_rot_speed;
// 		else
// 		{
// 			diff = M_PI * 2 - vars->player.angle;
// 			vars->player.angle = th_rot_speed - diff;
// 		}
// 		// printf("%f %f\n", M_PI / 2, vars->player.angle);
// 	}
// 	if (keycode == key_right)
// 	{
// 		if (vars->player.angle - th_rot_speed > 0)
// 			vars->player.angle -= th_rot_speed;
// 		else
// 		{
// 			diff = vars->player.angle;
// 			vars->player.angle = M_PI * 2 - th_rot_speed + diff;
// 		}
// 		// printf("%f\n", vars->player.angle);
// 	}

// 	if (keycode == key_esc)
// 		free_and_exit(vars);

// 	// no loop!
// 	update(vars);

// 	return (0);
// }


/*
*Function that runs at the start of every mlx-loop
*/
// int	update(t_vars *vars)
// {
// 	player_move(vars, vars->player);
// 	// get_fps(vars);
// 	//render(vars);
	
// 	return (0);
// }


/*
*Function that runs at the start of every mlx-loop
*/
int	update(t_vars *vars)
{
	player_move(vars, &vars->player);
	get_fps(vars);
	// mlx_clear_window(vars->mlx_vars->mlx_ptr, vars->mlx_vars->win_ptr);
	// if (vars->mlx_vars->minimap)
	// {
	// 	mlx_destroy_image(vars->mlx_vars->mlx_ptr, vars->mlx_vars->minimap->img_ptr);
	// 	free(vars->mlx_vars->minimap);
	// 	vars->minimap = NULL;
	// }
	// if (vars->main_img)
	// {
	// 	mlx_destroy_image(vars->mlx_vars->mlx_ptr, vars->main_img->img_ptr);
	// 	free(vars->main_img);
	// 	vars->main_img = NULL;
	// }
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
