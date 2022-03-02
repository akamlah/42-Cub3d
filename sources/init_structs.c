#include "../header/cub3d.h"


int	init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->angle = 0;
	player->speed = 10;
	player->angle = 0;
	// player->rot_speed = 0.05;
		player->rot_speed = M_PI / 48;

	player->move_backward = 0;
	player->move_forward = 0;
	player->move_left = 0;
	player->move_right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
	// player->fov = 1.04;
	player->dir.x = 0;
	player->dir.y = 0;

	return (0);
}

// int	init_minimap(t_vars *vars)
// {
int	init_minimap(t_minimap *minimap)
{
	minimap->scale = 30;
	minimap->p_pos.x = 0;
	minimap->p_pos.y = 0;
	return (0);
}

/*
*	Set all pointers in main struct to null or allocate memory for them before using them
*/
int	init_vars(t_vars *vars)
{
	init_player(&vars->player);
	init_minimap(&vars->minimap);
	vars->last_time_ms = 100;

	vars->prj_pane_dist = (MAIN_IMG_W / 2 / tan(FOV_RAD / 2));
	// SCALE = 64;
	vars->move_forward = 0;
	vars->map = NULL;
	vars->mlx_vars = NULL;
	vars->main_img = NULL;

	// NOW IT IS ON STACK
	// vars->minimap = NULL;
	// vars->minimap = malloc(sizeof(t_minimap));
	return (0);
}