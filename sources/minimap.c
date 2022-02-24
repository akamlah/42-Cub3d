#include "../header/cub3d.h"

void	init_minimap(t_vars *vars)
{
	if (!vars->minimap)
		vars->minimap = malloc(sizeof(t_minimap));
	vars->minimap->scale = 50;
	vars->minimap->width = (vars->map->max_width - 1) * vars->minimap->scale;
	vars->minimap->height = vars->map->n_lines * vars->minimap->scale;
	vars->minimap->img = new_image(vars, \
		vars->minimap->width, \
		vars->minimap->height, \
		10, \
		WH - vars->minimap->height - 10);
}

/*
*	Draw the blocks of the 2d world in the minimap
*/
void	draw_blocks_minimap(t_vars *vars)
{
	int i, j;
	i = 0;
	while (vars->map->nodes[i] && i < vars->map->n_lines)
	{
		j = 0;
		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
		{
			if (vars->map->nodes[i][j] == '1')
				draw_square_tlc(vars->minimap->img, \
					vars->minimap->scale - 1, \
					vars->minimap->scale - 1, \
					j * vars->minimap->scale, \
					i * vars->minimap->scale, \
					0xffffff);
			if (vars->map->nodes[i][j] == '0')
				draw_square_tlc(vars->minimap->img, \
					vars->minimap->scale - 1, \
					vars->minimap->scale - 1, \
					j * vars->minimap->scale, \
					i * vars->minimap->scale, \
					0x000000);
			j++;
		}
		i++;
	}
}
void	draw_line(t_image *img, int I_xo, int I_yo, int I_xend, int I_yend);

void	draw_player_minimap(t_vars *vars)
{
	int size;

	// for now player as cube 1/10 of blocksize in minimap
	size = vars->minimap->scale / 10;
	draw_square_tlc(vars->minimap->img, size, size, \
	// conversion RW coords to minimap coords
		vars->player->RW_x * vars->minimap->scale / RW_UNIT - size / 2, \
		vars->player->RW_y * vars->minimap->scale / RW_UNIT - size / 2, \
	0xff0000);
	draw_line(vars->minimap->img, \
		vars->player->RW_x * vars->minimap->scale / RW_UNIT - size / 2, \
		vars->player->RW_y * vars->minimap->scale / RW_UNIT - size / 2, \
		0, 0);
}

void	draw_minimap(t_vars *vars)
{
	init_minimap(vars);

	// background
	draw_square_tlc(vars->minimap->img, \
		vars->minimap->width, \
		vars->minimap->height, \
		0, \
		0, \
		0x808080);

	// draw blocks
	draw_blocks_minimap(vars);
	draw_player_minimap(vars);

	vars->prjp = new_image(vars, PRJP_W, PRJP_H, 20, 20);


	// find HORIZONTAL COLLISIONS:
	float first_hor_grid_coll_RW_x = 0;
	float first_hor_grid_coll_RW_y = 0;

	// find coordinates of 1st intersection with the horizontal gridlines from player position.

	// 1st octant
	if (vars->player->th <= 0.0001 || vars->player->th >= (M_PI * 2) - 0.0001)
	{
		// first_hor_grid_coll_RW_x = ((vars->player->RW_x / RW_UNIT) + 1) * RW_UNIT; // actually it  is a vertical collision - should be infinite
		first_hor_grid_coll_RW_x = (vars->map->max_width - 1) * RW_UNIT;
		first_hor_grid_coll_RW_y = vars->player->RW_y;
	}
	if (0.0001 < vars->player->th && M_PI / 2 -  0.0001 > vars->player->th) // find better solution but tan segfaults if th = 0.00001!
	{
		// ray points upwards so y coord will be same as y of the whole gridline, ie py / rw_unit
		// vertical distance to grid is py % rw_unit.
		// x  coord of pt is px % rwunit + (vertical distance to grid / tan (th))
		first_hor_grid_coll_RW_x = vars->player->RW_x + ((vars->player->RW_y % RW_UNIT) / tan(vars->player->th));
		first_hor_grid_coll_RW_y = (vars->player->RW_y / RW_UNIT) * RW_UNIT;
	}

	// 2nd octant
	if (vars->player->th <= M_PI / 2 + 0.0001 && vars->player->th >= M_PI / 2 - 0.0001)
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x;
		first_hor_grid_coll_RW_y = (vars->player->RW_y / RW_UNIT) * RW_UNIT;
	}
	if (M_PI / 2 + 0.0001 < vars->player->th && M_PI - 0.0001 > vars->player->th)
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x - ((vars->player->RW_y % RW_UNIT) / tan(M_PI - vars->player->th));
		first_hor_grid_coll_RW_y = (vars->player->RW_y / RW_UNIT) * RW_UNIT;
	}

	// 3rd octant
	if (vars->player->th >= M_PI - 0.0001 && vars->player->th <= M_PI + 0.0001)
	{
		// first_hor_grid_coll_RW_x = ((vars->player->RW_x / RW_UNIT)) * RW_UNIT; // actually it  is a vertical collision  - should be infinite
		first_hor_grid_coll_RW_x = 0;
		first_hor_grid_coll_RW_y = vars->player->RW_y;
	}
	if (vars->player->th > M_PI + 0.0001 && vars->player->th < 3 * (M_PI / 2) - 0.0001)
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x - ((RW_UNIT - vars->player->RW_y % RW_UNIT) / tan(vars->player->th - M_PI));
		first_hor_grid_coll_RW_y = ((vars->player->RW_y / RW_UNIT) + 1) * RW_UNIT;
	}

	// 4th octant
	if (vars->player->th >= 3 * (M_PI / 2) - 0.0001 && vars->player->th <= 3 * (M_PI / 2) + 0.0001)
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x;
		first_hor_grid_coll_RW_y = (vars->player->RW_y / RW_UNIT + 1) * RW_UNIT;
	}
	if (vars->player->th > 3 * (M_PI / 2) + 0.0001 && vars->player->th < (M_PI * 2) - 0.0001)
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x + ((RW_UNIT - vars->player->RW_y % RW_UNIT) / tan(M_PI * 2 - vars->player->th));
		first_hor_grid_coll_RW_y = (vars->player->RW_y / RW_UNIT + 1) * RW_UNIT;
	}


	draw_line(vars->minimap->img, \
		vars->player->RW_x * vars->minimap->scale / RW_UNIT, \
		vars->player->RW_y * vars->minimap->scale / RW_UNIT, \
		(int)first_hor_grid_coll_RW_x * vars->minimap->scale / RW_UNIT, \
		(int)first_hor_grid_coll_RW_y * vars->minimap->scale / RW_UNIT);


	// put to window
	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->minimap->img->img_ptr, \
		vars->minimap->img->S_xtlc, \
		vars->minimap->img->S_ytlc);
}