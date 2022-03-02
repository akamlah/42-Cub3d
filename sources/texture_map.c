#include "../header/cub3d.h"

int	get_pixel_color(t_image *img, double x, double y)
{
	char	*dst;

	dst = img->address + ((int)floor(y) * img->line_length + (int)floor(x) * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_tex_line(t_vars *vars, t_ray *ray, int line_height, t_image *src_img, int i)
{
	int		y;
	double	incr;
	int		color;
	double	tex_x;
	double	y_offs;
	int		img_addr_offs;


	img_addr_offs = (MAIN_IMG_W - i - 1) * (vars->main_img->bits_per_pixel / 8);
	color = 0;
	y = 0;
	y_offs = (vars->main_img->height / 2) - line_height / 2;
	incr = (double)src_img->height / line_height;
	if (ray->facing_direction == 1 || ray->facing_direction == 3)
	{
		tex_x = (fmod((ray->closest_hit.x), SCALE) / SCALE) * src_img->width ;
	}
	else
		tex_x = (fmod(ray->closest_hit.y, SCALE) / SCALE) * src_img->width;
	
	while (y < line_height)
	{
		color = get_pixel_color(src_img, tex_x, y * incr);
		*(unsigned int *)(vars->main_img->address + (int)((y + y_offs) * vars->main_img->line_length + img_addr_offs)) = color;
		y++;
	}
}