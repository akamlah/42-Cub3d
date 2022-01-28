r#include "../header/cub3d.h"

int	init_map(t_vars *vars)
{
	//vars->character_pos = vars->spawn_pos;
	vars->character_pos.x = 300;
	vars->character_pos.y = 300;
	vars->direction.x = -1;
	vars->direction.y = 0;
	vars->cam_plane.x = 0;
	vars->cam_plane.y = 0.66f;
	vars->time = 0;
	vars->oldTime = 0;
	return (0);
}

// int	cast_ray(t_vars *vars)
// {
// 	int		x;
// 	int		y;
// 	double	camera_x;
// 	double	ray_x;
// 	double	ray_y;

// 	x = 0;
// 	y = 0;
// 	ray_x = 0;
// 	ray_y = 0;
// 	camera_x = 0;
// 	//raycast loop
// 	while (x < WW)
// 	{
// 		camera_x = 2 * x / WW -1;
// 		ray_x = vars->direction.x + vars->cam_plane.x * camera_x;
// 		ray_y = vars->direction.y + vars->cam_plane.y * camera_x;
		

// 		x++;


// 	}

// }

void	drawSquare()//t_vars *vars, int startX, int startY, int sideSize)
{

	return ;
}

int	render(t_vars *vars)
{
	t_vars *tempvars;
	tempvars = vars;
	int x = 0;
	int y = 0;

	vars->buffer = mlx_get_data_addr(vars->mlx_vars->minimapImg, &vars->bits_per_pixel, &vars->sizeline, &vars->endian);
	vars->sizeline /= 4;
	while (y < 500)
	{
		while (x < 500)
		{
			vars->buffer [(y * vars->sizeline) + x] = mlx_get_color_value(vars->mlx_vars->mlx, 113245678);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
