#include "../header/cub3d.h"

void	raycast(t_vars *vars);

void draw_all(t_vars *vars)
{
	draw_minimap(vars);

	raycast(vars); // also draws to minimap img.
	// // put to window raycasted

	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->main_img->img_ptr, \
		vars->main_img->S_xtlc, \
		vars->main_img->S_ytlc);
	draw_player_minimap(vars);
	
	// // put to window minimap
	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->mlx_vars->minimap->img_ptr, \
		// vars->minimap->p_pos.x, \
		// vars->minimap->p_pos.y);
		vars->mlx_vars->minimap->S_xtlc, \
		vars->mlx_vars->minimap->S_ytlc);

}

