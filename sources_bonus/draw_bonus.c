#include "../header_bonus/cub3d_bonus.h"

void	raycast(t_vars *vars);

void render(t_vars *vars)
{
	anim_sprite(vars->mario_dance, 50000);
	draw_minimap(vars);

	// background main img:
	// draw_square_tlc(vars->main_img, MAIN_IMG_W, MAIN_IMG_H / 2, 0, MAIN_IMG_H / 2, 0xb2924e); // floor beige
	draw_square_tlc(vars->main_img, MAIN_IMG_W, MAIN_IMG_H / 2, 0, MAIN_IMG_H / 2, 0x5b5b5b); // floor  0x455447

	
	draw_square_tlc(vars->main_img, MAIN_IMG_W, MAIN_IMG_H / 2, 0, 0, 0xb8dcfd);	// ceiling perfect sky blue
	// draw_square_tlc(vars->main_img, MAIN_IMG_W, MAIN_IMG_H / 2, 0, 0, 0xcfe3d4); // f3f6f4

	if (vars->display_full_map == 1)
		draw_full_map(vars);

	raycast(vars); // also draws to minimap img. and full map
	// // put to window raycasted

	draw_player_minimap(vars);
	draw_player_full_map(vars);
	
	display_data_sidebar(vars);


	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->main_img->img_ptr, \
		vars->main_img->pos.x, \
		vars->main_img->pos.y);
		
	// // put to window minimap

	if (vars->display_full_map == 0)
	{
		mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
			vars->mlx_vars->win_ptr, \
			vars->mlx_vars->minimap->img_ptr, \
			vars->mlx_vars->minimap->pos.x, \
			vars->mlx_vars->minimap->pos.y);
	}

	if (vars->display_full_map == 1)
	{
		// draw_full_map(vars);
		mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
			vars->mlx_vars->win_ptr, \
			vars->full_map.img->img_ptr, \
			vars->full_map.img->pos.x, \
			vars->full_map.img->pos.y);
	}

}

