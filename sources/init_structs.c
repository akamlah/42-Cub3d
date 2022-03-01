#include "../header/cub3d.h"


int	init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->angle = 0;
	player->speed = 1;
	player->angle = 0;
	player->rot_speed = 0.05;
	player->move_backward = 0;
	player->move_forward = 0;
	player->move_left = 0;
	player->move_right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
	player->fov = 1.04;
	player->dir.x = 0;
	player->dir.y = 0;

	return (0);
}

// int	init_minimap(t_vars *vars)
// {
int	init_minimap(t_minimap *minimap)
{
	minimap->scale = 16;
	minimap->p_pos.x = 0;
	minimap->p_pos.y = 0;

	// minimap->p_size = 4;
	// minimap->xframelen = 0;
	// minimap->xframeoffset = 0;
	// minimap->yframelen = 0;
	// minimap->yframeoffset = 0;
	// minimap->xwinoffset = 0;
	// minimap->ywinoffset = 0;
// 	return (0);
// }

	// if (!vars->minimap)
	// 	vars->minimap = malloc(sizeof(t_minimap));
	// vars->minimap->scale = 30;
	// vars->minimap->p_pos.x = 10;

	// vars->minimap->height = vars->map->n_lines * vars->minimap->scale;
	// vars->minimap->p_pos.y = WH - vars->minimap->height - 10;
	// vars->minimap->width = (vars->map->max_width - 1) * vars->minimap->scale;
	// vars->minimap->img = new_image(vars, \
	// 	vars->minimap->width, \
	// 	vars->minimap->height, \
	// 	vars->minimap->p_pos.x, \
	// 	vars->minimap->p_pos.y);

	return (0);
}

/*
*	Set all pointers in main struct to null or allocate memory for them before using them
*/
int	init_vars(t_vars *vars)
{
// int	init_vars(t_vars *vars)
// {
// 	vars->map = NULL;
// 	vars->scale = 64;
// 	vars->move_forward = 0;
// 	// init_minimap(&vars->minimap);
	init_player(&vars->player);
// 	vars->last_time_ms = 100;
// 	return (0);
// }
	vars->scale = 64;
	vars->move_forward = 0;

	// vars->player = NULL;
	vars->map = NULL;
	vars->mlx_vars = NULL;
	vars->main_img = NULL;

	// vars->minimap = NULL;
	// vars->minimap = malloc(sizeof(t_minimap));
	init_minimap(&vars->minimap);


	// vars->last_time_ms = 100;

	return (0);
}