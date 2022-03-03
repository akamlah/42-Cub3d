#include "../header/cub3d.h"

void	raycast(t_vars *vars);

void draw_all(t_vars *vars)
{
	draw_minimap(vars);

	// background main img:
	// draw_square_tlc(vars->main_img, MAIN_IMG_W, MAIN_IMG_H / 2, 0, MAIN_IMG_H / 2, 0xb2924e); // floor beige
		draw_square_tlc(vars->main_img, MAIN_IMG_W, MAIN_IMG_H / 2, 0, MAIN_IMG_H / 2, 0x5b5b5b); // floor  0x455447

	
	draw_square_tlc(vars->main_img, MAIN_IMG_W, MAIN_IMG_H / 2, 0, 0, 0xb8dcfd);	// ceiling perfect sky blue
	// draw_square_tlc(vars->main_img, MAIN_IMG_W, MAIN_IMG_H / 2, 0, 0, 0xcfe3d4); // f3f6f4

	raycast(vars); // also draws to minimap img.
	// // put to window raycasted

	draw_player_minimap(vars);




	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->main_img->img_ptr, \
		vars->main_img->pos.x, \
		vars->main_img->pos.y);
		
	// // put to window minimap
	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->mlx_vars->minimap->img_ptr, \
		vars->mlx_vars->minimap->pos.x, \
		vars->mlx_vars->minimap->pos.y);

}

