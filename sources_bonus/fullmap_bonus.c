#include "../header_bonus/cub3d_bonus.h"

int	create_fullmap(t_vars *vars)
{
	if (vars->map->n_lines >= vars->map->max_width)
		vars->full_map.blocksize = vars->full_map.max_height / vars->map->n_lines;
	else
		vars->full_map.blocksize = vars->full_map.max_width / (vars->map->max_width - 1);
	if (vars->full_map.blocksize > 20)
		vars->full_map.blocksize = 20;
	if (vars->full_map.blocksize < 5)
		vars->full_map.blocksize = 5;
	vars->full_map.width = vars->full_map.blocksize * (vars->map->max_width - 1);
	vars->full_map.height = vars->full_map.blocksize * vars->map->n_lines;
	vars->full_map.player_size = vars->full_map.blocksize / 3;
	vars->full_map.img = new_image(vars, \
		vars->full_map.width, \
		vars->full_map.height, \
		vars->full_map.top_left_corner_pos);
	if (!vars->full_map.img)
		return (0);
	return (1);
}

void	draw_player_full_map(t_vars *vars)
{
	draw_square_tlc(vars->full_map.img, vars->full_map.player_size, vars->full_map.player_size, \
		vars->player.pos.x * vars->full_map.blocksize / SCALE - vars->full_map.player_size / 2, \
		vars->player.pos.y * vars->full_map.blocksize / SCALE - vars->full_map.player_size / 2, \
		vars->minimap.player_color);
}

/*
*	Draw the blocks of the 2d world in the minimap
*/
void	draw_blocks_full_map(t_vars *vars, t_image *map_img, int blocksize)
{
	int i, j;
	i = 0;
	while (vars->map->nodes[i] && i < vars->map->n_lines)
	{
		j = 0;
		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
		{
			if (vars->map->nodes[i][j] == '1')
				draw_square_tlc(map_img, blocksize - 1, blocksize - 1, \
					j * blocksize, i * blocksize, vars->minimap.wall_color);
			if (vars->map->nodes[i][j] == '0')
				draw_square_tlc(map_img, blocksize - 1, blocksize - 1, \
					j * blocksize, i * blocksize, vars->minimap.floor_color);
			j++;
		}
		i++;
	}
}
void	draw_ray_fullmap(t_vars *vars, t_ray *ray)
{
	draw_line(vars->full_map.img, \
		vars->player.pos.x * vars->full_map.blocksize / SCALE, \
		vars->player.pos.y * vars->full_map.blocksize / SCALE, \
		(int)ray->closest_hit.x * vars->full_map.blocksize / SCALE, \
		(int)ray->closest_hit.y * vars->full_map.blocksize / SCALE, vars->minimap.ray_color);
}

void	draw_full_map(t_vars *vars)
{
	// background:
	draw_square_tlc(vars->full_map.img, vars->full_map.width, vars->full_map.height, 0, 0, vars->minimap.background_color);
	draw_blocks_full_map(vars, vars->full_map.img, vars->full_map.blocksize);
}