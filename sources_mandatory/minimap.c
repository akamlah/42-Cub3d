#include "../header/cub3d.h"

int	create_minimap(t_vars *vars)
{
	if (vars->minimap.height >= vars->minimap.width)
		vars->minimap.scale = vars->minimap.height / 12;
	else
		vars->minimap.scale = vars->full_map.max_width / 12;
	if (vars->minimap.scale > 20)
		vars->minimap.scale = 20;
	else if (vars->minimap.scale < 5)
		vars->minimap.scale = 5;
	vars->minimap.width = vars->minimap.width / vars->minimap.scale * vars->minimap.scale;
	vars->minimap.height = vars->minimap.height / vars->minimap.scale * vars->minimap.scale;
	vars->minimap.total_width = (vars->map->max_width - 1) * vars->minimap.scale;
	vars->minimap.total_height = vars->map->n_lines * vars->minimap.scale;
	vars->minimap.p_pos.y = WH - vars->minimap.height - 25;
	vars->minimap.p_pos.x = 25;
	vars->mlx_vars->minimap = new_image(vars, vars->minimap.width, \
	vars->minimap.height, vars->minimap.p_pos);
	if (!vars->mlx_vars->minimap)
		return (0);
	return (1);
}


/*
*	Draw the blocks of the 2d world in the minimap
*/
void	draw_blocks_minimap(t_vars *vars, t_image *map_img, int	blocksize)
{
	int i, j;

	i = 0;
	while (vars->map->nodes[i + vars->minimap.h_offs] \
		&& i + vars->minimap.h_offs < vars->map->n_lines
		&& i * vars->minimap.scale < vars->minimap.height)
	{
		j = 0;
		while (vars->map->nodes[i + vars->minimap.h_offs][j + vars->minimap.w_offs] \
			&& vars->map->nodes[i + vars->minimap.h_offs][j + vars->minimap.w_offs] != '\n'
			&& j * vars->minimap.scale < vars->minimap.width )
		{
			if (vars->map->nodes[i+ vars->minimap.h_offs][j + vars->minimap.w_offs] == '1')
				draw_square_tlc(map_img, blocksize - 1, blocksize - 1, \
					(j * blocksize), (i * blocksize), vars->minimap.wall_color);
			if (vars->map->nodes[i + vars->minimap.h_offs][j + vars->minimap.w_offs] == '0')
				draw_square_tlc(map_img, blocksize - 1, blocksize - 1, \
					(j * blocksize), (i * blocksize), vars->minimap.floor_color);
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_vars *vars)
{
	draw_square_tlc(vars->mlx_vars->minimap, vars->minimap.player_size, vars->minimap.player_size, \
		(vars->player.pos.x * vars->minimap.scale / SCALE - vars->minimap.player_size / 2)\
		 - vars->minimap.w_offs * vars->minimap.scale, \
		(vars->player.pos.y * vars->minimap.scale / SCALE - vars->minimap.player_size / 2)\
		 - vars->minimap.h_offs * vars->minimap.scale, \
		vars->minimap.player_color);
}

void	draw_minimap(t_vars *vars)
{
	// background
	draw_square_tlc(vars->mlx_vars->minimap, \
		vars->mlx_vars->minimap->width, \
		vars->mlx_vars->minimap->height, 0 ,0, \
		vars->minimap.background_color);
	vars->minimap.h_offs = vars->player.pos.y / SCALE - (vars->minimap.height / 2 / vars->minimap.scale);
	if (vars->minimap.h_offs < 0)
		vars->minimap.h_offs = 0;
	if (vars->minimap.h_offs > (vars->minimap.total_height - vars->minimap.height) / vars->minimap.scale)
		vars->minimap.h_offs = (vars->minimap.total_height - vars->minimap.height) / vars->minimap.scale;
	vars->minimap.w_offs = vars->player.pos.x / SCALE - (vars->minimap.width / 2 / vars->minimap.scale);
	if (vars->minimap.w_offs < 0)
		vars->minimap.w_offs = 0;
	if (vars->minimap.w_offs > (vars->minimap.total_width - vars->minimap.width) / vars->minimap.scale)
		vars->minimap.w_offs = (vars->minimap.total_width - vars->minimap.width) / vars->minimap.scale;
	draw_blocks_minimap(vars, vars->mlx_vars->minimap, vars->minimap.scale);
}

void	draw_ray_minimap(t_vars *vars, t_ray *ray)
{
	draw_line(vars->mlx_vars->minimap, \
		vars->player.pos.x * vars->minimap.scale / SCALE\
		 - vars->minimap.w_offs * vars->minimap.scale, \
		vars->player.pos.y * vars->minimap.scale / SCALE\
		 - vars->minimap.h_offs * vars->minimap.scale, \
		(int)ray->closest_hit.x * vars->minimap.scale / SCALE\
		 - vars->minimap.w_offs * vars->minimap.scale, \
		(int)ray->closest_hit.y * vars->minimap.scale / SCALE\
		 - vars->minimap.h_offs * vars->minimap.scale, \
		 vars->minimap.ray_color);
}