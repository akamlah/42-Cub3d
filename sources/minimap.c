#include "../header/cub3d.h"

void	create_minimap(t_vars *vars)
{
	vars->minimap.p_pos.y = WH - vars->map->n_lines * vars->minimap.scale - 10;
	vars->minimap.p_pos.x = 10;
	vars->mlx_vars->minimap = new_image(vars, (vars->map->max_width - 1) * vars->minimap.scale, \
	vars->map->n_lines * vars->minimap.scale, vars->minimap.p_pos);
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
				draw_square_tlc(vars->mlx_vars->minimap, \
					vars->minimap.scale - 1, \
					vars->minimap.scale - 1, \
					j * vars->minimap.scale, \
					i * vars->minimap.scale, \
					0xffffff);
			if (vars->map->nodes[i][j] == '0')
				draw_square_tlc(vars->mlx_vars->minimap, \
					vars->minimap.scale - 1, \
					vars->minimap.scale - 1, \
					j * vars->minimap.scale, \
					i * vars->minimap.scale, \
					0x000000);
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_vars *vars)
{
	int size;

	// for now player as cube 1/10 of blocksize in minimap
	size = vars->minimap.scale / 10;
	draw_square_tlc(vars->mlx_vars->minimap, size, size, \
	// conversion RW coords to minimap coords
		vars->player.pos.x * vars->minimap.scale / SCALE - size / 2, \
		vars->player.pos.y * vars->minimap.scale / SCALE - size / 2, \
	0xff0000);
}

void	draw_minimap(t_vars *vars)
{
	// init_minimap(vars);

	// background
	draw_square_tlc(vars->mlx_vars->minimap, \
		vars->mlx_vars->minimap->width, \
		vars->mlx_vars->minimap->height, \
		0, \
		0, \
		0x003333);

	// draw blocks
	draw_blocks_minimap(vars);
	// draw_player_minimap(vars);
}
