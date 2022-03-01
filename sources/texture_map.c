#include "../header/cub3d.h"

int	get_pixel_color(t_image *img, double x, double y)
{
	char	*dst;

	// if (x < 0)
	// 	x = 0;
	// if (y < 0)
	// 	y = 0;
	// if (x >= img->width)
	// 	x = img->width - 1;
	// if (y >= img->height)
	// 	y = img->height - 1;
	dst = img->address + ((int)floor(y) * img->line_length + (int)floor(x) * (img->bits_per_pixel / 8));
	//printf("test: %p\n", dst);
	return (*(unsigned int *)dst);
}

void	draw_tex_line(t_vars *vars, t_ray *ray, int line_height, t_image *src_img, int i)
{
	int		y;
	double	incr;
	int		color;

	color = 0;
	y = 0;
	incr = (double)src_img->height / line_height;
	while (y < line_height)
	{
		if (ray->facing_direction == 1 || ray->facing_direction == 3)
			color = get_pixel_color(src_img, (fmod(ray->closest_hit.x, vars->scale) / vars->scale) * src_img->width, y * incr);
		if (ray->facing_direction == 2 || ray->facing_direction == 4)
			color = get_pixel_color(src_img, (fmod(ray->closest_hit.y, vars->scale) / vars->scale) * src_img->width, y * incr);
		//printf("color: %d, x: %f, y: %d, i: %d\n", color, ray->closest_hit.x, y, i);
		cub_pixel_put(vars->main_img, PRJP_W - i - 1, y + (vars->main_img->height / 2) - line_height / 2, color);
		y++;
	}
}