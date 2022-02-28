#include "../header/cub3d.h"

void	init_minimap(t_vars *vars)
{
	if (!vars->minimap)
		vars->minimap = malloc(sizeof(t_minimap));
	vars->minimap->scale = 30;
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
		0x003333);

	// draw blocks
	draw_blocks_minimap(vars);
	// draw_player_minimap(vars);
}
