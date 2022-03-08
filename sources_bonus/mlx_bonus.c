#include "../header_bonus/cub3d_bonus.h"

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
	vars->main_img = new_image(vars, MAIN_IMG_W, MAIN_IMG_H, new_vector2(20, 20));
	if (!create_minimap(vars))
		return (4);
	if (!create_fullmap(vars))
		return (4);

	vars->tex_door = new_image_tex(vars, "./textures_xpm/door_rust.xpm");
	vars->tex_N = new_image_tex(vars, vars->map->textr_n);
	vars->tex_S = new_image_tex(vars, vars->map->textr_s);
	vars->tex_E = new_image_tex(vars, vars->map->textr_e);
	vars->tex_W = new_image_tex(vars, vars->map->textr_w);
	vars->mario_dance = init_anim_sprite(vars, "./mario_frames/", 22);
	return (0);
}

/*
*Calls all mlx-hooks (keyhooks, loophooks, etc)
*/
int	mlx_hooks(t_vars *vars)
{
	mlx_hook(vars->mlx_vars->win_ptr, 17, 0, &exit_hook, vars);
	mlx_hook(vars->mlx_vars->win_ptr, 6, 0, &on_mouse_move, vars);
	mlx_hook(vars->mlx_vars->win_ptr, 2, 0, &on_key_down, vars);
	mlx_hook(vars->mlx_vars->win_ptr, 3, 0, &on_key_up, vars);
	mlx_loop_hook(vars->mlx_vars->mlx_ptr, &update, vars); 
	mlx_loop(vars->mlx_vars->mlx_ptr);
	return (0);
}

int on_mouse_move(int x, int y, t_vars *vars)
{
	int	temp;

	temp = y;
	if (vars->player.mouse_last_x > MAIN_IMG_W)
		vars->player.mouse_last_x = MAIN_IMG_W;
	if (vars->player.mouse_last_x < 0)
		vars->player.mouse_last_x = 0;
	if (x < vars->player.mouse_last_x + 1)
		vars->player.angle += vars->player.rot_speed;
	if (x > vars->player.mouse_last_x - 1)
		vars->player.angle -= vars->player.rot_speed;
	vars->player.mouse_last_x = x;
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
	else if (keycode == key_tab)
		vars->display_full_map = 1;
	else if (keycode == key_space)
		vars->player.speed = vars->player.sprinting_speed;
	else if (keycode == key_Lshift || keycode == key_Rshift)
		vars->player.rot_speed = vars->player.rot_fast_speed;
	if (keycode == key_f)
		vars->player.action_set = 1;
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
	else if (keycode == key_tab)
		vars->display_full_map = 0;
	else if (keycode == key_space)
		vars->player.speed = vars->player.basic_speed;
	else if (keycode == key_Lshift || keycode == key_Rshift)
		vars->player.rot_speed = vars->player.rot_slow_speed;
	return (0);
}

/*
*Function that runs at the start of every mlx-loop
*/
int	update(t_vars *vars)
{
	player_move(vars, &vars->player);
	//get_fps(vars);
	render(vars);
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
