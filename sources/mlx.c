#include "../header/cub3d.h"

/*
*Loads an image from path and returns MLX-Image as void pointer.
*Returns NULL Pointer if file invalid
*/
void	*loadimage(char *path, t_vars *vars)
{
	void	*img;
	int		fd;
	int		width;
	int		height;

	if (!path)
	{
		printf("Error: Empty image file name.\n");
		return(NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		return (NULL);
	}
	img = mlx_xpm_file_to_image(vars->mlx_vars->mlx_ref, path, &width, &height);
	if (!img)
	{
		printf("Error: Image file could not be opened. Please make sure it exists and is in .xpm format.\n");
		return(NULL);
	}
	close (fd);
	return (img);
}


/*
*Initializes MLX variables
*/
int	init_mlx_vars(t_vars *vars)
{
	vars->mlx_vars = malloc(sizeof(t_mlx_vars));
	if (!vars->mlx_vars)
	{
		printf("Failed to allocate mlx_vars memory.\n");
		return (1);
	}
	vars->mlx_vars->mlx_ref = mlx_init();
	if (!vars->mlx_vars->mlx_ref)
	{
		printf("Failed to initialize mlx\n");
		return (2);
	}
	vars->mlx_vars->window
		= mlx_new_window(vars->mlx_vars->mlx_ref, WW, WH, "cub3d");
	if (!vars->mlx_vars->window)
	{
		printf("Failed to initialize mlx window\n");
		return (3);
	}
	return (0);
}
