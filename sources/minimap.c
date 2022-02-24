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
	double first_hor_grid_coll_RW_x = 0;
	double first_hor_grid_coll_RW_y = 0;
	double range_rounding = 0.0000001;

	// find coordinates of 1st intersection with the horizontal gridlines from player position.

	// edge cases... excluded from drawing
	// around 0
	if (vars->player->th <= range_rounding || vars->player->th >= (M_PI * 2) - range_rounding)
	{
		first_hor_grid_coll_RW_x = (vars->map->max_width - 1) * RW_UNIT;
		first_hor_grid_coll_RW_y = vars->player->RW_y;
	}
	// around 90
	if (vars->player->th <= M_PI_2 + range_rounding && vars->player->th >= M_PI_2 - range_rounding)
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x;
		first_hor_grid_coll_RW_y = (vars->player->RW_y / RW_UNIT) * RW_UNIT;
	}
	// around 180
	if (vars->player->th >= M_PI - range_rounding && vars->player->th <= M_PI + range_rounding)
	{
		first_hor_grid_coll_RW_x = 0;
		first_hor_grid_coll_RW_y = vars->player->RW_y;
	}
	// around 270
	if (vars->player->th >= 3 * M_PI_2 - range_rounding && vars->player->th <= 3 * M_PI_2 + range_rounding)
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x;
		first_hor_grid_coll_RW_y = ((vars->player->RW_y / RW_UNIT) + 1) * RW_UNIT;
	}

	double dy = RW_UNIT;
	double dx = RW_UNIT / tan(vars->player->th);

	// 1st octant
	// 2nd octant
	if ((range_rounding < vars->player->th && M_PI_2 -  range_rounding > vars->player->th)
		|| (M_PI_2 + range_rounding < vars->player->th && M_PI - range_rounding > vars->player->th))
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x + ((vars->player->RW_y % RW_UNIT) / tan(vars->player->th));
		first_hor_grid_coll_RW_y = (vars->player->RW_y / RW_UNIT) * RW_UNIT;
		// next hit has x coord of first hit + dx, y coord of first hit + dy;
		/// if init i = 0, iterate in i * dx, i * dy orr something like that.make
		while ()
	}

	// 3rd octant
	// 4th octant
	if ((vars->player->th > M_PI + range_rounding && vars->player->th < 3 * M_PI_2 - range_rounding)
		|| (vars->player->th > 3 * M_PI_2 + range_rounding && vars->player->th < (M_PI * 2) - range_rounding))
	{
		first_hor_grid_coll_RW_x = vars->player->RW_x - ((RW_UNIT - vars->player->RW_y % RW_UNIT) / tan(vars->player->th)); 
		first_hor_grid_coll_RW_y = ((vars->player->RW_y / RW_UNIT) + 1) * RW_UNIT;
	}

	if (!(first_hor_grid_coll_RW_x <= 0
		|| first_hor_grid_coll_RW_y <= 0
		|| first_hor_grid_coll_RW_x >= (vars->map->max_width - 1) * RW_UNIT
		|| first_hor_grid_coll_RW_y >= vars->map->n_lines * RW_UNIT))
			draw_line(vars->minimap->img, \
				vars->player->RW_x * vars->minimap->scale / RW_UNIT, \
				vars->player->RW_y * vars->minimap->scale / RW_UNIT, \
				(int)first_hor_grid_coll_RW_x * vars->minimap->scale / RW_UNIT, \
				(int)first_hor_grid_coll_RW_y * vars->minimap->scale / RW_UNIT);
	// if statement makes sure that only if intersection exists  the line is drawwn -> use later to check.


	// put to window
	mlx_put_image_to_window(vars->mlx_vars->mlx_ptr, \
		vars->mlx_vars->win_ptr, \
		vars->minimap->img->img_ptr, \
		vars->minimap->img->S_xtlc, \
		vars->minimap->img->S_ytlc);

}