#include "../header/cub3d.h"

/*
	Draws a pixel in the given image given its image coordinate (x, y)
	and its color 'col'
*/
int	cub_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

/*
	This function allocates memory for a new image and initialises it with the given size
	and position of its top left corner in the window (S_xtlc, S_ytlc) (values in pixel), and
	returns a pointer to it.
*/
t_image *new_image(t_vars *vars, int width, int height, t_vector2 pos)
{
	t_image	*new_image;

	new_image = malloc(sizeof(t_image));
	new_image->width = width;
	new_image->height = height;
	new_image->pos = pos;
	new_image->img_ptr = mlx_new_image(vars->mlx_vars->mlx_ptr, new_image->width, new_image->height);
	new_image->address = mlx_get_data_addr(new_image->img_ptr, &new_image->bits_per_pixel, &new_image->line_length, &new_image->endian);
	if (!new_image->address)
	{
		printf("Error: Failed to retrieve image address\n");
		free_and_exit(vars);
	}
	return (new_image);
}

/*
	This function allocates memory for a new image and initialises it with the given size
	and position of its top left corner in the window (S_xtlc, S_ytlc) (values in pixel), and
	returns a pointer to it.
*/
t_image *new_image_tex(t_vars *vars, char *tex_path)
{
	t_image	*new_image;

	new_image = malloc(sizeof(t_image));
	new_image->width = 0;
	new_image->height = 0;

	new_image->img_ptr = loadimage(tex_path, vars, new_image);
	new_image->address = mlx_get_data_addr(new_image->img_ptr, &new_image->bits_per_pixel, &new_image->line_length, &new_image->endian);
	if (!new_image->address)
	{
		printf("Error: Failed to retrieve image address\n");
		free_and_exit(vars);
	}
	return (new_image);
}
/*
	Draws a square sized 'xsize' * 'ysize' pixels given:
	- width and height in pixels
	- its top left corner (I_xtlc, I_ytlc) in IMAGE coordinates, in pixels
	- its color 'color'
	The if statement before drawing allows only pixels that actually fall into img boundaries to be drawn.
*/
void	draw_square_tlc(t_image *img, int width, int height, int I_xtlc, int I_ytlc, int color)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if ((I_xtlc + j < img->width && I_ytlc + i < img->height)
				&& (I_xtlc >= 0 && I_ytlc >= 0))
				cub_pixel_put(img, I_xtlc + j, I_ytlc + i, color);
			j++;
		}
		i++;
	}
}

/*
	Draws a line with Bresenham algorithm from point o to point end
*/
void	draw_line(t_image *img, int I_xo, int I_yo, int I_xend, int I_yend, int color)
{
	int sx, sy, err, dx, dy, e2;
	dx = abs(I_xend - I_xo);
	if (I_xo < I_xend)
		sx = 1;
	else
		sx = -1;
	dy = -abs(I_yend - I_yo);
	if (I_yo < I_yend)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		if ((I_xo >= 0 && I_xo < img->width)// && I_xend >= 0 && I_xend < img->width)
			&& (I_yo >= 0 && I_yo < img->height))// && I_yend >= 0 && I_yend < img->height))
		cub_pixel_put(img, I_xo, I_yo, color);
		if (I_xo == I_xend && I_yo == I_yend)
			break ;
		e2 = 2 * err;
		if (e2 > dy)
		{
			err += dy;
			I_xo += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			I_yo += sy;
		}
	}
}

/*
*Loads an image from path and returns MLX-Image as void pointer.
*Returns NULL Pointer if file invalid
*/
void	*loadimage(char *path, t_vars *vars, t_image *img_memory)
{
	void	*img;
	int		fd;

	if (!path)
	{
		printf("Error: Empty image file name.\n");
		free_and_exit(vars);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		free_and_exit(vars);
	}
	img = mlx_xpm_file_to_image(vars->mlx_vars->mlx_ptr, path, &img_memory->width, &img_memory->height);
	if (!img)
	{
		printf("Error: Image file could not be opened. Please make sure it exists and is in .xpm format.\n");
		free_and_exit(vars);
	}
	close (fd);
	return (img);
}
