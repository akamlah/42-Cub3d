#include "../header/cub3d.h"

// put pixel to image
int	cub_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address +
	(y * img->line_length +
	x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

// draw square top left corner of given position. too many vars -> typedef?
void	draw_square_tlc(t_image *img, int size, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			cub_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_vars *vars)
{
	int psize = 4;
	draw_square_tlc(vars->mlx_vars->mainImg, psize, (vars->px * psize + vars->minimap_xoffset), \
	vars->py * psize + vars->minimap_xoffset, 0xfaf20f);
}

// testbench
void	fcku(t_vars *vars)
{
	int i = 0;
	int j;//, k, l;
	int w = 10;
	int h = 10;
	int testmap[10][10] = 
	{
		{1, 1, 1, 0, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
		{1, 1, 0, 0, 1, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
	};
	// background
	draw_square_tlc(vars->mlx_vars->mainImg, vars->minimap_scale * w + 1, \
	(vars->minimap_xoffset - 1), \
	(vars->minimap_yoffset - 1), \
	0x91cad1);//+ vars->mlx_vars->test);
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			// draws node:
			// cub_pixel_put(vars->mlx_vars->mainImg, j * vars->minimap_scale + vars->minimap_xoffset, \
			// i * vars->minimap_scale + vars->minimap_yoffset, testmap[i][j] * 0xfffffff);
			// dreaw a square for every dot, with tlc = dot
			draw_square_tlc(vars->mlx_vars->mainImg, vars->minimap_scale - 1, \
			(j * vars->minimap_scale + vars->minimap_xoffset), \
			(i * vars->minimap_scale + vars->minimap_yoffset), \
			testmap[i][j] * 0xffffff);//+ vars->mlx_vars->test);
			j++;
		}
		i++;
	}
	draw_player(vars);
}

void draw(t_vars *vars)
{
	vars->mlx_vars->mainImg = malloc(sizeof(t_image));
	vars->mlx_vars->mainImg->ref = mlx_new_image(vars->mlx_vars->mlx_ref, WW, WH);
	// printf("%p\n", vars->mlx_vars->mlx_ref);//, vars->mlx_vars->mainImg, vars->mlx_vars->window);
	vars->mlx_vars->mainImg->address = mlx_get_data_addr(vars->mlx_vars->mainImg->ref, 
		&vars->mlx_vars->mainImg->bits_per_pixel, 
		&vars->mlx_vars->mainImg->line_length, 
		&vars->mlx_vars->mainImg->endian);
	// fill image -> I drew a square. change col with 's'.
	fcku(vars);
	// raycasted:
	// raycast_urmom(vars);
	mlx_put_image_to_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, \
	vars->mlx_vars->mainImg->ref, 0, 0);
	// free(vars->mlx_vars->mainImg);
}