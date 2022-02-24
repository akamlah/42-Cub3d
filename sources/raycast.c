#include "../header/cub3d.h"

void	raycast(t_vars *vars)
{
	vars->prjp = new_image(vars, PRJP_W, PRJP_H, 20, 20);


	// find HORIZONTAL COLLISIONS:

	// find coordinates of 1st intersection with the horizontal gridlines from player position.
	if (0.001 < vars->player->th && M_PI / 2 > vars->player->th) // find better solution but tan segfaults if th = 0.00001!
	{
		// ray points upwards so y coord will be same as y of the whole gridline, ie py / rw_unit
		// vertical distance to grid is py % rw_unit.
		// x  coord of pt is px % rwunit + (vertical distance to grid / tan (th))
		float hor_grid_collision_RW_x = vars->player->RW_x + ((vars->player->RW_y % RW_UNIT) / tan(vars->player->th));
		float hor_grid_collision_RW_y = vars->player->RW_y;
		// printf("%f %d %f %d\n", hor_grid_collision_x, (int)hor_grid_collision_x, hor_grid_collision_y, (int)hor_grid_collision_y);
		printf("%f %f\n", hor_grid_collision_RW_x, hor_grid_collision_RW_y);
		
		draw_line(vars->minimap->img, \
			vars->player->RW_x * vars->minimap->scale / RW_UNIT, \
			vars->player->RW_y * vars->minimap->scale / RW_UNIT, \
			(int)hor_grid_collision_RW_x * vars->minimap->scale / RW_UNIT, \
			(int)hor_grid_collision_RW_y * vars->minimap->scale / RW_UNIT);
		if (vars->map->nodes[(int)(hor_grid_collision_RW_y / RW_UNIT)][(int)(hor_grid_collision_RW_x / RW_UNIT)] == '1')
		{
			printf("yo!");
		}

	}


	// put to window
	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->prjp->img_ptr, \
		vars->prjp->S_xtlc, \
		vars->prjp->S_ytlc);
}
