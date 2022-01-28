#include "../header/cub3d.h"

int	cub_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->mlx_vars->mainImg->address +
	(y * vars->mlx_vars->mainImg->line_length +
	x * (vars->mlx_vars->mainImg->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

void	fcku(t_vars *vars)
{
	// fill image -> I drew a square. alternate white and blue
	int i = 0;
	int j, k, l;

	// blinking square test:
/* 	while (i < 100) {j = 0; while (j < 100) {cub_pixel_put(vars, 500 + i + vars->mlx_vars->test, 500 + j + vars->mlx_vars->test, 0xffffff5 + vars->mlx_vars->test);j++;}i++;} */

	int w = 10;
	int h = 10;
/* 	int testmap[h][w] = 
	{
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1},
	}; */
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
	// h = 13;
	// 	int testmap[13][10] = 
	// {
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	// 	{1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	// 	{1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	// 	{1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// };
	int scale = 50; // distance in pixel between points
	int offset = 500; // here it is both for x and for y, it is the distance from tlc of screen.
	// solution for color:multiply white by 0 or one, to switch on/off
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			// dreaw a square for every dot, with tlc = dot
				k = 0;
				while (k < scale)
				{
					l = 0;
					while (l < scale)
					{
						cub_pixel_put(vars, (j * scale + offset) + l, (i * scale + offset) + k, testmap[i][j] * 0xffffff + vars->mlx_vars->test);
						l++;
					}
					k++;
				}
			// draws nodes:
			cub_pixel_put(vars, j * scale + offset, i * scale + offset, testmap[i][j] * 0xfffffff);
			j++;
		}
		i++;
	}

		int pw = 10;
		int ph = 10;

		// vars->px = 0;
		// vars->py = 0;
		// draw palyer
		k = 0;
		while (k < ph)
		{
			l = 0;
			while (l < pw)
			{
				cub_pixel_put(vars, (vars->px * 10 + offset) + l, (vars->py * 10 + offset) + k, 0xf9dc4a);
				l++;
			}
			k++;
		}

}

/* 
void	raycast_urmom(t_vars *vars)
{
	int i = 0;
	int j;
	int w = 13;
	int h = 10;
	int testmap[13][10] = 
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};



}*/

void draw(t_vars *vars)
{

	mlx_clear_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window);

	if (vars->mlx_vars->mainImg)
	{
		free(vars->mlx_vars->mainImg);
		vars->mlx_vars->mainImg = NULL;
	}
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


	mlx_put_image_to_window(vars->mlx_vars->mlx_ref, vars->mlx_vars->window, vars->mlx_vars->mainImg->ref, 0, 0);
	// free(vars->mlx_vars->mainImg);
}