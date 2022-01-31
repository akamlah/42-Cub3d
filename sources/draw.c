#include "../header/cub3d.h"

// put pixel to image
int	cub_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

// draw square top left corner of given position. too many vars -> typedef?
void	draw_square_tlc(t_image *img, int xsize, int ysize, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < ysize)
	{
		j = 0;
		while (j < xsize)
		{
			cub_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_frame(t_image *img, int w, int h, int xtl, int ytl, int col)
{
	int i;
	int j;

	i = 0;
	while (i < h)
	{
		cub_pixel_put(img, xtl, ytl + i, col);
		cub_pixel_put(img, xtl + w, ytl + i, col);
		i++;
	}
	j = 0;
	while (j < w)
	{
		cub_pixel_put(img, xtl + j, ytl, col);
		cub_pixel_put(img, xtl + j, ytl + h, col);
		j++;
	}
}

void draw_player_minimap(t_vars *vars)
{
	draw_square_tlc(vars->mlx_vars->minimap, vars->ps, \
	vars->ps, vars->px + vars->minimap_xframeoffset, \
	vars->py + vars->minimap_yframeoffset, \
	0xfaf20f);
}


void	fill_minimap(t_vars *vars)
{
	int i;
	int j;
	int col;
	// minimap background?
	i = 0;
	while (vars->map->nodes[i] && i < vars->map->n_lines)
	{
		j = 0;
		while (vars->map->nodes[i][j] && vars->map->nodes[i][j] != '\n')
		{
			if (vars->map->nodes[i][j] == 'N')
			{
				vars->px = j * vars->minimap_scale + vars->minimap_scale / 2 - vars->ps / 2;
				vars->py = i * vars->minimap_scale + vars->minimap_scale / 2 - vars->ps / 2;
				vars->map->nodes[i][j] = '0';
			}
			if (vars->map->nodes[i][j] == '1')
				col = 1;
			else
				col = 0;
			if (vars->map->nodes[i][j] == '1' || vars->map->nodes[i][j] == '0')
			{
				draw_square_tlc(vars->mlx_vars->minimap, vars->minimap_scale - 1, vars->minimap_scale - 1, \
				(j * vars->minimap_scale + vars->minimap_xframeoffset), \
				(i * vars->minimap_scale + vars->minimap_yframeoffset), col * 0xffffff);
			}
			j++;
		}
		i++;
	}

}

void	draw_minimap(t_vars *vars)
{
	vars->minimap_xframeoffset = 10;
	vars->minimap_yframeoffset = 10;
	vars->minimap_xframelen = vars->minimap_scale * (vars->map->max_width - 1) + vars->minimap_xframeoffset * 2;
	vars->minimap_yframelen = vars->minimap_scale * vars->map->n_lines + vars->minimap_yframeoffset * 2;
	vars->mlx_vars->minimap = malloc(sizeof(t_image));
	vars->mlx_vars->minimap->ref = mlx_new_image(vars->mlx_vars->mlx_ref, vars->minimap_xframelen, \
		vars->minimap_yframelen);
	vars->mlx_vars->minimap->address = mlx_get_data_addr(vars->mlx_vars->minimap->ref, \
		&vars->mlx_vars->minimap->bits_per_pixel, &vars->mlx_vars->minimap->line_length, \
		&vars->mlx_vars->minimap->endian);
	draw_square_tlc(vars->mlx_vars->minimap, vars->minimap_xframelen - 4, vars->minimap_yframelen - 4, 2, 2, 0x809672);
	draw_frame(vars->mlx_vars->minimap, vars->minimap_xframelen - 1, vars->minimap_yframelen -1, 0, 0, 0xf4f2f3);
	fill_minimap(vars);
	draw_player_minimap(vars);
	vars->minimap_xwinoffset = 20;
	vars->minimap_ywinoffset = WH - vars->minimap_yframelen - 20;
	mlx_put_image_to_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, vars->mlx_vars->minimap->ref, \
	vars->minimap_xwinoffset, vars->minimap_ywinoffset);
}

void	draw_background(t_vars *vars)
{
	vars->mlx_vars->background = malloc(sizeof(t_image));
	vars->mlx_vars->background->ref = mlx_new_image(vars->mlx_vars->mlx_ref, WW, WH);
	vars->mlx_vars->background->address = mlx_get_data_addr(vars->mlx_vars->background->ref, &vars->mlx_vars->background->bits_per_pixel, &vars->mlx_vars->background->line_length, &vars->mlx_vars->background->endian);
	// background color
	draw_square_tlc(vars->mlx_vars->background, WW, WH, 0, 0, 0x1e1a1c);
	draw_frame(vars->mlx_vars->background, WW - 10, WH - 10, 5, 5, 0xf4f2f3);
	mlx_put_image_to_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, vars->mlx_vars->background->ref, 0, 0);
}


