#include "../header/cub3d.h"

void draw(t_vars *vars)
{
	// clear window fo rsfter hook todo


	vars->mlx_vars->mainImg = mlx_new_image(vars->mlx_vars->mlx, WW, WH);

	// printf("%p\n", vars->mlx_vars->mlx);//, vars->mlx_vars->mainImg, vars->mlx_vars->window);

	vars->mlx_vars->addr = mlx_get_data_addr(vars->mlx_vars->mainImg, &vars->mlx_vars->bpp, 
		&vars->mlx_vars->ll, &vars->mlx_vars->edn);


	mlx_put_image_to_window(vars->mlx_vars->mlx, vars->mlx_vars->window, vars->mlx_vars->mainImg, 0, 0);
}