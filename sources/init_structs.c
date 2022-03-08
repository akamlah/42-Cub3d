#include "../header/cub3d.h"


int	init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->angle = 0;
	player->basic_speed = 6;
	player->sprinting_speed = 10;
	player->speed = player->basic_speed;
	player->angle = 0;
	player->rot_slow_speed = 0.04;
	player->rot_fast_speed = 0.08;
	player->rot_speed = player->rot_slow_speed;

	// player->rot_speed = M_PI / 128;

	player->move_backward = 0;
	player->move_forward = 0;
	player->move_left = 0;
	player->move_right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->mouse_last_x = 0;
	return (0);
}

// int	init_minimap(t_vars *vars)
// {
int	init_minimap(t_minimap *minimap)
{
	minimap->scale = 10;
	minimap->p_pos.x = 0;
	minimap->p_pos.y = 0;
	minimap->width = WW / 6;
	minimap->height = WH / 6;

	minimap->player_size = minimap->scale / 2;

	minimap->wall_color = 0xece2e0;
	minimap->floor_color = 0x200000;
	minimap->background_color = 0x400000;
	minimap->player_color = 0xdde663;
	minimap->ray_color = 0xa0a37e;

	return (0);
}

void	init_full_map(t_full_map *full_map)
{
	full_map->max_width = MAIN_IMG_W - FUL_MAP_MAIN_IMG_OFFSET * 2;
	full_map->max_height = MAIN_IMG_H - FUL_MAP_MAIN_IMG_OFFSET * 2;
	full_map->top_left_corner_pos.x = FULL_MAP_WIN_OFFSET;
	full_map->top_left_corner_pos.y = FULL_MAP_WIN_OFFSET;
	full_map->blocksize = 0;
	full_map->player_size = 0;
	full_map->img = NULL;
}

/*
*	Set all pointers in main struct to null or allocate memory for them before using them
*/
int	init_vars(t_vars *vars)
{
	init_player(&vars->player);

	init_minimap(&vars->minimap);

	init_full_map(&vars->full_map);
	vars->display_full_map = 0;

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