void render_raycast(t_vars *vars)
{
	vars->mlx_vars->raycast = malloc(sizeof(t_image));
	vars->mlx_vars->raycast->ref = mlx_new_image(vars->mlx_vars->mlx_ref, WW - 100, WH - 100);
	vars->mlx_vars->raycast->address = mlx_get_data_addr(vars->mlx_vars->raycast->ref, \
	&vars->mlx_vars->raycast->bits_per_pixel, &vars->mlx_vars->raycast->line_length, \
	&vars->mlx_vars->raycast->endian);

	draw_square_tlc(vars->mlx_vars->raycast, WW - 100, WH - 100, 0, 0, 0xffffff);
	
	
	mlx_put_image_to_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, \
	vars->mlx_vars->raycast->ref, 50, 50);
}

void compone_window(t_vars *vars)
{
	draw_background(vars);

	render_raycast(vars);
	draw_minimap(vars);

	// write player coord on screen:
	char *tmp;
	tmp = ft_strjoin("Player x coordinate: ", ft_itoa(vars->px));
	mlx_string_put(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, 10, 10, 0xffffff, tmp);
	free(tmp);
	tmp = ft_strjoin("Player y coordinate: ", ft_itoa(vars->py));
	mlx_string_put(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, 10, 30, 0xffffff, tmp);
	free(tmp);
}

// ----------------------------------------------------------------

// // testbench
// void	testdraw(t_vars *vars)
// {
// 	int i = 0;
// 	int j;//, k, l;
// 	int w = 10;
// 	int h = 10;
// 	int testmap[10][10] = 
// 	{
// 		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 1, 2, 1, 0, 1, 1, 1, 0, 1},
// 		{1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
// 		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
// 		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
// 		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
// 		{1, 0, 1, 0, 0, 1, 1, 1, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	};
// 	// background
// 	draw_square_tlc(vars->mlx_vars->minimap, vars->minimap_scale * w + 1, \
// 	(vars->minimap_xwinoffset - 1), \
// 	(vars->minimap_ywinoffset - 1), \
// 	0x91cad1);//+ vars->mlx_vars->test);
// 	while (i < h)
// 	{
// 		j = 0;
// 		while (j < w)
// 		{
// 			// draws node:
// 			// cub_pixel_put(vars->mlx_vars->minimap, j * vars->minimap_scale + vars->minimap_xwinoffset, \
// 			// i * vars->minimap_scale + vars->minimap_ywinoffset, testmap[i][j] * 0xfffffff);
// 			// dreaw a square for every dot, with tlc = dot
// 			if (testmap[i][j] == 2)
// 			{
// 				vars->px = j * vars->minimap_scale + vars->minimap_xwinoffset + vars->minimap_scale / 2 - vars->ps / 2; 
// 				vars->py = i * vars->minimap_scale + vars->minimap_ywinoffset + vars->minimap_scale / 2 - vars->ps / 2;
// 				testmap[i][j] = 0;
// 			}
// 			draw_square_tlc(vars->mlx_vars->minimap, vars->minimap_scale - 1, \
// 			(j * vars->minimap_scale + vars->minimap_xwinoffset), \
// 			(i * vars->minimap_scale + vars->minimap_ywinoffset), \
// 			testmap[i][j] * 0xffffff);//+ vars->mlx_vars->test);
// 			j++;
// 		}
// 		i++;
// 	}
// 	draw_player(vars);
// }