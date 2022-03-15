/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agebert <agebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:49:35 by agebert           #+#    #+#             */
/*   Updated: 2022/03/15 00:37:37 by agebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3d_bonus.h"

int	init_images(t_vars *vars)
{
	vars->main_img
		= new_image(vars, MAIN_IMG_W, MAIN_IMG_H, new_vector2(20, 20));
	if (!create_minimap(vars))
		exit_cub();
	if (!create_fullmap(vars))
		exit_cub();
	vars->door_sprites = init_anim_sprite(vars, "./door_frames/", 24);
	vars->tex_n = new_image_tex(vars, vars->map->textr_n);
	vars->tex_s = new_image_tex(vars, vars->map->textr_s);
	vars->tex_e = new_image_tex(vars, vars->map->textr_e);
	vars->tex_w = new_image_tex(vars, vars->map->textr_w);
	return (0);
}

/*
*	Initializes MLX variables: connection to server, window.
*/
int	init_mlx_vars(t_vars *vars)
{
	vars->mlx_vars = malloc(sizeof(t_mlx_vars));
	if (!vars->mlx_vars)
	{
		printf("Error\nailed to allocate mlx_vars memory.\n");
		return (1);
	}
	vars->mlx_vars->minimap = NULL;
	vars->mlx_vars->mlx_ptr = mlx_init();
	if (!vars->mlx_vars->mlx_ptr)
	{
		printf("Failed to initialize mlx\n");
		return (2);
	}
	vars->mlx_vars->win_ptr
		= mlx_new_window(vars->mlx_vars->mlx_ptr, vars->ww, vars->wh, "cub3d");
	if (!vars->mlx_vars->win_ptr)
	{
		printf("Error\nFailed to initialize mlx window\n");
		return (3);
	}
	if (init_images(vars))
		return (4);
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

/*
*Function that runs at the start of every mlx-loop
*/
int	update(t_vars *vars)
{
	player_move(vars, &vars->player);
	render(vars);
	return (0);
}

/*
*Exits window vars->when "x" is pressed
*/
int	exit_hook(void)
{
	exit_cub();
	return (0);
}
